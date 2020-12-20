#include "d3dpch.h"
#include "CameraBound.h"

std::vector<RECT> CameraBound::bounds;
int CameraBound::currentBoundIndex = 0;

void CameraBound::AddBound(RECT bound)
{
	bounds.emplace_back(bound);
}

void CameraBound::SetCurrentBound(RECT rect)
{
	for (size_t index = 0; index < bounds.size(); ++index)
	{
		if (CheckBound(bounds[index], rect))
		{
			currentBoundIndex = index;
			return;
		}
	}
}

bool CameraBound::CheckBound(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.left || rect1.right < rect2.right || rect1.top > rect2.top || rect1.bottom < rect2.bottom)
		return false;

	return true;
}