#include "d3dApp.h"


LRESULT WINAPI MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return D3DApp::GetD3DApp()->MsgProc(hWnd, msg, wParam, lParam);
}

D3DApp* D3DApp::m_this = nullptr;
D3DApp::D3DApp(HINSTANCE hInstance) : m_hInstance(hInstance)
{
	m_this = this;
	m_hWnd = nullptr;
}

D3DApp::~D3DApp()
{
}
D3DApp* D3DApp::GetD3DApp()
{
	return m_this;
}

LRESULT D3DApp::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

		// key was pressed
	case WM_KEYDOWN: {
		switch (wParam)
		{
		case VK_ESCAPE: {
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		}

		}
		break;
	}
				   // User press the x so we are ordered to suicide
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 1;
	}

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool D3DApp::Initialize()
{
	if (!InitMainWindow())
		return false;

	if (!InitDirect3D())
		return false;

	return true;
}

bool D3DApp::InitMainWindow()
{
	WNDCLASSEX	wndclass;

	// Set up window attributes
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wndclass.lpfnWndProc = MainWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = m_hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = TEXT("TwoTriangles");
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (RegisterClassEx(&wndclass) == 0)
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// create window
	if (!(m_hWnd = CreateWindowEx(NULL, L"TwoTriangles",
		L"DirectX 12 TwoTriangles - By Yosbi Saenz",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
		WS_MINIMIZEBOX | WS_VISIBLE,
		GetSystemMetrics(SM_CXSCREEN) / 2 - (1280 / 2),
		GetSystemMetrics(SM_CYSCREEN) / 2 - (720 / 2),
		1280, 720, NULL, NULL, m_hInstance, NULL)))
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

bool D3DApp::InitDirect3D()
{
#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif

	ThrowIfFailed(CreateDXGIFactory(IID_PPV_ARGS(&m_dxgiFactory)));

	// Try to create hardware device.
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,             // default adapter
		D3D_FEATURE_LEVEL_12_0,
		IID_PPV_ARGS(&m_d3dDevice));

	// Fallback to WARP device.
	if (FAILED(hardwareResult))
	{
		ComPtr<IDXGIAdapter> pWarpAdapter;
		ThrowIfFailed(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));

		ThrowIfFailed(D3D12CreateDevice(
			pWarpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m_d3dDevice)));
	}

	return true;
}


int D3DApp::Run()
{
	MSG			msg;
	ZeroMemory(&msg, sizeof(msg));

	// Main windows loop
	while (msg.message != WM_QUIT)
	{
		// handle messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}
