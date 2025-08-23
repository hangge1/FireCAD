#include "qtvtkocct.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtVtkOcct window;
    window.show();
    return app.exec();
}
