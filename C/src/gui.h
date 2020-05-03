#ifndef GUI_H
#define GUI_H

#include <QFileSystemWatcher>
#include <QMainWindow>
#include <QActionGroup>

#include <iostream>
#include <QCollator>
#include "PrintParameters.h"
#include "ModelPrint.cpp"

#include <QMenuBar>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QLabel;
class QSpinBox;
QT_END_NAMESPACE

#include "mesh.h"
#include "parser.h"

class Renderer;
struct ModelPrint;

class Gui : public QMainWindow
{
    Q_OBJECT
public:
    explicit Gui(QWidget* parent= nullptr);
    bool load_stl_file(const QString& filename, bool is_reload= false);

protected:
    //void dragEnterEvent(QDragEnterEvent* event) override;
    //void dropEvent(QDropEvent* event) override;

public slots:
    void on_open_action();
    void on_about_action();
    void on_bad_stl_action();
    void on_empty_mesh_action();
    void on_missing_file_action();
    void on_confusing_stl_action();

    void on_printer_parameters_action();

    void on_slice_action();
    void on_gcodeExport_action();

    void enable_open();
    void disable_open();

    void set_watched_action(const QString& file_name);

private slots:
    void on_projection_action(QAction* proj);
    void on_drawMode_action(QAction* mode);
    void on_watched_change_action(const QString& filename);
    void on_reload();
    void on_autoreload_triggered(bool r);
    void on_clear_recent_files();
    void on_load_recent_files(QAction* a);
    void on_loaded(const QString& filename);
	
private:
    void rebuild_recent_files();


    /*
     * Add a QAction* const variable here for the menu bar
     * */
    QAction* const open;
    QAction* const about;
    QAction* const quit;
    QAction* const perspective;
    QAction* const orthogonal;
    QAction* const shaded;
    QAction* const wireframe;
    QAction* const reload;
    QAction* const autoreload;
    QAction* const export_GCODE;
    QAction* const slicer;
    QAction* const printer_parameters;
    QLabel *valueLabel{};
    QSettings s;
    QMenu* const recent;
    QActionGroup* const group_recent;
    QAction* const clear_recent;
    const static int MAX_RECENT_NUM=8;
    const static QString RECENT_KEY;
    QString current_file;
    QSpinBox *valueSpinBox{};
    QGroupBox *controlsGroup{};
    QFileSystemWatcher* watcher;

    Renderer* canvas;
    Parser* loader{};
    ModelPrint print;

    PrintParameters params;
    void createControls(const QString &title, int max);


    void RenderSlice();
};

#endif