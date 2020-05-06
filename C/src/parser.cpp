#include "parser.h"

Parser::Parser(QObject* parent, QString  file_name, bool reloaded)
        : QThread(parent), filename(std::move(file_name)), is_reload(reloaded)
{
    object = nullptr;
}

Parser::~Parser() {
    object = nullptr;
}

Mesh* Parser::parse_ascii(QFile& fi)
{
    fi.readLine();
    uint32_t tri_count = 0;
    QVector<Vector3> verts(tri_count * 3);
    bool okay = true;
    while (!fi.atEnd() && okay)
    {
        const auto line = fi.readLine().simplified();
        if (line.startsWith("endsolid"))
        {
            break;
        }
        else if (!line.startsWith("facet normal") ||
                 !fi.readLine().simplified().startsWith("outer loop"))
        {
            okay = false;
            break;
        }

        for (int i=0; i < 3; ++i)
        {
            auto line_array = fi.readLine().simplified().split(' ');
            if (line_array[0] != "vertex")
            {
                okay = false;
                break;
            }
            const float x = line_array[1].toFloat(&okay);
            const float y = line_array[2].toFloat(&okay);
            const float z = line_array[3].toFloat(&okay);
            verts.push_back(Vector3(x, y, z));
        }
        if (!fi.readLine().trimmed().startsWith("endloop") ||
            !fi.readLine().trimmed().startsWith("endfacet"))
        {
            okay = false;
            break;
        }
        tri_count++;
    }
    if (okay)
    {
        return generate_mesh(tri_count, verts);
    }
    else
    {
        emit error_bad_stl();
        return nullptr;
    }
}

Mesh* Parser::parse_stl()
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        emit error_missing_file();
        return nullptr;
    }
    if (file.read(5) == "solid")
    {
        file.readLine(); // skip solid name
        const auto line = file.readLine().trimmed();
        if (line.startsWith("facet") ||
            line.startsWith("endsolid"))
        {
            file.seek(0);
            return parse_ascii(file);
        }
        confusing_stl = true;
    }
    else
    {
        confusing_stl = false;
    }
    file.seek(0);
    return parse_binary(file);
}

Mesh* Parser::generate_mesh(uint32_t tri_count, QVector<Vector3>& verts)
{
    size_t i = 0;
    while(i < tri_count * 3)
    {
        verts[i].i = i;
        ++i;
    }
    auto th = std::thread::hardware_concurrency();
    if (th == 0)
    {
        th = 8;
    }
    sort_vector(verts.begin(), verts.end(), th);
    std::vector<GLuint> indices(tri_count*3);
    size_t vertex_count = 0;
    for (auto v : verts)
    {
        if (!vertex_count || v != verts[vertex_count-1])
        {
            verts[vertex_count++] = v;
        }
        indices[v.i] = vertex_count - 1;
    }
    verts.resize(vertex_count);

    std::vector<GLfloat> flat_verts;
    flat_verts.reserve(vertex_count*3);
    for (auto v : verts)
    {
        flat_verts.push_back(v.x_val);
        flat_verts.push_back(v.y_val);
        flat_verts.push_back(v.z_val);
    }
    return new Mesh(std::move(flat_verts), std::move(indices));
}

Mesh* Parser::parse_binary(QFile& fi)
{
    QDataStream data(&fi);
    data.setByteOrder(QDataStream::LittleEndian);
    data.setFloatingPointPrecision(QDataStream::SinglePrecision);
    fi.seek(80);
    uint32_t tri_count;
    data >> tri_count;
    if (fi.size() != 84 + tri_count * 50)
    {
        emit error_bad_stl();
        return nullptr;
    }
    QVector<Vector3> verts(tri_count * 3);
    std::unique_ptr<uint8_t> buffer(new uint8_t[tri_count * 50]);
    data.readRawData((char*)buffer.get(), tri_count * 50);
    auto b = buffer.get() + 3 * sizeof(float);
    for (auto v=verts.begin(); v != verts.end(); v += 3)
    {
        for (unsigned i=0; i < 3; ++i)
        {
            memcpy(&v[i], b, 3*sizeof(float));
            b += 3 * sizeof(float);
        }
        b += 3 * sizeof(float) + sizeof(uint16_t);
    }
    if (confusing_stl)
    {
        emit warning_confusing_stl();
    }
    return generate_mesh(tri_count, verts);
}

void Parser::sort_vector(Vector3* begin, Vector3* end, int threads)
{
    if (threads < 2 || end - begin < 2)
    {
        std::sort(begin, end);
    }
    else
    {
        const auto mid = begin + (end - begin) / 2;
        if (threads == 2)
        {
            auto future = std::async(sort_vector, begin, mid, threads / 2);
            std::sort(mid, end);
            future.wait();
        }
        else
        {
            auto a = std::async(std::launch::async, sort_vector, begin, mid, threads / 2);
            auto b = std::async(std::launch::async, sort_vector, mid, end, threads / 2);
            a.wait();
            b.wait();
        }
        std::inplace_merge(begin, mid, end);
    }
}

void Parser::run()
{
    Mesh* mesh = parse_stl();
    QString temp = filename;
    QString temp2 = ":/gl_files/bed.stl";
    filename = temp2;
    Mesh* bed_mesh = parse_stl();
    if (bed_mesh)
    {
        if (bed_mesh->empty())
        {
            std::cout<<"Empty bed mesh"<<std::endl;
            emit error_empty_mesh();
            delete bed_mesh;
        }
        else
        {
            emit loaded_file(filename);
            //std::string utf8_text = filename.toUtf8().constData();
            //std::cout<<utf8_text<<std::endl;
        }
    }
    filename = temp;

    if (mesh)
    {
        if (mesh->empty())
        {
            emit error_empty_mesh();
            delete mesh;
        }
        else {
            object = mesh;
            emit got_mesh(mesh, bed_mesh, is_reload);
            emit loaded_file(filename);
        }
    }
}



