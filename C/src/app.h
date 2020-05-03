#ifndef APP_H
#define APP_H

#include <QApplication>
//#include "canvas.h"
#include "gui.h"

class Gui;

class App : public QApplication
{
    Q_OBJECT
public:
    explicit App(int& argc, char *argv[]);
	~App();
protected:
    bool event(QEvent* event) override;
private:
    Gui* const gui;

};

#endif // APP_H
