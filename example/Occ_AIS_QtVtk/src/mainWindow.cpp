#include "mainWindow.h"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkConeSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <BRepPrimAPI_MakeBox.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>
#include <vtkOutputWindow.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/icons/resource/QtVtkOcct.ico")); 
	initWidget();
    initVTK();
    test();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initWidget()
{
	vtkOutputWindow::SetGlobalWarningDisplay(0);
	vtkWidget_ = new QVTKOpenGLNativeWidget(this);
	setCentralWidget(vtkWidget_);
	vtkNew<vtkGenericOpenGLRenderWindow> window;
	vtkWidget_->setRenderWindow(window.Get());
}

void MainWindow::initVTK()
{
    occ_source_ = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
    display_mode_filter_ = vtkSmartPointer<IVtkTools_DisplayModeFilter>::New();

    render_window_ = vtkWidget_->renderWindow();
    mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor_ = vtkSmartPointer<vtkActor>::New();
    renderer_ = vtkSmartPointer<vtkRenderer>::New();

    display_mode_filter_->SetInputConnection(occ_source_->GetOutputPort());
    mapper_->SetInputConnection(display_mode_filter_->GetOutputPort());
    actor_->SetMapper(mapper_);
    renderer_->AddActor(actor_);
    render_window_->AddRenderer(renderer_);
}

void MainWindow::test()
{
    BRepPrimAPI_MakeBox box(2, 2, 2);
    const TopoDS_Shape& shape = box.Shape();
    occ_source_->SetShape(new IVtkOCC_Shape(shape));
}