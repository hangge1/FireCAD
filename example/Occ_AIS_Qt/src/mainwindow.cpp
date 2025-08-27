#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     _devPx(devicePixelRatio())
{
    initMenuToolbar();
    initOCCTView();
    initSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initMenuToolbar()
{
    setWindowTitle("Occ_AIS_Qt");
    setWindowIcon(QIcon(":/icons/resource/QtVtkOcct.ico"));

    tb_view = new QToolBar(this);
    //tb_view->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(tb_view);

    act_hideAll = new QAction(QIcon(":/icons/resource/hideAll.png"), "hideAll", this);
    act_hide = new QAction(QIcon(":/icons/resource/hide.png"), "hide", this);
    act_fitAll = new QAction(QIcon(":/icons/resource/view-fullscreen.svg"), "fitAll", this);
    act_axo = new QAction(QIcon(":/icons/resource/view-axonometric.svg"), "axo", this);
    act_top = new QAction(QIcon(":/icons/resource/view-top.svg"), "top", this);
    act_buttom = new QAction(QIcon(":/icons/resource/view-bottom.svg"), "buttom", this);
    act_left = new QAction(QIcon(":/icons/resource/view-left.svg"), "left", this);
    act_right = new QAction(QIcon(":/icons/resource/view-right.svg"), "right", this);
    act_front = new QAction(QIcon(":/icons/resource/view-front.svg"), "front", this);
    act_back = new QAction(QIcon(":/icons/resource/view-rear.svg"), "back", this);
    act_shade = new QAction(QIcon(":/icons/resource/DrawStyleShaded.svg"), "shade", this);
    act_wireframe = new QAction(QIcon(":/icons/resource/DrawStyleWireFrame.svg"), "wireframe", this);
    act_axis = new QAction(QIcon(":/icons/resource/axis.png"), "axis", this);
    act_test = new QAction(QIcon(":/icons/resource/utilities-terminal.svg"), "test", this);


    tb_view->addActions({ act_hideAll,act_hide,act_fitAll,act_axo,
    act_top,act_buttom,act_left,act_right,act_front,act_back });
    tb_view->addSeparator();
    tb_view->addActions({ act_shade,act_wireframe,act_axis,act_test });

    tb_style = new QToolBar(this);
    addToolBar(tb_style);
    addToolBarBreak();

    act_color = new QAction(QIcon(":/icons/resource/colors.svg"), "color", this);
    act_material = new QAction(QIcon(":/icons/resource/Material.svg"), "material", this);

    actgp_selectMode = new QActionGroup(this);
    actgp_selectMode->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);
    act_selectVertex = new QAction(QIcon(":/icons/resource/vertex-selection.svg"), "selectVertex", this);

    act_selectVertex->setCheckable(true);
    act_selectEdge = new QAction(QIcon(":/icons/resource/edge-selection.svg"), "selectEdge", this);
    act_selectEdge->setCheckable(true);
    act_selectFace = new QAction(QIcon(":/icons/resource/face-selection.svg"), "selectFace", this);
    act_selectFace->setCheckable(true);

    tb_style->addActions({ act_color,act_material });
    tb_style->addSeparator();
    tb_style->addActions({ act_selectVertex, act_selectEdge, act_selectFace });

    stb = new QStatusBar(this);
    this->setStatusBar(stb);
    lb_positionInfo = new QLabel(this);
    stb->addWidget(lb_positionInfo);
}

void MainWindow::initOCCTView()
{
    myViewer = Viewer(V3d_XposYnegZpos);
    myContext = new AIS_InteractiveContext(myViewer);
    view_occt = new View(myContext, this);
    view_occt->installEventFilter(this);
    setCentralWidget(view_occt);
}

void MainWindow::initSignals()
{
    connect(act_hideAll, &QAction::triggered, view_occt, &View::removeAll);
    connect(act_hide, &QAction::triggered, view_occt, &View::remove);
    connect(act_fitAll, &QAction::triggered, view_occt, &View::fitAll);
    connect(act_axo, &QAction::triggered, view_occt, &View::setAxo);
    connect(act_top, &QAction::triggered, view_occt, &View::setTop);
    connect(act_buttom, &QAction::triggered, view_occt, &View::setBottom);
    connect(act_left, &QAction::triggered, view_occt, &View::setLeft);
    connect(act_right, &QAction::triggered, view_occt, &View::setRight);
    connect(act_front, &QAction::triggered, view_occt, &View::setFront);
    connect(act_back, &QAction::triggered, view_occt, &View::setBack);

    connect(act_shade, &QAction::triggered, view_occt, &View::setShading);
    connect(act_wireframe, &QAction::triggered, view_occt, &View::setWireframe);
    connect(act_axis, &QAction::triggered, view_occt, &View::setAxis);
    connect(act_test, &QAction::triggered, this, &MainWindow::test);

    connect(act_selectVertex, &QAction::triggered, this, &MainWindow::setSelectMode);
    connect(act_selectEdge, &QAction::triggered, this, &MainWindow::setSelectMode);
    connect(act_selectFace, &QAction::triggered, this, &MainWindow::setSelectMode);
}

