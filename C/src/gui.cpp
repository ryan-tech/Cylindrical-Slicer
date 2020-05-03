#include <QMenuBar>
#include "gui.h"
#include "renderer.h"


const QString Gui::RECENT_KEY = "recentFiles";

/* Parameterized Constructor:
 * Define Actions here (add actions in the gui.h file)
 * */
Gui::Gui(QWidget *parent) :
        QMainWindow(parent),
        open(new QAction("Open", this)),
        about(new QAction("About", this)),
        quit(new QAction("Quit", this)),
        perspective(new QAction("Perspective", this)),
        orthogonal(new QAction("Orthographic", this)),
        shaded(new QAction("Shaded", this)),
        wireframe(new QAction("Wireframe", this)),
        reload(new QAction("Reload", this)),
        autoreload(new QAction("Autoreload", this)),
        export_GCODE(new QAction("Export GCODE", this)),
        slicer(new QAction("Slicer", this)),
        recent(new QMenu("Open recent", this)),
        group_recent(new QActionGroup(this)),
        clear_recent(new QAction("Clear recent files", this)),
        printer_parameters(new QAction("View Printer Parameters", this)),

        watcher(new QFileSystemWatcher(this))

{
    setWindowTitle("Cylindrical Slicer");
    setAcceptDrops(true);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(2, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);

    QSurfaceFormat::setDefaultFormat(format);

    canvas = new Renderer(format, this);
    setCentralWidget(canvas);

    QObject::connect(watcher, &QFileSystemWatcher::fileChanged,
                     this, &Gui::on_watched_change_action);

    open->setShortcut(QKeySequence::Open);
    QObject::connect(open, &QAction::triggered,
                     this, &Gui::on_open_action);

    quit->setShortcut(QKeySequence::Quit);
    QObject::connect(quit, &QAction::triggered,
                     this, &Gui::close);

    autoreload->setCheckable(true);
    autoreload->setChecked(true);
    autoreload->setEnabled(false);
    QObject::connect(autoreload, &QAction::triggered,
            this, &Gui::on_autoreload_triggered);

    reload->setShortcut(QKeySequence::Refresh);
    reload->setEnabled(false);
    QObject::connect(reload, &QAction::triggered,
                     this, &Gui::on_reload);

    QObject::connect(about, &QAction::triggered,
                     this, &Gui::on_about_action);

    // Connects the slicer function to the slicer action
    QObject::connect(slicer, &QAction::triggered,
                     this, &Gui::on_slice_action);

    // Connects the export function to the export action
    QObject::connect(export_GCODE, &QAction::triggered,
                     this, &Gui::on_gcodeExport_action);

    QObject::connect(clear_recent, &QAction::triggered,
                     this, &Gui::on_clear_recent_files);
    QObject::connect(group_recent, &QActionGroup::triggered,
                     this, &Gui::on_load_recent_files);

    QObject::connect(printer_parameters, &QAction::triggered,
                      this, &Gui::on_printer_parameters_action);


    rebuild_recent_files();

    auto fileMenuBar = menuBar()->addMenu("File");
    fileMenuBar->addAction(open);
    fileMenuBar->addMenu(recent);
    fileMenuBar->addSeparator();
    fileMenuBar->addAction(reload);
    fileMenuBar->addAction(autoreload);
    fileMenuBar->addAction(quit);

    auto viewMenuBar = menuBar()->addMenu("View");
    auto projectionMenuBar = viewMenuBar->addMenu("Projection");
    projectionMenuBar->addAction(perspective);
    projectionMenuBar->addAction(orthogonal);
    auto projections = new QActionGroup(projectionMenuBar);
    for (auto p : {perspective, orthogonal})
    {
        projections->addAction(p);
        p->setCheckable(true);
    }
    perspective->setChecked(true);
    projections->setExclusive(true);
    QObject::connect(projections, &QActionGroup::triggered,
                     this, &Gui::on_projection_action);

    auto drawMenuBar = viewMenuBar->addMenu("Draw Mode");
    drawMenuBar->addAction(shaded);
    drawMenuBar->addAction(wireframe);
    auto drawModes = new QActionGroup(drawMenuBar);
    for (auto p : {shaded, wireframe})
    {
        drawModes->addAction(p);
        p->setCheckable(true);
    }
    shaded->setChecked(true);
    drawModes->setExclusive(true);
    QObject::connect(drawModes, &QActionGroup::triggered,
                     this, &Gui::on_drawMode_action);

    auto slicerMenuBar = menuBar()->addMenu("Slice");
    slicerMenuBar->addAction(slicer);

    auto printerMenuBar = menuBar()->addMenu("Printer Parameters");
    printerMenuBar->addAction(printer_parameters);

    auto exportMenuBar = menuBar()->addMenu("Export");
    exportMenuBar->addAction(export_GCODE);

    auto helpMenuBar = menuBar()->addMenu("Help");
    helpMenuBar->addAction(about);

    resize(600, 400);
}

void Gui::on_open_action()
{
    QString filename = QFileDialog::getOpenFileName(
            this, "Load .stl file", QString(), "*.stl");
    if (!filename.isNull())
    {
        load_stl_file(filename);
    }
}

