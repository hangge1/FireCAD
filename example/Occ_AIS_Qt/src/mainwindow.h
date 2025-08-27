#pragma once

#include "View.h"

#include <QMainWindow>
#include <QComboBox>
#include <QStatusBar>
#include <QLabel>
#include <QActionGroup>
#include <QToolBar>

#include "Geom_Plane.hxx"
#include "GeomAPI_ProjectPointOnSurf.hxx"
#include "BRepPrimAPI_MakeBox.hxx"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initMenuToolbar();
    void initOCCTView();
    void setViewer(const Handle(V3d_Viewer)& theViewer);
    void initSignals();
    void test();
    void setSelectMode();

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    Handle(V3d_Viewer) Viewer(const V3d_TypeOfOrientation theViewProj);

    void updateStatusBar(const std::vector<double>& aNewPos);

    const Standard_Real _devPx;
    Handle(V3d_Viewer) myViewer;
    Handle(AIS_InteractiveContext) myContext;
    std::vector<double> myClickPos;

    View* view_occt;
    QStatusBar* stb;
    QLabel* lb_positionInfo;

    QToolBar* tb_view;
    QAction* act_hideAll;
    QAction* act_hide;
    QAction* act_fitAll;
    QAction* act_axo;
    QAction* act_top;
    QAction* act_buttom;
    QAction* act_left;
    QAction* act_right;
    QAction* act_front;
    QAction* act_back;
    QAction* act_shade;
    QAction* act_wireframe;
    QAction* act_axis;
    QAction* act_test;

    QToolBar* tb_style;
    QAction* act_color;
    QAction* act_material;
    QActionGroup* actgp_selectMode;
    QAction* act_selectVertex;
    QAction* act_selectEdge;
    QAction* act_selectFace;
};

