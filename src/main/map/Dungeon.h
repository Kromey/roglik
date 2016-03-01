#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <stdint.h>

#include "map/Map.h"

enum dungeon_t
{
	CaveDungeon,
	DungeonDungeon,
	CityDungeon,
	CampDungeon,
	WildernessDungeon
};

/**
 * Container/manager object for a "dungeon", which is just any set of 1 or more
 * Map%s.
 */
class Dungeon
{
	public:
		/**
		 * Default constructor will produce a Cave Dungeon.
		 */
		Dungeon();

		/**
		 * Specify the type of Dungeon to instantiate. The type governs how many
		 * Map%s and how each is generated.
		 *
		 * @param type The type to create
		 */
		Dungeon(dungeon_t type);

		/**
		 * Retrieve the Dungeon's seed.
		 *
		 * @return The seed.
		 */
		uint32_t getDungeonSeed();
		/**
		 * Set the seed for the Dungeon.
		 *
		 * @param seed The seed to use.
		 */
		void setDungeonSeed(uint32_t seed);

		/**
		 * Move to a new level of the Dungeon.
		 *
		 * This results in the Dungeon generating a new Map.
		 *
		 * @param new_level The new level to move to
		 */
		void changeDungeonLevel(int new_level);

		/**
		 * Retrieve the current Map.
		 *
		 * @return Reference to the current Dungeon Map.
		 */
		Map& getMap();

	private:
		/**
		 * Generate a Map for the current Dungeon level.
		 */
		void generateDungeonMap();

		/**
		 * Retrieve the Map-specific seed.
		 *
		 * @return Seed for the current Map.
		 */
		uint32_t getMapSeed();

		/**
		 * The Dungeon's seed.
		 */
		uint32_t _seed;

		/**
		 * The type for this Dungeon.
		 */
		dungeon_t _type;

		/**
		 * Current level of the Dungeon.
		 */
		int _current_level;

		/**
		 * The current Dungeon Map.
		 */
		Map* _map;
};

#endif