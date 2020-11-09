#include "d3dpch.h"
#include "Application/Application.h"

std::unique_ptr<Application> app;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    AllocConsole();

	Log::Init();

	app = std::make_unique<Application>();
	HRESULT hr = S_OK;
	hr = app->Run(nCmdShow);
	return hr;
}