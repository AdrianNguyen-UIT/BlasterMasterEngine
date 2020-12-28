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

	for (std::shared_ptr<Object2D> object : objects)
	{
		object->InnerUpdate(SceneManager::GetActiveScene()->GetActiceCamera()->GetWorldToViewportMat());
	}

	for (std::shared_ptr<Object2D> object : objects)
	{
		for (std::shared_ptr<Object2D> innerObject : objects)
		{
			if (object != innerObject)
			{
				object->DoCollision(innerObject);
			}
		}
	}

	SceneManager::GetActiveScene()->UpdateCanvas();
}

HRESULT Renderer::CreateRendererResources()
{
	HRESULT hr = S_OK;

	for (std::shared_ptr<Object2D> object : SceneManager::GetActiveScene()->GetObjectList())
	{
		object->InnerStart();
	}

	SceneManager::GetActiveScene()->StartCanvas();
	return hr;
}

void Renderer::Render()
{
	D3DXMATRIX worldToVPMatrix = SceneManager::GetActiveScene()->GetActiceCamera()->GetWorldToViewportMat();
	HRESULT hr = DeviceResources::GetDevice()->BeginScene();
	if (SUCCEEDED(hr))
	{
		RenderBackground();

		for (std::shared_ptr<Object2D> object : SceneManager::GetActiveScene()->GetAllRenderableObjects())
		{
			object->Draw(D3DXSPRITE_ALPHABLEND);
			//object->RenderDebugRectangle(worldToVPMatrix);
		}

		SceneManager::GetActiveScene()->RenderCanvas(D3DXSPRITE_ALPHABLEND);

		DeviceResources::GetDevice()->EndScene();
	}
}

void Renderer::RenderBackground()
{
	DeviceResources::GetDevice()->StretchRect(SceneManager::GetActiveScene()->GetBackground(), &SceneManager::GetActiveScene()->GetMapRender(), DeviceResources::GetBackBuffer(), NULL, D3DTEXF_NONE);
}