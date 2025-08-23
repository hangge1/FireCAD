#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_qtvtkocct.h"

class QVTKOpenGLNativeWidget;

class QtVtkOcct : public QMainWindow
{
    Q_OBJECT

public:
    QtVtkOcct(QWidget *parent = nullptr);
    ~QtVtkOcct();

private:
    //Ui::QtVtkOcctClass ui;

    QVTKOpenGLNativeWidget* vtkWidget;
};

