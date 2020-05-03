#include <QDebug>
#include <QFileOpenEvent>

#include "app.h"


App::App(int& argc, char *argv[]) :
        QApplication(argc, argv), gui(new Gui())
{
    QCoreApplication::setOrganizationName("Team23");
    QCoreApplication::setOrganizationDomain("https://github.com/ryan-tech/Cylindrical-Slicer");
    QCoreApplication::setApplicationName("Cylindrical Slicer");

    if (argc > 1)
        gui->load_stl_file(argv[1]);
    else
        gui->load_stl_file(":gl_files/default.stl");
    gui->show();
}

App::~App()
{
	delete gui;
}

bool App::event(QEvent* event)
{
    if (event->type() == QEvent::FileOpen)
    {
        gui->load_stl_file(dynamic_cast<QFileOpenEvent *>(event)->file());
        return true;
    }
    else
    {
        return QApplication::event(event);
    }
}
