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

#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "layermanagercontrol.h"

QtVtkOcct::QtVtkOcct(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
	initWidget();
	initLayers();

	layoutManagerWidget_->setLayers(testLayers_);
	layoutManagerWidget_->loadLayers();
	//runTestLayers();
}

QtVtkOcct::~QtVtkOcct()
{
	destroyLayers();
}

void QtVtkOcct::initWidget()
{
	vtkOutputWindow::SetGlobalWarningDisplay(0);

	controlDock_ = new QDockWidget(this);
	addDockWidget(Qt::LeftDockWidgetArea ,controlDock_);

	QVBoxLayout* dockLayout = new QVBoxLayout();
	layoutManagerWidget_ = new LayerManagerControl(this);
	layoutManagerWidget_->setLayout(dockLayout);
	controlDock_->setWidget(layoutManagerWidget_);


	vtkWidget_ = new QVTKOpenGLNativeWidget(this);
	setCentralWidget(vtkWidget_);

	vtkNew<vtkGenericOpenGLRenderWindow> window;
	vtkWidget_->setRenderWindow(window.Get());


	resize(800, 600);
}

void QtVtkOcct::initLayers()
{
	auto boxTest = new makeBoxTest("MakeBox");
	boxTest->setRenderWindow(vtkWidget_->renderWindow());
	//boxTest->setDisplayMode(DM_Wireframe);
	testLayers_.push_back(boxTest);

	auto boxTest2 = new makeBoxTest("MakeBox");
	boxTest2->setRenderWindow(vtkWidget_->renderWindow());
	//boxTest->setDisplayMode(DM_Wireframe);
	testLayers_.push_back(boxTest2);
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


