/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"
#include <random>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	snek({2,2}),
	goal(rng, brd, snek),
	newObs()
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!isStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isStarted = true;
		}
	}
	if (!gameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			delta_loc = { 0,-1 };
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = { -1,0 };
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1,0 };
		}
	}

	++MoveCounter;
	if (MoveCounter >= MovePeriod)
	{
		MoveCounter = 0;
		const Location next = snek.GetNextHeadLocation(delta_loc);
		
		if (!brd.IsInsideBoard(next) ||
			snek.IsInTile(next))

		{
			gameOver = true;
		}
		else
		{
			bool eating = (next == goal.GetLocation());
			if (eating)
			{
				score += 1;
				snek.Grow();
				if ((MovePeriod > 4) && (score % 4 == 0))
				{
					MovePeriod -= 2;
				}
				
				int obsTest = rand() % 100;
				if ((numObstacles < maxObstacles) && (obsTest % 4) == 0)
				{
					Obstacle newObs;
					newObs.initObs(rng, brd, snek, goal);
					ObsList[numObstacles] = newObs;
					numObstacles += 1;
				}
			}

			for (int i = 0; i < numObstacles; i++)
			{
				if (next == ObsList[i].GetLocation())
				{
					gameOver = true;
				}
			}

			if (!gameOver)
			{
				snek.MoveBy(delta_loc);
			}
			if (eating)
			{
				goal.Respawn(rng, brd, snek);
			}
		}
	}

}

void Game::DrawScoreboard()
{
	int groupCount = 0;
	int remainder = score;
	
	while (remainder >= 5)
	{
		remainder -= 5;
		groupCount += 1;
	}

	for (int i = 0; i < groupCount; i++)
	{
		gfx.DrawFive(scoreBoardX, scoreBoardY, Colors::Blue);
		scoreBoardY += 25;
	}

	
	for (int i = 0; i < remainder; i++)
	{
		gfx.DrawRectDim(scoreBoardX, scoreBoardY, 3, 20, Colors::Blue);
		scoreBoardX += 5;
	}

	scoreBoardX = 600;
	scoreBoardY = 50;
}

void Game::ComposeFrame()
{
	if (!isStarted)
	{
		SpriteCodex::DrawTitle(200, 200, gfx);
	}
	else
	{
		
		brd.DrawBorder(gfx);
		DrawScoreboard();
		if (!gameOver)
		{
			snek.Draw(brd);
			goal.Draw(brd);
		}
		for (int i = 0; i < numObstacles; i++)
		{
			ObsList[i].Draw(brd);
		}
		if (gameOver)
		{
			SpriteCodex::DrawGameOver(250, 250, gfx);
		}
	}
}
