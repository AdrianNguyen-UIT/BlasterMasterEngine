#pragma once
#include "Core/Canvas/UIElement/UIElement.h"
#include "ImageUI.h"
class TextUI : public UIElement
{
protected:
	std::string text;
	std::string font;
	bool horizontal;
	D3DXVECTOR2 offset;

public:
	TextUI(const float x = 0.0f, const float y = 0.0f, const std::string& str = "", const std::string fn = "", const bool& h = true, const D3DXVECTOR2 &os = {0.0f, 0.0f});

	virtual void Start() override;
	virtual void CreateResources() override;

	std::string GetText() { return text; }
	void SetText(const std::string& str) { text = str; }

	std::string GetFont() { return font; }
	void SetFontUI(const std::string& f) { font = f; }

	void SetHorizontal(bool enable) { horizontal = enable; }
	bool GetHorizontal() { return horizontal; }

	void SetOffset(const float& x, const float& y) { offset.x = x; offset.y = y; }
	D3DXVECTOR2 GetOffset() { return offset; }

	virtual void SetColor(Color c) override;
	virtual void SetPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f) override;
	virtual void SetEnable(bool p_Enable) override;
};