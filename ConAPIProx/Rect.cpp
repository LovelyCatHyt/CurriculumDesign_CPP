#include "Rect.h"
#include <utility>

namespace ConAPIProx
{
	Rect::Rect(const Position& lu, const Position& rd) : leftUp(lu), rightDown(rd)
	{
		if (leftUp.x > rightDown.x) std::swap(leftUp.x, rightDown.x);
		if (rightDown.y < leftUp.y) std::swap(rightDown.y, leftUp.y);
	}
	short Rect::Width() const
	{
		return rightDown.x - leftUp.x + 1;
	}
	short Rect::Height() const
	{
		return leftUp.y - rightDown.y + 1;
	}
}