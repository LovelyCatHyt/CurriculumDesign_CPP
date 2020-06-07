#pragma once
#include <Windows.h>

namespace ConAPIProx
{
	class Position
	{
	public:
		short x, y;
		Position(const COORD& coord = { 0,0 });
		Position(const short& x, const short& y);
		operator COORD () const;
		Position operator+(const Position& b) const;
		Position operator-(const Position& b) const;
	};
}

