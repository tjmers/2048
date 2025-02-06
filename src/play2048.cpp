// g++ src/play2048.cpp src/board.cpp src/visual_board.cpp src/input.cpp src/graphics.cpp -o 2048.exe -O3 -std=c++20 -ld2d1 -lWindowsCodecs -lole32

#include <Windows.h>

#include "graphics.h"
#include "input.h"
#include "visual_board.h"

#include <chrono>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Graphics graphics;


int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow) {

    constexpr LPCWSTR CLASS_NAME = L"mainwin";

    using namespace std::chrono_literals;
    constexpr int targetFPS = 60;
    constexpr float ONE_SIXTYITH = 1.0f / targetFPS;
	constexpr std::chrono::nanoseconds timestep(1000ms / targetFPS);


	WNDCLASSEXW window{ 0 };
	window.hInstance = hInstance;
	window.lpszClassName = CLASS_NAME;
	window.lpfnWndProc = WndProc;
	window.cbSize = sizeof(window);
	window.style = CS_OWNDC;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hIcon = nullptr;
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.lpszMenuName = nullptr;
	window.hIconSm = nullptr;
	RegisterClassExW(&window);


	RECT client_region = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&client_region, WS_CAPTION | WS_SYSMENU | WS_BORDER, FALSE, 0);

	HWND hWnd = CreateWindowExW(
		0,
		CLASS_NAME,
		L"2048",
		WS_CAPTION | WS_SYSMENU | WS_BORDER,
		75, 25, client_region.right - client_region.left, client_region.bottom - client_region.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (FAILED(graphics.CreateGraphicsResources(hWnd))) {
		return -1;
	}


	if (FAILED(VisualBoard::init(graphics))) {
		return -1;
	}



	VisualBoard board;
	Input::Reset();

    ShowWindow(hWnd, SW_SHOW);

	using clock = std::chrono::high_resolution_clock;
	std::chrono::nanoseconds lag(0ns);
	auto timeStart = clock::now();

    float frame_delta_time = 0.0f;

	MSG msg{ 0 };
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT) {
		auto currentTime = clock::now();
		auto delta_time = currentTime - timeStart;
		timeStart = currentTime;
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);
        frame_delta_time += delta_time.count();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			while (lag >= timestep) {
				lag -= timestep;
                constexpr static int ONE_BILLION = 1e9;
				board.update(/*frame_delta_time / ONE_BILLION / ONE_SIXTYITH*/); // pass in number of frames reletive to 60 FPS (if exactly 1/60 second passed, 1.0f would get passed in)
                frame_delta_time = 0;
			}


			graphics.BeginDraw();
			board.draw(graphics);
			graphics.EndDraw();

		}
		
	}



    return static_cast<int>(msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KILLFOCUS:
		Input::Reset();
		break;
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
		Input::HandleKeyboardInput(wParam, (lParam & 0x80000000) == 0);

		break;

	default:
		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}