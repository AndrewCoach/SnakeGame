#include <iostream>
#include "olcConsoleGameEngine.h"
#include "AStar.h"

enum class Keys
{
	W = 1, A = 2, S = 4, D = 8
};

class OneLoneCoder_Example : public olcConsoleGameEngine
{
public:
	OneLoneCoder_Example() {}

	bool OnUserCreate() override
	{
		////CREATE FOR WALLS DEMO

		//initiLIZE the snake to an arbitrary size for now.
		for (int i = 0; i < 10; i++)
		{
			GridLocation element{ i + 10, 10 };
			snake.push_back(element);
		}

		//fill this block with white
		this->Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, COLOUR::FG_WHITE);

		//// create for ASTAR, will have to be redone
		astar.addEmptyWeightedGraph(this->ScreenWidth(), this->ScreenHeight());

		//Add walls
		astar.addWallToGraph(10, 50, 1, 3);
		astar.addWallToGraph(55, 56, 1, 70);

		//draw walls
		for (auto& location : astar.forrestGrid.walls)
		{
			this->Draw(location.x, location.y, PIXEL_SOLID, FG_BLACK);
		}

		//draw snake - lets hope it is not in a wall
		for (auto& snakeBody : snake)
		{
			this->Draw(snakeBody.x, snakeBody.y, PIXEL_SOLID, FG_GREEN);
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		elapsedTime += fElapsedTime;
		// if it has been at least half a second...

		if (m_keys[L'W'].bPressed || m_keys[L'W'].bHeld && key != Keys::S)
		{
			wantToGO = Keys::W;
		}
		else if (m_keys[L'A'].bPressed || m_keys[L'A'].bHeld && key != Keys::D)
		{
			wantToGO = Keys::A;
		}
		else if (m_keys[L'S'].bPressed || m_keys[L'S'].bHeld && key != Keys::W)
		{
			wantToGO = Keys::S;
		}
		else if (m_keys[L'D'].bPressed || m_keys[L'D'].bHeld && key != Keys::A)
		{
			wantToGO = Keys::D;
		}

		if (elapsedTime > 0.5F)
		{
			//DRAWING
			//fill this block with white
			this->Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, COLOUR::FG_WHITE);
			//draw walls
			for (auto& location : astar.forrestGrid.walls)
			{
				this->Draw(location.x, location.y, PIXEL_SOLID, FG_BLACK);
			}

			auto oldSnake = snake;
			auto oldHead = snake.at(0);
			elapsedTime = 0;
			if (wantToGO == Keys::W)
			{
				auto newHead = oldHead;
				newHead.y -= 1;
				snake.clear();
				snake.push_back(newHead);
				for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
				{
					snake.push_back(*it);
				}
				snake.pop_back();
				key = Keys::W;
			}
			else if (wantToGO == Keys::A)
			{
				auto newHead = oldHead;
				newHead.x -= 1;
				snake.clear();
				snake.push_back(newHead);
				for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
				{
					snake.push_back(*it);
				}
				snake.pop_back();
				key = Keys::A;
			}
			else if (wantToGO == Keys::S)
			{
				auto newHead = oldHead;
				newHead.y += 1;
				snake.clear();
				snake.push_back(newHead);
				for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
				{
					snake.push_back(*it);
				}
				snake.pop_back();
				key = Keys::S;
			}
			else if (wantToGO == Keys::D)
			{
				auto newHead = oldHead;
				newHead.x += 1;
				snake.clear();
				snake.push_back(newHead);
				for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
				{
					snake.push_back(*it);
				}
				snake.pop_back();
				key = Keys::D;
			}
			else
			{
				auto newHead = oldHead;
				switch ((int)key)
				{
				case 1:
					newHead.y -= 1;
					break;
				case 2:
					newHead.x -= 1;
					break;
				case 4:
					newHead.y += 1;
					break;
				case 8:
					newHead.x += 1;
					break;
				}

				snake.clear();
				snake.push_back(newHead);
				for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
				{
					snake.push_back(*it);
				}
				snake.pop_back();
			}

			//draw snake - lets hope it is not in a wall
			for (auto& snakeBody : snake)
			{
				this->Draw(snakeBody.x, snakeBody.y, PIXEL_SOLID, FG_RED);
			}
		}

		return true;
	}

private:
	Keys wantToGO = Keys::S;
	Keys key = Keys::S;
	float elapsedTime;
	AStar astar;
	// walls parameters
	std::unordered_set<GridLocation> walls;
	GridLocation start;
	GridLocation end;
	std::vector<GridLocation> snake;
};

int main()
{
	int width;
	int height;
	std::cout << "Please input a width for a graph (10-200)" << std::endl;
	std::cin >> width;
	std::cout << "Please input a height for a graph (10-200)" << std::endl;
	std::cin >> height;

	OneLoneCoder_Example game;
	game.ConstructConsole(width, height, 8, 8);
	game.Start();
	return 0;
}
