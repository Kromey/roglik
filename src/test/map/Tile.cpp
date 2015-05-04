#include "gtest/gtest.h"
#include "map/Tile.h"

TEST(TileTest, WallTileIsOpaque)
{
	Tile t1 = WallTile;

	EXPECT_FALSE(t1.isTransparent());
}

TEST(TileTest, WallTileIsInpassable)
{
	Tile t1 = WallTile;

	EXPECT_FALSE(t1.isPassable());
}

TEST(TileTest, FloorTileIsTransparent)
{
	Tile t1 = FloorTile;

	EXPECT_TRUE(t1.isTransparent());
}

TEST(TileTest, FloorTileIsPassable)
{
	Tile t1 = FloorTile;

	EXPECT_TRUE(t1.isPassable());
}

TEST(TileTest, ClosedDoorTileIsOpaque)
{
	Tile t1 = ClosedDoorTile;

	EXPECT_FALSE(t1.isTransparent());
}

TEST(TileTest, ClosedDoorTileIsInpassable)
{
	Tile t1 = ClosedDoorTile;

	EXPECT_FALSE(t1.isPassable());
}

TEST(TileTest, OpenDoorTileIsTransparent)
{
	Tile t1 = OpenDoorTile;

	EXPECT_TRUE(t1.isTransparent());
}

TEST(TileTest, OpenDoorTileIsPassable)
{
	Tile t1 = OpenDoorTile;

	EXPECT_TRUE(t1.isPassable());
}

TEST(TileTest, FloorEqualsFloor)
{
	Tile floor = FloorTile;
	Tile wall = FloorTile;

	EXPECT_TRUE(floor == wall);
}

TEST(TileTest, FloorDoesNotEqualWall)
{
	Tile floor = FloorTile;
	Tile wall = WallTile;

	EXPECT_TRUE(floor != wall);
}

