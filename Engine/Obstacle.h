#pragma once
#include "Snake.h"
#include "Board.h"
#include <random>
#include "Location.h"
#include "Goal.h"

class Obstacle
{
public:
	void initObs(std::mt19937& rng, const Board& brd, const Snake& snake, Goal& goal);
	void Draw(Board& brd) const;
	const Location& GetLocation()const;
private:
	Location loc;
	static constexpr Color c = Colors::Gray;
};