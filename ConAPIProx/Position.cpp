#include "Position.h"
#include <Windows.h>


namespace ConAPIProx
{
	Position::Position(const COORD& coord) : x(coord.X), y(coord.Y)
	{
	}
	Position::Position(const short& x, const short& y) : x(x), y(y)
	{
	}
	Position::operator COORD() const
	{
		return { x,y };
	}
	Position Position::operator+(const Position& b) const
	{
		return Position(x + b.x, y + b.y);
	}
	Position Position::operator-(const Position& b) const
	{
		return Position(x - b.x, y - b.y);
	}
}
