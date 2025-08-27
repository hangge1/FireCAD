#pragma once

#include <QtWidgets/QMainWindow>
#include "vtkSmartPointer.h"

class QVTKOpenGLNativeWidget;
class vtkRenderer;
class vtkActor;
class vtkPolyDataMapper;
class IVtkTools_DisplayModeFilter;
class IVtkTools_ShapeDataSource;
class vtkRenderWindow;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void initWidget();
    void initVTK();
    void test();

private:
    QVTKOpenGLNativeWidget* vtkWidget_;
    vtkRenderWindow* render_window_{};

    vtkSmartPointer<IVtkTools_ShapeDataSource> occ_source_{};
    vtkSmartPointer<IVtkTools_DisplayModeFilter> display_mode_filter_{};
    vtkSmartPointer<vtkPolyDataMapper> mapper_{};
    vtkSmartPointer<vtkActor> actor_{};
    vtkSmartPointer<vtkRenderer> renderer_{}; 
};

