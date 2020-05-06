#ifndef LOADER_H
#define LOADER_H
#include <future>
#include <iostream>
#include <utility>
#include <QThread>

#include "vec3.h"
#include "mesh.h"

class Parser : public QThread
{
    Q_OBJECT
public:
    explicit Parser(QObject* parent, QString file_name, bool reloaded);
    ~Parser();
    void run();
    Mesh* get_mesh() { return object; }
    void sort_vector(Vector3* begin, Vector3* end, int threads);
    Mesh* generate_mesh(uint32_t tri_count, QVector<Vector3>& verts);

protected:
    Mesh* parse_stl();
    //Mesh* combine_mesh(const Mesh*& left, const Mesh*& right);
    Mesh* parse_ascii(QFile& fi);
    Mesh* parse_binary(QFile& fi);

signals:
    void loaded_file(QString filename);
    void got_mesh(Mesh* m, Mesh* b, bool is_reload);
    void error_bad_stl();
    void error_empty_mesh();
    void warning_confusing_stl();
    void error_missing_file();

private:
    QString filename;
    bool is_reload;
    bool confusing_stl{};
    Mesh* object;

};

#endif // LOADER_H
