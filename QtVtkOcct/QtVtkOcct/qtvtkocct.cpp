#include "qtvtkocct.h"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkConeSource.h>
#include <vtkGenericOpenGLRenderWindow.h>

QtVtkOcct::QtVtkOcct(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);

    vtkWidget = new QVTKOpenGLNativeWidget(this);
	setCentralWidget(vtkWidget);


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

QtVtkOcct::~QtVtkOcct()
{}

