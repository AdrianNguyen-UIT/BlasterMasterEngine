#include "d3dpch.h"
#include "Window.h"
#include "Core/Time/time.h"

Window::Window()
{
	m_WindowClassName = L"D3DWindowClassName";
	m_HInstance = NULL;
    m_HWnd = NULL;
    m_Rc = { 0, 0, 0, 0 };
}

HRESULT Window::Create(std::wstring title, UINT clientWidth, UINT clientHeight)
{
    if (m_HInstance == NULL)
        m_HInstance = (HINSTANCE)GetModuleHandle(NULL);

    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_HInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = m_WindowClassName.c_str();
    wc.lpszMenuName = NULL;
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    SetRect(&m_Rc, 0, 0, clientWidth, clientHeight);
    AdjustWindowRect(&m_Rc, WS_OVERLAPPEDWINDOW, FALSE);

    m_HWnd = CreateWindowEx(NULL,
        m_WindowClassName.c_str(),
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT, 
        m_Rc.right - m_Rc.left,
        m_Rc.bottom - m_Rc.top,
        NULL,
        NULL,
        m_HInstance,
        NULL);

    if (m_HWnd == NULL)
    {
        DWORD dwError = GetLastError();
        return HRESULT_FROM_WIN32(dwError);
    }

    return S_OK;
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
    {
        HMENU hMenu;
        hMenu = GetMenu(hWnd);
        if (hMenu != NULL)
        {
            DestroyMenu(hMenu);
        }
        DestroyWindow(hWnd);
        UnregisterClass(
            m_WindowClassName.c_str(),
            m_HInstance
        );
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

HRESULT Window::Run(std::unique_ptr<DeviceResources>& deviceResources, std::unique_ptr<Renderer>& renderer, std::unique_ptr<Input>& input, std::unique_ptr<SceneManager>& sceneManager, int nCmdShow)
{
    if (!IsWindowVisible(m_HWnd))
    {
        ShowWindow(m_HWnd, nCmdShow);
        UpdateWindow(m_HWnd);
    }

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    static float lastFrameTime = (float)timeGetTime();

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Time::SetFixedDeltaTime(MONITOR_REFESH_RATE);
            float currentFrameTime = (float)timeGetTime();
            Time::SetDeltaTime((currentFrameTime - lastFrameTime) * 0.001f);
            lastFrameTime = currentFrameTime;

            input->GetMouse();
            input->GetKeyboard();

            if (sceneManager->LoadActiveScene())
            {
                renderer->CreateRendererResources();
            }

            renderer->Update();
            renderer->Render();

            deviceResources->Present();

            if (Input::GetKeyDown(KeyCode_ESCAPE))
            {
                LOG_INFO("Cleaning resources...");
                PostMessage(m_HWnd, WM_DESTROY, 0, 0);
            }
        }
    }
    return S_OK;
}