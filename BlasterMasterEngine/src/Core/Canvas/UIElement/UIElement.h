#pragma once
#include "Component/Component.h"
#include "Core/DeviceResources/DeviceResources.h"
#include "Core/SpriteResources/SpriteResources.h"
class UIElement : public std::enable_shared_from_this<UIElement>
{
protected:
	D3DXVECTOR3 position;
	std::string name;
	bool enable;
	Color color;
	std::unique_ptr<SpriteRenderer> spriteRenderer;

	std::vector<std::shared_ptr<UIElement>> childUIElements;

public:
	UIElement(float x = 0.0f, float y = 0.0f);
	virtual ~UIElement() = default;

	virtual void Start() {}
	virtual void Update() {}
	virtual void CreateResources() {}

	template <class T>
	std::shared_ptr<UIElement> GetPtr() { return shared_from_this(); }

	virtual void SetEnable(bool p_Enable) { enable = p_Enable; }
	bool GetEnable() { return enable; }

	virtual void SetPosition(D3DXVECTOR3 pos = {0.0f, 0.0f, 0.0f});
	virtual void SetPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	D3DXVECTOR3 GetPosition() { return position; }

	void SetName(std::string p_Name);
	std::string GetName() { return name; }

	virtual void SetColor(Color c);
	Color GetColor() { return color; }

	void AddChildUIElement(std::shared_ptr<UIElement> &child);

public:
	void Draw(DWORD flags);
};