#pragma once

#include <string>
#include "vtkSmartPointer.h"
#include "IVtk_Types.hxx"

class IVtkTools_DisplayModeFilter;
class IVtkTools_ShapeDataSource;
class vtkRenderWindow;
class vtkRenderer;
class vtkActor;
class vtkPolyDataMapper;
class TopoDS_Shape;


class occLayer
{
public:
    occLayer();
    occLayer(const std::string& test_name);
    occLayer(const occLayer&) = delete;
    occLayer& operator=(const occLayer&) = delete;
    occLayer(occLayer&&) = delete;
    occLayer& operator=(occLayer&&) = delete;
    virtual ~occLayer();

    void setRenderWindow(vtkRenderWindow* render_window);
    void setShape(const TopoDS_Shape& shape);
    void setDisplayMode(IVtk_DisplayMode display_mode);
    void attach();
    void detach();

protected:
    virtual void preInit();
    virtual void init() = 0;
    virtual void initMapperColor();
    virtual void reset();
protected:
    vtkSmartPointer<vtkRenderer> renderer_ {};
    vtkSmartPointer<vtkActor> actor_ {};
    vtkSmartPointer<vtkPolyDataMapper> mapper_ {};
    vtkSmartPointer<IVtkTools_DisplayModeFilter> display_mode_filter_ {};
    vtkSmartPointer<IVtkTools_ShapeDataSource> occ_source_ {};
    std::string layer_name_;
    vtkRenderWindow* render_window_ {};
    bool is_init_ { false };
    IVtk_DisplayMode display_mode_{ DM_Shading };
};
