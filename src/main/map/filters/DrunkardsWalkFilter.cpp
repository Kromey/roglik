#include <stdexcept>

#include "map/filters/DrunkardsWalkFilter.h"
#include "core/Rand.h"

DrunkardsWalkFilter::DrunkardsWalkFilter()
{
	_x = 0;
	_y = 0;

	_use_random_start = true;

	_tile = FloorTile;

	_ratio = 0.30;
}

void DrunkardsWalkFilter::apply(Level& level)
{
	//Our current coordinates
	int x = _x;
	int y = _y;

	//We'll need randomness
	Rand rand(_seed);

	if(_use_random_start)
	{
		x = rand.randInt(0, level.getWidth() - 1);
		y = rand.randInt(0, level.getHeight() - 1);
	}

	//Now we keep track of how many tiles we've applied.
	int tile_count = 0;
	int max_tiles = (level.getWidth() * level.getHeight()) * _ratio;

	//Variables to hold our deltas later on
	int dx;
	int dy;

	while(tile_count < max_tiles)
	{
		if(level.getTile(x, y) != _tile)
		{
			level.setTile(x, y, _tile);
			tile_count++;
		}

		do {
			dx = rand.randInt(2) - 1;
			dy = rand.randInt(2) - 1;
		} while(
			(0 == x && dx < 0) || x + dx >= level.getWidth() ||
			(0 == y && dy < 0) || y + dy >= level.getHeight()
			);

		x += dx;
		y += dy;
	}
}

void DrunkardsWalkFilter::setStart(int x, int y)
{
	_x = x;
	_y = y;

	//We were given a set starting point, let's use it.
	_use_random_start = false;
}

void DrunkardsWalkFilter::useRandomStart(bool random)
{
	_use_random_start = random;
}

void DrunkardsWalkFilter::setTile(Tile tile)
{
	_tile = tile;
}

void DrunkardsWalkFilter::setTileRatio(float ratio)
{
	_ratio = ratio;
}

