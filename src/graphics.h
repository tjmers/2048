#pragma once

#include <Windows.h>

#include <d2d1.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 640;

class Graphics
{
    ID2D1Factory* factory;
    ID2D1HwndRenderTarget* render_target;
    ID2D1SolidColorBrush* brush;
    IWICImagingFactory* imaging_factory;
    IWICFormatConverter* format_converter;

public:
    Graphics();
    ~Graphics();

    HRESULT CreateGraphicsResources(HWND hWnd);
    HRESULT LoadBitmapFromFile(PCWSTR uri, ID2D1Bitmap** bitmap);

    void SetColor(const D2D1::ColorF& color) const;
    void ClearScreen(float r, float g, float b);
    void ClearScreen(const D2D1::ColorF& color);
    void DrawRect(const D2D1_RECT_F& rect, const float thickness) const;
    void FillRect(const D2D1_RECT_F& rect) const;
    void FillCircle(float x, float y, float r) const;
    void DrawLine(const D2D1_POINT_2F& point1, const D2D1_POINT_2F& point2, const float thickness) const;
    void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F src, D2D1_RECT_F dest);

    void BeginDraw();
    void EndDraw();
};