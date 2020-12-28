#pragma once

class SpriteResources
{
private:
	static std::vector<std::shared_ptr<Sprite>> sprites;
public:
	SpriteResources();
	~SpriteResources();

	HRESULT CreateSpriteResources();

	static std::shared_ptr<Sprite> GetSprite(const std::string& name);
};