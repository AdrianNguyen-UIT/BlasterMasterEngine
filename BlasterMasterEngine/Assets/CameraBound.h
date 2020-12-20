#pragma once

class CameraBound
{
private:
	static std::vector<RECT> bounds;
	static int currentBoundIndex;

public:
	static void AddBound(RECT bound);
	static RECT GetCurrentBound() { return bounds[currentBoundIndex]; }
	static void SetCurrentBound(RECT rect);

private:
	static bool CheckBound(RECT rect1, RECT rect2);
};