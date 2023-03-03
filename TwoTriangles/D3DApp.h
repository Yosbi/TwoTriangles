#ifndef D3D_APP_H
#define D3D_APP_H

#pragma once

#include "D3DUtil.h"



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
	void CreateCommandObjects();
	void CreateSwapChain();
	int Run();


protected:


private:
	static D3DApp* m_this;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> m_d3dDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;

	// Fence stuff (cpu/gpu sync)
	Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
	UINT64 m_CurrentFence = 0;

	UINT m_RtvDescriptorSize = 0;		// Render target 
	UINT m_DsvDescriptorSize = 0;		// Deep Stencil 
	UINT m_CbvSrvUavDescriptorSize = 0;	// Constant buffer

	// Multisampling 
	bool      m4xMsaaState = false;    // 4X MSAA enabled
	UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA

	// Command objects
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_CmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;

	// Backbuffer stuff
	const int m_nSwapChainBufferCount = 2;


	DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM; // Backbuffer format
	DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT; // DeepStencil format

	int m_ClientWidth = 1280;
	int m_ClientHeight = 720;
};
#endif

