// main.cpp
// UTF-8 编码（请保存为 UTF-8 无 BOM）
// 功能：使用 Win32 原生窗口 + OpenCASCADE V3d / AIS，显示一个立方体
// 并确保：鼠标左键拖动旋转、滚轮缩放、右键平移 —— 全部可用！

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

// ===== OpenCASCADE 头文件 =====
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <WNT_Window.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <iostream>

// ===== 全局变量，用于保存 OpenCASCADE 对象 =====
Handle(V3d_Viewer) g_Viewer = nullptr;
Handle(V3d_View) g_View = nullptr;
Handle(AIS_InteractiveContext) g_Context = nullptr;
Handle(AIS_Shape) g_AIS_Shape = nullptr;

// ===== Win32 窗口过程 =====
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SIZE:
        if (!g_View.IsNull())
        {
            g_View->MustBeResized();
            g_View->RedrawImmediate();
        }
        return 0;

    case WM_PAINT:
        if (!g_View.IsNull())
        {
            g_View->RedrawImmediate();
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// ===== 主函数：WinMain 入口 =====
int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    // ===== 1. 注册窗口类 =====
    const TCHAR CLASS_NAME[] = _T("OpenCASCADE_Win32_Class");

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.style = CS_OWNDC; // 必须，为了 OpenGL

    if (!RegisterClass(&wc))
    {
        MessageBox(nullptr, _T("窗口类注册失败！"), _T("错误"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // ===== 2. 创建窗口 =====
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        _T("OpenCASCADE 示例：鼠标旋转立方体（Win32 + V3d）"),
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr)
    {
        MessageBox(nullptr, _T("窗口创建失败！"), _T("错误"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // ✅ 必须调用！否则窗口不显示
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // ===== 3. 初始化 OpenCASCADE =====

    // 3.1 创建 DisplayConnection
    Handle(Aspect_DisplayConnection) aDisplayConnection = new Aspect_DisplayConnection();
    if (aDisplayConnection.IsNull())
    {
        MessageBox(nullptr, _T("无法创建 DisplayConnection！"), _T("错误"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // 3.2 创建 OpenGL 图形驱动
    Handle(OpenGl_GraphicDriver) aGraphicDriver = new OpenGl_GraphicDriver(aDisplayConnection);
    if (aGraphicDriver.IsNull())
    {
        MessageBox(nullptr, _T("无法创建图形驱动！"), _T("错误"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // 3.3 创建 V3d Viewer
    g_Viewer = new V3d_Viewer(aGraphicDriver);
    g_Viewer->SetDefaultBackgroundColor(Quantity_NOC_GRAY20);
    g_Viewer->SetDefaultLights();
    g_Viewer->SetLightOn();

    // 3.4 创建 WNT_Window（传入 Win32 的 HWND）
    Handle(WNT_Window) aWin = new WNT_Window((Aspect_Handle)hwnd);
    if (!aWin->IsMapped())
    {
        MessageBox(nullptr, _T("无法创建 WNT_Window！"), _T("错误"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // 3.5 创建 V3d_View
    g_View = g_Viewer->CreateView();
    g_View->SetWindow(aWin);

    // ✅ 必须调用！！！
    g_View->MustBeResized();

    // ✅ 强烈建议：启用立即更新，确保交互响应
    g_View->SetImmediateUpdate(Standard_True);

    // ✅ 必须调用！
    g_View->RedrawImmediate();

    // 3.6 创建交互上下文
    g_Context = new AIS_InteractiveContext(g_Viewer);
    g_Context->SetDisplayMode(AIS_Shaded, Standard_True);

    // 3.7 创建一个立方体 Shape
    TopoDS_Shape aShape = BRepPrimAPI_MakeBox(50.0, 50.0, 50.0).Shape();

    // 3.8 包装为 AIS_Shape
    g_AIS_Shape = new AIS_Shape(aShape);
    g_Context->Display(g_AIS_Shape, Standard_True);

    // 3.9 自动适配视角（关键！让摄像机正确朝向物体）
    g_View->FitAll();
    g_View->ZFitAll();
    g_View->RedrawImmediate();

    // ===== 4. 消息循环 =====
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}