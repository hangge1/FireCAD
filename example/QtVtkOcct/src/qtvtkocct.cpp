#include "qtvtkocct.h"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkConeSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <BRepPrimAPI_MakeBox.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>
#include <IVtkTools_ShapePicker.hxx>

#include "layers/makeBoxTest.h"

#include "vtkOutputWindow.h"

QtVtkOcct::QtVtkOcct(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
	initWidget();
	initLayers();
	runTestLayers();
}

QtVtkOcct::~QtVtkOcct()
{
	destroyLayers();
}

void QtVtkOcct::initWidget()
{
	vtkOutputWindow::SetGlobalWarningDisplay(0);
	vtkWidget = new QVTKOpenGLNativeWidget(this);
	setCentralWidget(vtkWidget);
	resize(800, 600);
}

void QtVtkOcct::initLayers()
{
	auto boxTest = new makeBoxTest("MakeBox");
	boxTest->setRenderWindow(vtkWidget->renderWindow());
	//boxTest->setDisplayMode(DM_Wireframe);
	testLayers_.push_back(boxTest);
}

void QtVtkOcct::runTestLayers()
{
	for (const auto layer : testLayers_)
	{
		layer->attach();
	}
}

void QtVtkOcct::destroyLayers()
{
	for (const auto layer : testLayers_)
	{
		layer->detach();
	}
}


