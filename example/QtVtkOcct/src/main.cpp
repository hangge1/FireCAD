#include "qtvtkocct.h"
#include <QtWidgets/QApplication>
#include <QVTKOpenGLNativeWidget.h>

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication app(argc, argv);
    QtVtkOcct window;
    window.show();
    return app.exec();
}