void Gui::on_slice_action()
{
    canvas->set_sliced(true);
    print.convertMeshToTriangles(*(loader->get_mesh()));
    print.buildPrint();

    auto *wdg = new QWidget;
    //wdg->resize(200, 100);
    wdg->show();
    std::cout << "Number of slices: " << print.PrintSlices.size() << std::endl;
    createControls(tr("Controls"), print.PrintSlices.size() - 1);

    auto *layout = new QGridLayout;
    layout->addWidget(valueLabel, 0, 0);
    layout->addWidget(valueSpinBox, 1, 0);
    wdg->setLayout(layout);

    valueSpinBox->setValue(0);

    connect(valueSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &Gui::RenderSlice);

    setWindowTitle(tr("Slice View"));
}

void Gui::on_gcodeExport_action()
{
   	print.exportGcode();
}

void Gui::createControls(const QString &title, int max)
{
    controlsGroup = new QGroupBox(title);
    valueLabel = new QLabel(tr("Current value:"));
    valueSpinBox = new QSpinBox;
    valueSpinBox->setRange(0, max);
    valueSpinBox->setSingleStep(1);
}

void Gui::RenderSlice()
{
    canvas->set_slice(print.PrintSlices.at(valueSpinBox->value()).cartesianSegments);
    //print.PrintSlices.at(valueSpinBox->value()).cartesianSegments;
    //std::cout << valueSpinBox->value() << std::endl;
}

void Gui::on_printer_parameters_action()
{     
    QMessageBox msgBox;
    bool ok;


    QString bed_length = QInputDialog::getText(this, "",
                                         "Print Bed Length (mm): ", QLineEdit::Normal,
                                         "", &ok);
    QString bed_radius = QInputDialog::getText(this, "",
                                         "Print Bed Radius (mm): ", QLineEdit::Normal,
                                         "", &ok);
    QString filament_diameter = QInputDialog::getText(this, "",
                                         "Filament Diameter (mm): ", QLineEdit::Normal,
                                         "", &ok); 
    QString extruder_temp = QInputDialog::getText(this, "",
                                         "Extruder Tempature (C): ", QLineEdit::Normal,
                                         "", &ok);      
    QString bed_temp = QInputDialog::getText(this, "",
                                         "Bed Tempature (C): ", QLineEdit::Normal,
                                         "", &ok);           
    QString z_offset = QInputDialog::getText(this, "",
                                         "Z Offset (mm): ", QLineEdit::Normal,
                                         "", &ok);
    QString layer_height = QInputDialog::getText(this, "",
                                         "Layer Height (mm): ", QLineEdit::Normal,
                                         "", &ok);
    QString first_layer_height = QInputDialog::getText(this, "",
                                         "First Layer Height (mm): ", QLineEdit::Normal,
                                         "", &ok);
    QString travel_speed = QInputDialog::getText(this, "",
                                         "Travel (mm/s): ", QLineEdit::Normal,
                                         "", &ok);      
    QString first_layer_speed = QInputDialog::getText(this, "",
                                         "First Layer Speed (mm/s): ", QLineEdit::Normal,
                                         "", &ok);  
    QString print_speed = QInputDialog::getText(this, "",
                                         "Print Speed (mm/s): ", QLineEdit::Normal,
                                         "", &ok);                                                   
    params.bed_length = bed_length.toFloat();
    params.bed_radius = bed_radius.toFloat();


    msgBox.setText("<b>Cylindrical Slicer Printer Parameters</b>");
    msgBox.setInformativeText("Print Bed Length (X-Axis): " + bed_length + " mm\n" +
                           "Bed Radius (Y-Axis): " + bed_radius + " mm\n" +
                           "Bed Layer Thickness (Z-Axis): " + filament_diameter + " mm\n" +
                           "Extruder Temperature: " + extruder_temp + " °C\n" +
                           "Bed Temperature: " + bed_temp + " °C\n" +
                           "Z Offset: " + z_offset + " mm\n" +
                           "Layer Height: " + layer_height + " mm\n" +
                           "First Layer Height: " + first_layer_height + " mm\n" +
                           "Travel Speed: " + travel_speed + " mm/s\n" +
                           "First Layer Speed: " + first_layer_speed + " mm/s\n" +
                           "Print Speed: " + print_speed + " mm/s\n\n");

    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    
    int ret = msgBox.exec();
}

void Gui::on_about_action()
{
    QMessageBox::about(this, "",
        "<p align=\"center\"><b>Cylindrical Slicer About</b></p>"
        "<p>A slicer for a cylindrical bed 3D printer.<br>"
        "<a href=\"https://github.com/ryan-tech/Cylindrical-Slicer\""
        "   style=\"color: #93a1a1;\">https://github.com/ryan-tech/Cylindrical-Slicer</a></p>"
        "<p>Email:<br>"
        "<a href=\"mailto:rkim@nevada.unr.edu\""
        "   style=\"color: #93a1a1;\">rkim@nevada.unr.edu</a></p>");
}

