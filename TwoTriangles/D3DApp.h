#ifndef D3D_APP_H
#define D3D_APP_H

#pragma once

#include "D3DUtil.h"

// Linking necessary d3d12 libraries
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	~D3DApp();

	static D3DApp* GetD3DApp();

	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Initialize();
	bool InitMainWindow();
	bool InitDirect3D();
	int Run();
	

protected:
	

private:
	static D3DApp* m_this;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> m_d3dDevice;
};

#endif

