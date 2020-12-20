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

	std::list<std::shared_ptr<Object2D>> objects = SceneManager::GetActiveScene()->GetAllRenderableObjects();

	for (auto object : objects)
	{
		object->InnerUpdate(SceneManager::GetActiveScene()->GetActiceCamera()->GetWorldToViewportMat());
	}
	//LOG_INFO("{0}", objects.size());

	for (auto object : objects)
	{
		for (auto innerObject : objects)
		{
			if (object != innerObject)
			{
				object->DoCollision(innerObject);
			}
		}
	}
}

HRESULT Renderer::CreateRendererResources()
{
	HRESULT hr = S_OK;

	for (auto object : SceneManager::GetActiveScene()->GetObjectList())
	{
		object->InnerStart();
	}
	return hr;
}

void Renderer::Render()
{
	D3DXMATRIX worldToVPMatrix = SceneManager::GetActiveScene()->GetActiceCamera()->GetWorldToViewportMat();
	HRESULT hr = DeviceResources::GetDevice()->BeginScene();
	if (SUCCEEDED(hr))
	{
		RenderBackground();

		for (auto object : SceneManager::GetActiveScene()->GetAllRenderableObjects())
		{
			object->Draw(D3DXSPRITE_ALPHABLEND);
			//object->RenderDebugRectangle(worldToVPMatrix);
		}

		DeviceResources::GetDevice()->EndScene();
	}
}

void Renderer::RenderBackground()
{
	DeviceResources::GetDevice()->StretchRect(SceneManager::GetActiveScene()->GetBackground(), &SceneManager::GetActiveScene()->GetMapRender(), DeviceResources::GetBackBuffer(), NULL, D3DTEXF_NONE);
}