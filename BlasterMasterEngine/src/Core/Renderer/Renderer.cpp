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
	D3DXMATRIX worldToVPMatrix = SceneManager::GetActiveScene()->GetActiceCamaera()->GetWorldToViewportMat();
	SceneManager::GetActiveScene()->UpdateCollideableObjects();
	std::list<std::shared_ptr<Object2D>> objects = SceneManager::GetActiveScene()->GetAllCollideableObjects();
	std::shared_ptr<Object2D> player = SceneManager::GetActiveScene()->GetPlayer();

	SceneManager::UpdateScene();

	player->InnerUpdate(worldToVPMatrix);
	
	for (auto object : objects)
	{
		object->InnerUpdate(worldToVPMatrix);
	}

	for (auto object : objects)
	{
		player->DoCollision(object);
	}

}

HRESULT Renderer::CreateRendererResources()
{
	HRESULT hr = S_OK;

	bool result = SceneManager::LoadScene("Area2");
	__ASSERT(result, "Unable to load scene");

	SceneManager::GetActiveScene()->GetPlayer()->InnerStart();

	for (auto object : SceneManager::GetActiveScene()->GetObjectList())
	{
		object->InnerStart();
	}
	return hr;
}

void Renderer::Render()
{
	D3DXMATRIX worldToVPMatrix = SceneManager::GetActiveScene()->GetActiceCamaera()->GetWorldToViewportMat();
	std::shared_ptr<Object2D> player = SceneManager::GetActiveScene()->GetPlayer();
	HRESULT hr = DeviceResources::GetDevice()->BeginScene();
	if (SUCCEEDED(hr))
	{
		RenderBackground();

		player->Draw(D3DXSPRITE_ALPHABLEND);
		player->RenderDebugRectangle(worldToVPMatrix);

		for (auto object : SceneManager::GetActiveScene()->GetAllCollideableObjects())
		{
			object->Draw(D3DXSPRITE_ALPHABLEND);
			object->RenderDebugRectangle(worldToVPMatrix);
		}

		DeviceResources::GetDevice()->EndScene();
	}
	LOG_INFO("{0}", SceneManager::GetActiveScene()->GetAllCollideableObjects().size());
}

void Renderer::RenderBackground()
{
	DeviceResources::GetDevice()->StretchRect(SceneManager::GetActiveScene()->GetBackground(), &SceneManager::GetActiveScene()->GetMapRender(), DeviceResources::GetBackBuffer(), NULL, D3DTEXF_NONE);
}