void MainWindow::test()
{
    TopoDS_Shape aShape = BRepPrimAPI_MakeBox(100, 200, 400);
    Handle(AIS_InteractiveObject) ais = new AIS_Shape(aShape);
    myContext->Display(ais, 1, 0, false);

    view_occt->fitAll();
}

void MainWindow::setSelectMode()
{
    bool checkVertex = act_selectVertex->isChecked();
    bool checkEdge = act_selectEdge->isChecked();
    bool checkFace = act_selectFace->isChecked();

    myContext->Deactivate();
    if (checkVertex && !checkEdge && !checkFace)
    {
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_VERTEX));
    }
    else if (!checkVertex && checkEdge && !checkFace)
    {
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_EDGE));
    }
    else if (!checkVertex && !checkEdge && checkFace)
    {
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_FACE));
    }
    else if (checkVertex && checkEdge && !checkFace)
    {
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_VERTEX));
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_EDGE));
    }
    else if (checkVertex && !checkEdge && checkFace)
    {
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_VERTEX));
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_FACE));
    }
    else if (!checkVertex && checkEdge && checkFace)
    {
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_EDGE));
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_FACE));
    }
    else if (checkVertex && checkEdge && checkFace)
    {
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_VERTEX));
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_EDGE));
        myContext->Activate(AIS_Shape::SelectionMode(TopAbs_FACE));
    }
    else
    {
        myContext->Activate(0);
    }
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* theEvent = static_cast<QMouseEvent*>(event);
        Qt::MouseButtons aMouseButtons = theEvent->buttons();
        myClickPos = { _devPx * theEvent->pos().x() , _devPx * theEvent->pos().y() };
        updateStatusBar(myClickPos);
    }

    return QMainWindow::eventFilter(watched, event);
}

Handle(V3d_Viewer) MainWindow::Viewer(const V3d_TypeOfOrientation theViewProj)
{
    static Handle(OpenGl_GraphicDriver) aGraphicDriver;
    Handle(Aspect_DisplayConnection) aDisplayConnection;
    aGraphicDriver = new OpenGl_GraphicDriver(aDisplayConnection);
    Handle(V3d_Viewer) aViewer = new V3d_Viewer(aGraphicDriver);
    aViewer->SetDefaultViewProj(theViewProj);

    aViewer->SetDefaultLights();
    aViewer->SetLightOn();
    return aViewer;
}

void MainWindow::updateStatusBar(const std::vector<double>& aNewPos)
{
    double XScreen = aNewPos[0];
    double YScreen = aNewPos[1];

    double x, y, z;
    view_occt->getView()->Convert(XScreen, YScreen, x, y, z);
    gp_Pnt worldPnt = gp_Pnt(x, y, z);

    double xEye, yEye, zEye, xAt, yAt, zAt;
    view_occt->getView()->Eye(xEye, yEye, zEye);
    view_occt->getView()->At(xAt, yAt, zAt);
    gp_Pnt eyePoint(xEye, yEye, zEye);
    gp_Pnt atPoint(xAt, yAt, zAt);

    gp_Dir eyeDir(gp_Vec(eyePoint, atPoint));
    gp_Pln plnAt = gp_Pln(atPoint, eyeDir);

    Handle(Geom_Plane) geoPlane = new Geom_Plane(plnAt);
    GeomAPI_ProjectPointOnSurf project(worldPnt, geoPlane);
    gp_Pnt position = project.NearestPoint();


    // 同上
    //gp_Pnt2d ConvertedPointOnPlane = ProjLib::Project(plnAt , worldPnt);
    //gp_Pnt position1 = ElSLib::Value(ConvertedPointOnPlane.X() , ConvertedPointOnPlane.Y() , plnAt);
    //QString positionInfo1 = QString("Position: %0, %1, %2").arg(position1.X()).arg(position1.Y()).arg(position1.Z());

    //QString screenPntInfo = QString("Screen: %0, %1").arg(XScreen).arg(YScreen);
    //QString worldPntInfo = QString("World: %0, %1, %2").arg(x).arg(y).arg(z);
    //QString eyePntInfo = QString("Eye: %0, %1, %2").arg(xEye).arg(yEye).arg(zEye);
    //QString atPntInfo = QString("At: %0, %1, %2").arg(xAt).arg(yAt).arg(zAt);
    QString positionInfo = QString("WCS: %0, %1, %2").arg(position.X()).arg(position.Y()).arg(position.Z());
    //QString info = screenPntInfo + "  "  + positionInfo;
    lb_positionInfo->setText(positionInfo);
}