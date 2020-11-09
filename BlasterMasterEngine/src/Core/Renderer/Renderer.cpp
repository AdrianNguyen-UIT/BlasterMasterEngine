#include "d3dpch.h"
#include "Renderer.h"

Renderer::Renderer(std::shared_ptr<DeviceResources> deviceResources)
	:m_deviceResources(deviceResources)
{
}

Renderer::~Renderer()
{
}

void Renderer::Update()
{
	SceneManager::UpdateScene();

	for (auto object : SceneManager::GetActiveScene()->objects)
	{
		object->InnerUpdate(SceneManager::GetActiveScene()->camera->GetWorldToViewportMat());
	}

	for (auto object : SceneManager::GetActiveScene()->objects)
	{
		for (auto innerObject : SceneManager::GetActiveScene()->objects)
		{
			if (object != innerObject)
				object->DoCollision(innerObject);
		}
	}
}

HRESULT Renderer::CreateRendererResources()
{
	HRESULT hr = S_OK;

	bool result = SceneManager::LoadScene(L"MainScene");
	__ASSERT(result, "Unable to load scene");

	for (auto object : SceneManager::GetActiveScene()->objects)
	{
		object->InnerStart(m_deviceResources);
	}
	return hr;
}

void Renderer::Render()
{
	HRESULT hr = m_deviceResources->GetDevice()->BeginScene();

	if (SUCCEEDED(hr))
	{
		RenderBackground();

		for (auto object : SceneManager::GetActiveScene()->objects)
		{
			object->Draw(D3DXSPRITE_ALPHABLEND);
			object->RenderDebugRectangle(SceneManager::GetActiveScene()->camera->GetWorldToViewportMat());
		}

		m_deviceResources->GetDevice()->EndScene();
	}
}

void Renderer::RenderBackground()
{
	m_deviceResources->GetDevice()->StretchRect(SceneManager::GetActiveScene()->backGround, &SceneManager::GetActiveScene()->mapRect, m_deviceResources->GetBackBuffer(), NULL, D3DTEXF_NONE);
}