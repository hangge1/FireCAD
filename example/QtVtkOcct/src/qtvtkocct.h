#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_qtvtkocct.h"

#include <IVtk_Types.hxx>
#include <vector>

class QVTKOpenGLNativeWidget;
class occLayer;

class QtVtkOcct : public QMainWindow
{
    Q_OBJECT

public:
    QtVtkOcct(QWidget *parent = nullptr);
    ~QtVtkOcct();

protected:
    void initWidget();
    void initLayers();
    void runTestLayers();
    void destroyLayers();

private:

    std::vector<occLayer*> testLayers_;
private:
    //Ui::QtVtkOcctClass ui;

    QVTKOpenGLNativeWidget* vtkWidget;
};

