

#include "layers/makeBoxTest.h"
#include <BRepPrimAPI_MakeBox.hxx>


void makeBoxTest::makeBox()
{
    BRepPrimAPI_MakeBox box(2, 2, 2);
	const TopoDS_Shape& shape = box.Shape();
    setShape(shape);
}

void makeBoxTest::init()
{
    makeBox();
}
