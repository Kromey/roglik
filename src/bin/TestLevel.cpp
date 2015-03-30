#include <iostream>

#include "map/Level.h"
#include "map/generators/WallsGenerator.h"
#include "map/generators/BigRoomGenerator.h"
#include "map/generators/CaveGenerator.h"

int main()
{
	std::cout << "WallsGenerator:" << std::endl;
	WallsGenerator walls;
	Level lwalls(40, 80, walls);
	lwalls.printLevel();
	std::cout << std::endl << std::endl;

	std::cout << "BigRoomGenerator:" << std::endl;
	BigRoomGenerator room;
	Level lroom(40, 80, room);
	lroom.printLevel();
	std::cout << std::endl << std::endl;

	std::cout << "CaveGenerator:" << std::endl;
	CaveGenerator cave;
	Level lcave(40, 80, cave);
	lcave.printLevel();
	std::cout << std::endl << std::endl;

	return 0;
}