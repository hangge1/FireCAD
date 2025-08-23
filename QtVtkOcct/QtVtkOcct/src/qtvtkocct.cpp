#include "qtvtkocct.h"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkConeSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <BRepPrimAPI_MakeBox.hxx>
#include <IVtkTools_ShapeDataSource.hxx>

QtVtkOcct::QtVtkOcct(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);

    vtkWidget = new QVTKOpenGLNativeWidget(this);
	setCentralWidget(vtkWidget);


	//addConeTest();
	addOccBoxTest();

}

QtVtkOcct::~QtVtkOcct()
{}

void QtVtkOcct::addConeTest()
{
	vtkNew<vtkConeSource> cone;
	cone->SetHeight(3.0);
	cone->SetRadius(1.0);
	cone->SetResolution(10);

	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputConnection(cone->GetOutputPort());

	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);

	vtkNew<vtkRenderer> render;
	render->AddActor(actor);

	auto renderWindow = vtkWidget->renderWindow();
	renderWindow->AddRenderer(render);
}

void QtVtkOcct::addOccBoxTest()
{
	BRepPrimAPI_MakeBox box(2, 2, 2);
	const TopoDS_Shape& shape = box.Shape();

	vtkNew<IVtkTools_ShapeDataSource> occSource;
	occSource->SetShape(new IVtkOCC_Shape(shape));

	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputConnection(occSource->GetOutputPort());

	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);

	vtkNew<vtkRenderer> render;
	render->AddActor(actor);

	auto renderWindow = vtkWidget->renderWindow();
	renderWindow->AddRenderer(render);
}

