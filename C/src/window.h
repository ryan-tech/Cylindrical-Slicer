#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QFileSystemWatcher>
#include <QCollator>
#include <QMenuBar>
#include <iostream>

#include "canvas.h"
#include "ModelPrint.cpp"

QT_BEGIN_NAMESPACE
class QGroupBox;
class QLabel;
class QSpinBox;
QT_END_NAMESPACE

#include "mesh.h"
#include "loader.h"
#include "SlidersGroup.h"


class Canvas;

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget* parent= nullptr);
    bool load_stl(const QString& filename, bool is_reload=false);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

public slots:
    void on_open();
    void on_about();
    void on_bad_stl();
    void on_empty_mesh();
    void on_missing_file();
    void on_confusing_stl();

    void on_slice();
    void on_gcodeExport();

    void enable_open();
    void disable_open();

    void set_watched(const QString& filename);

private slots:
    void on_projection(QAction* proj);
    void on_drawMode(QAction* mode);
    void on_watched_change(const QString& filename);
    void on_reload();
    void on_autoreload_triggered(bool r);
    void on_clear_recent();
    void on_load_recent(QAction* a);
    void on_loaded(const QString& filename);
	
private:
    void rebuild_recent_files();


    /* When creating actions, follow the naming scheme by following the name with an _action.
     *
     * Add a QAction* const variable here for the menu bar
     * */
    QAction* const open_action;
    QAction* const about_action;
    QAction* const quit_action;
    QAction* const perspective_action;
    QAction* const orthogonal_action;
    QAction* const shaded_action;
    QAction* const wireframe_action;
    QAction* const reload_action;
    QAction* const autoreload_action;
    QAction* const export_GCODE_action;
    QAction* const slicer_action;

    QMenu* const recent_files;
    QActionGroup* const recent_files_group;
    QAction* const recent_files_clear_action;
    const static int MAX_RECENT_FILES=8;
    const static QString RECENT_FILE_KEY;
    QString current_file;

    QFileSystemWatcher* watcher;

    Canvas* canvas;
    Loader* loader;
    ModelPrint print;

    void createControls(const QString &title, int max);

    QLabel *valueLabel;
    QSpinBox *valueSpinBox;
    QGroupBox *controlsGroup;
    void RenderSlice();
};

#endif // WINDOW_H
