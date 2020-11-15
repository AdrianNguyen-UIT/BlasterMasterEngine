#include "d3dpch.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Update()
{
	SceneManager::UpdateScene();

	std::list<std::shared_ptr<Object2D>> objects = SceneManager::GetActiveScene()->GetObjectList();
	for (auto object : objects)
	{
		object->InnerUpdate(SceneManager::GetActiveScene()->GetActiceCamaera()->GetWorldToViewportMat());
	}

	for (auto object : objects)
	{
		for (auto innerObject : objects)
		{
			if (object != innerObject)
				object->DoCollision(innerObject);
		}
	}
}

HRESULT Renderer::CreateRendererResources()
{
	HRESULT hr = S_OK;

	bool result = SceneManager::LoadScene("Area2");
	__ASSERT(result, "Unable to load scene");

	for (auto object : SceneManager::GetActiveScene()->GetObjectList())
	{
		object->InnerStart();
	}
	return hr;
}

void Renderer::Render()
{
	HRESULT hr = DeviceResources::GetDevice()->BeginScene();
	if (SUCCEEDED(hr))
	{
		RenderBackground();

		for (auto object : SceneManager::GetActiveScene()->GetObjectList())
		{
			object->Draw(D3DXSPRITE_ALPHABLEND);
			//object->RenderDebugRectangle(SceneManager::GetActiveScene()->GetActiceCamaera()->GetWorldToViewportMat());
		}

		DeviceResources::GetDevice()->EndScene();
	}
}

void Renderer::RenderBackground()
{

	DeviceResources::GetDevice()->StretchRect(SceneManager::GetActiveScene()->GetBackground(), &SceneManager::GetActiveScene()->GetMapRect(), DeviceResources::GetBackBuffer(), NULL, D3DTEXF_NONE);
}