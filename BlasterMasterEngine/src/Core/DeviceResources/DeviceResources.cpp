#include "d3dpch.h"
#include "DeviceResources.h"

LPDIRECT3D9 DeviceResources::d3d;
LPDIRECT3DDEVICE9 DeviceResources::d3ddev;
LPDIRECT3DSURFACE9 DeviceResources::backBuffer;

DeviceResources::DeviceResources()
{
	d3d = NULL;
    d3ddev = NULL;
    backBuffer = NULL;
}

DeviceResources::~DeviceResources()
{
    backBuffer->Release();
    d3d->Release();
    d3ddev->Release();
}

HRESULT DeviceResources::CreateDeviceResources(HWND hWnd)
{
    HRESULT hr = S_OK;
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.Flags = 0;
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    d3dpp.EnableAutoDepthStencil = FALSE;
    RECT rc;
    GetClientRect(hWnd, &rc);

    d3dpp.BackBufferWidth = rc.right;
    d3dpp.BackBufferHeight = rc.bottom;
    d3dpp.BackBufferCount = 1;

    hr = d3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3ddev);


    srand(time(NULL));

    D3DVIEWPORT9 viewData = { (DWORD)0.0f, (DWORD)0.0f, (DWORD)rc.right, (DWORD)rc.bottom, 0.1f, 1.0f };
    hr = d3ddev->SetViewport(&viewData);

    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

    return hr;
}

void DeviceResources::Present()
{
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DSURFACE9 DeviceResources::LoadSurface(std::wstring filename, D3DCOLOR transcolor)
{
    LPDIRECT3DSURFACE9 image = NULL;
    D3DXIMAGE_INFO info;
    HRESULT hr;
    hr = D3DXGetImageInfoFromFile(filename.c_str(), &info);
    if (FAILED(hr))
    {
        __ASSERT(false, "Unable to get image info!");
        return NULL;
    }

    hr = d3ddev->CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &image, NULL);
    if (FAILED(hr))
    {
        __ASSERT(false, "Unable to create offscreen plain surface!");
        return NULL;
    }

    hr = D3DXLoadSurfaceFromFile(image, NULL, NULL, filename.c_str(), NULL, D3DX_DEFAULT, transcolor, NULL);
    if (FAILED(hr))
    {
        __ASSERT(false, "Unable to load surface!");
        return NULL;
    }
    return image;
}

std::shared_ptr<Sprite> DeviceResources::LoadTexture(std::wstring filename, D3DCOLOR transcolor)
{
    LPDIRECT3DTEXTURE9 texture = NULL;
    D3DXIMAGE_INFO info;
    HRESULT hr;

    hr = D3DXGetImageInfoFromFile(filename.c_str(), &info);
    if (FAILED(hr))
    {
        __ASSERT(false, "Unable to get image info!");
        return NULL;
    }

    hr = D3DXCreateTextureFromFileEx(
        d3ddev,
        filename.c_str(),
        info.Width,
        info.Height,
        1,
        D3DPOOL_DEFAULT,
        D3DFMT_UNKNOWN,
        D3DPOOL_DEFAULT,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        transcolor,
        &info,
        NULL,
        &texture
    );
    if (FAILED(hr))
    {
        __ASSERT(false, "Unable to load texture!");
        return NULL;
    }
    return std::make_shared<Sprite>(texture);
}