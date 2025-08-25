#include "layers/occLayer.h"

#include <cassert>

#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "IVtkTools_DisplayModeFilter.hxx"
#include "IVtkTools_ShapeDataSource.hxx"
#include "IVtkOCC_Shape.hxx"
#include "TopoDS_Shape.hxx"

#define DefaultLayerName "DefaultLayer"

occLayer::occLayer()
    : occLayer(DefaultLayerName)
{

}

occLayer::occLayer(const QString& layer_name)
    : layer_name_(layer_name)
{
}

occLayer::~occLayer()
{
}

QString occLayer::getName() const
{
    return layer_name_;
}

void occLayer::setRenderWindow(vtkRenderWindow* render_window)
{
    assert(render_window);
    render_window_ = render_window;
}


void occLayer::preInit()
{
    if(is_init_) return;

    occ_source_ = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
    display_mode_filter_ = vtkSmartPointer<IVtkTools_DisplayModeFilter>::New();
    display_mode_filter_->SetDisplayMode(display_mode_);

    mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
    initMapperColor();

    actor_ = vtkSmartPointer<vtkActor>::New();
    renderer_ = vtkSmartPointer<vtkRenderer>::New();

    display_mode_filter_->SetInputConnection(occ_source_->GetOutputPort());
    mapper_->SetInputConnection(display_mode_filter_->GetOutputPort());
    actor_->SetMapper(mapper_);
    renderer_->AddActor(actor_);
    render_window_->AddRenderer(renderer_);

    is_init_ = true;
}

void occLayer::initMapperColor()
{
    assert(mapper_);
    IVtkTools::InitShapeMapper(mapper_);
}

void occLayer::reset()
{
    render_window_->RemoveRenderer(renderer_);
    renderer_->RemoveAllViewProps();
    renderer_ = nullptr;
    actor_ = nullptr;
    mapper_ = nullptr;
    display_mode_filter_ = nullptr;
    occ_source_ = nullptr;
    layer_name_ = "";
    display_mode_ = DM_Shading;
    is_init_ = false;
}

void occLayer::setShape(const TopoDS_Shape& shape)
{
	assert(is_init_);
	assert(occ_source_);
    occ_source_->SetShape(new IVtkOCC_Shape(shape));
}

void occLayer::setDisplayMode(IVtk_DisplayMode display_mode)
{
    display_mode_ = display_mode;
}

void occLayer::attach()
{
    if(!is_init_)
    {
        preInit();
    }
    init();
}

void occLayer::detach()
{
    if (!is_init_) return;

    reset();
}