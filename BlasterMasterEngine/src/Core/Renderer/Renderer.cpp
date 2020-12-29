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
	std::list<std::shared_ptr<Object2D>> objects = SceneManager::GetActiveScene()->GetAllObjects();

	for (std::shared_ptr<Object2D> object : objects)
	{
		object->InnerUpdate(SceneManager::GetActiveScene()->GetActiceCamera()->GetWorldToViewportMat());
	}

	SceneManager::UpdateScene();

	std::list<std::shared_ptr<Object2D>> returnObjects;
	for (std::shared_ptr<Object2D> object : objects)
	{
		if (!object->NoCollision())
		{
			SceneManager::GetActiveScene()->RetrieveCollidableObjects(returnObjects, object);
			for (std::shared_ptr<Object2D> innerObject : returnObjects)
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

	for (std::shared_ptr<Object2D> object : SceneManager::GetActiveScene()->GetAllObjects())
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
		std::list<std::shared_ptr<Object2D>> returnObjects;
		SceneManager::GetActiveScene()->RetrieveRenderableObjects(returnObjects);
		for (std::shared_ptr<Object2D> object : returnObjects)
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