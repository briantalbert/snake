#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(50 + (loc.x * dimension), 50 + (loc.y * dimension), dimension, dimension, Colors::Black);
	gfx.DrawRectDim(53 + (loc.x * dimension), 53 + (loc.y * dimension), dimension - 3, dimension - 3, c);
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetGridWidth() const
{
	return width;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 &&
		loc.x < width &&
		loc.y >= 0 &&
		loc.y < height;
}

void Board::DrawBorder(Graphics & gfx)
{
	for (int i = 48; i < (width * dimension) + 52; i++)
	{
		for (int j = 48; j < (height * dimension) + 52; j++)
		{
			if (i == 49 || i == 48 || j == 49 || j == 48 ||
				i == width * dimension + 50 || j == height * dimension + 50 ||
				i == width * dimension + 51 || j == height * dimension + 51)
			{
				gfx.PutPixel(i, j, Colors::Blue);
			}
		}
	}
}
