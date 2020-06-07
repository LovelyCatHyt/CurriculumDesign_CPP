#pragma once
#include "Position.h"

namespace ConAPIProx
{
	class Rect
	{
	public:
		Position leftUp, rightDown;
		Rect(const Position& lu, const Position& rd);
		short Width() const;
		short Height() const;
	};
}