void Gui::on_bad_stl_action()
{
    QMessageBox::critical(this, "Error",
                          "<b>Error: This stl file is invalid.</b>");
}

void Gui::on_empty_mesh_action()
{
    QMessageBox::critical(this, "Error",
                          "<b>Error: This stl file is has no meshes.</b>");
}

void Gui::on_confusing_stl_action()
{
    QMessageBox::warning(this, "Warning",
                         "This stl file has a confusing format.");
}

void Gui::on_missing_file_action()
{
    QMessageBox::critical(this, "Error",
                          "<b>Error: The selected file is missing. </b>");
}

void Gui::enable_open()
{
    open->setEnabled(true);
}

void Gui::disable_open()
{
    open->setEnabled(false);
}

void Gui::set_watched_action(const QString& file_name)
{
    const auto files = watcher->files();
    if (files.empty())
    {
        watcher->removePaths(watcher->files());
    }
    watcher->addPath(file_name);

    auto recent_files_list = s.value(RECENT_KEY).toStringList();
    const auto f = QFileInfo(file_name).absoluteFilePath();
    recent_files_list.removeAll(f);
    recent_files_list.prepend(f);
    while (recent_files_list.size() > MAX_RECENT_NUM)
    {
        recent_files_list.pop_back();
    }
    s.setValue(RECENT_KEY, recent_files_list);
    rebuild_recent_files();
}

void Gui::on_projection_action(QAction* proj)
{
    if (proj == perspective)
    {
        canvas->perspective_view();
    }
    else
    {
        canvas->orthographic_view();
    }
}

void Gui::on_drawMode_action(QAction* mode)
{
    if (mode == shaded)
    {
        canvas->render_shaded_shader();
    }
    else
    {
        canvas->render_wireframe_shader();
    }
}

void Gui::on_watched_change_action(const QString& filename)
{
    if (autoreload->isChecked())
    {
        load_stl_file(filename, true);
    }
}

void Gui::on_autoreload_triggered(bool b)
{
    if (b)
    {
        on_reload();
    }
}

void Gui::on_clear_recent_files()
{
    s.setValue(RECENT_KEY, QStringList());;
    rebuild_recent_files();
}

void Gui::on_load_recent_files(QAction* a)
{
    load_stl_file(a->data().toString());
}

void Gui::on_loaded(const QString& filename)
{
    current_file = filename;
}

void Gui::rebuild_recent_files()
{
    QStringList files = s.value(RECENT_KEY).toStringList();

    const auto actions = group_recent->actions();
    for (auto a : actions)
    {
        group_recent->removeAction(a);
    }
    recent->clear();

    for (auto const &f : files)
    {
        const auto a = new QAction(f, recent);
        a->setData(f);
        group_recent->addAction(a);
        recent->addAction(a);
    }
    if (files.empty())
    {
        auto a = new QAction("Recent files empty.", recent);
        recent->addAction(a);
        a->setEnabled(false);
    }
    recent->addSeparator();
    recent->addAction(clear_recent);
}

void Gui::on_reload()
{
    auto fs = watcher->files();
    if (fs.size() == 1)
    {
        load_stl_file(fs[0], true);
    }
}

bool Gui::load_stl_file(const QString& filename, bool is_reload)
{
    if (!open->isEnabled())  return false;

    canvas->setStatus("Loading " + filename);

    loader = new Parser(this, filename, is_reload);
    connect(loader, &Parser::started,
              this, &Gui::disable_open);

    connect(loader, &Parser::got_mesh,
            canvas, &Renderer::load_mesh);
    connect(loader, &Parser::error_bad_stl,
              this, &Gui::on_bad_stl_action);
    connect(loader, &Parser::error_empty_mesh,
              this, &Gui::on_empty_mesh_action);
    connect(loader, &Parser::warning_confusing_stl,
              this, &Gui::on_confusing_stl_action);
    connect(loader, &Parser::error_missing_file,
              this, &Gui::on_missing_file_action);

    connect(loader, &Parser::finished,
            loader, &Parser::deleteLater);
    connect(loader, &Parser::finished,
              this, &Gui::enable_open);
    connect(loader, &Parser::finished,
            canvas, &Renderer::clearStatus);

    if (filename[0] != ':')
    {
        connect(loader, &Parser::loaded_file,
                  this, &Gui::setWindowTitle);
        connect(loader, &Parser::loaded_file,
                  this, &Gui::set_watched_action);
        connect(loader, &Parser::loaded_file,
                  this, &Gui::on_loaded);
        autoreload->setEnabled(true);
        reload->setEnabled(true);
    }
    loader->start();

    return true;
}

//void Gui::dragEnterEvent(QDragEnterEvent *event)
//{
//    if (event->mimeData()->hasUrls())
//    {
//        auto urls = event->mimeData()->urls();
//        if (urls.size() == 1 && urls.front().path().endsWith(".stl"))
//            event->acceptProposedAction();
//    }
//}
//
//void Gui::dropEvent(QDropEvent *event)
//{
//    load_stl_file(event->mimeData()->urls().front().toLocalFile());
//}
