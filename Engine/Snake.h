#pragma once
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		void InitHead(const Location& loc);
		void InitBody();
		void MoveBy(const Location& delta_loc);
		const Location GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Grow();
	void Draw(Board& brd) const;
	bool IsInTile(const Location& target) const;
	bool IsInTileIncEnd(const Location & target) const;

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::MakeRGB(0, 255, 0);
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};
