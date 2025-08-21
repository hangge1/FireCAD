#include <BRepPrimAPI_MakeBox.hxx>
#include <IVtkTools_ShapeDataSource.hxx>

#include <vtkAutoInit.h>
#include <vtkRenderer.h>
#include <VtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>

int main()
{
    BRepPrimAPI_MakeBox box(2, 2, 2);
    const TopoDS_Shape& shape = box.Shape();

    vtkNew<vtkRenderWindow> renderWindow;
    vtkNew<vtkRenderer> render;
    renderWindow->AddRenderer(render);

    vtkNew<vtkRenderWindowInteractor> iren;
    vtkNew<vtkInteractorStyleTrackballCamera> istyle;

    iren->SetRenderWindow(renderWindow);
    iren->SetInteractorStyle(istyle);

    vtkNew<IVtkTools_ShapeDataSource> occSource;
    occSource->SetShape(new IVtkOCC_Shape(shape));

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(occSource->GetOutputPort());
    
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    render->AddActor(actor);

    iren->Initialize();
    iren->Start();

    return 0;
}
