#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_qtvtkocct.h"

#include <IVtk_Types.hxx>
#include <QVector>

class QVTKOpenGLNativeWidget;
class occLayer;
class QDockWidget;
class QPushButton;
class LayerManagerControl;

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
    //Ui::QtVtkOcctClass ui;
    QVector<occLayer*> testLayers_;
    QVTKOpenGLNativeWidget* vtkWidget_;
    QDockWidget* controlDock_;
    LayerManagerControl* layoutManagerWidget_;
};

