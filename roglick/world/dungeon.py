from .level import LevelManager
from roglick.engine import event,random
from roglick import components
from roglick.events import MoveEvent,ClimbDownEvent,ClimbUpEvent,NewMapEvent,MessageEvent,AttackEvent,SpawnEntityEvent
from roglick.mobs import npcs


class DungeonManager(object):
    """This object manages all data for a particular dungeon."""
    def __init__(self, world_manager, dungeon_seed):
        self._wm = world_manager
        self._random = random.Random(dungeon_seed)

        self._seeds = []
        self._stairs = []
        self._depth = 0

        self.create_level()

    def create_level(self):
        seed = self.get_level_seed(self._depth)
        self._level = LevelManager(self, seed)

        maps = 1
        while not self._level_valid():
            # Didn't get a valid map, re-build it
            print("Discarding map {} and trying again...".format(maps))
            self._level.map.make_map()
            maps += 1

        stairs_up = self.get_level_stairs(self._depth-1)
        stairs_down = self.get_level_stairs(self._depth)

        self._level.add_stairs_up(stairs=stairs_up)
        self._level.add_stairs_down(stairs=stairs_down)

        self._add_npcs()

        event.dispatch(NewMapEvent())

    @property
    def depth(self):
        """Return the current depth.

        For simplicity, we simply decide that each level is 10ft.
        """
        return self._depth * 10

    @property
    def current_level(self):
        return self._level

    def _level_valid(self):
        # Ensure all stairs go on valid tiles
        stairs = self.get_level_stairs(self._depth-1)

        for x,y in stairs:
            if not self._level.map.tiles[x][y].passable:
                return False

        return True

    def get_level_stairs(self, level):
        if level < 0:
            return []

        while len(self._stairs) <= level:
            self._stairs.append(self.build_level_stairs(len(self._stairs)))

        return self._stairs[level]

    def build_level_stairs(self, level):
        down_stairs = []
        for n in range(2,5):
            x,y = self.current_level.map.get_random_cell()
            down_stairs.append((x,y))

        return down_stairs

    def get_level_seed(self, level):
        while len(self._seeds) <= level:
            self._seeds.append(self._random.get_int())

        return self._seeds[level]

    def _add_npcs(self, attempts=150):
        for n in range(attempts):
            x = random.get_int(0, self.current_level.map.width-1)
            y = random.get_int(0, self.current_level.map.height-1)

            if self.current_level.map.tiles[x][y].passable:
                self._spawn_npc(x,y)

    def _spawn_npc(self, x, y):
        e = self._wm._em.create_entity()

        npc = npcs.random()

        self._wm._em.set_component(e, components.PositionComponent(x,y))
        self._wm._em.set_component(e, components.SpriteComponent(**npc['sprite']))
        self._wm._em.set_component(e, components.AttributesComponent(**npc['attributes']))

        npc_skills = components.SkillsComponent()
        for skill in npc['skills']:
            npc_skills[skill] = components.SkillsComponent.Skill(npc['skills'][skill])
        self._wm._em.set_component(e, npc_skills)

        event.dispatch(SpawnEntityEvent(e))

    def map_handler(self, myevent):
        self.current_level.map_handler(myevent)

        # Dungeon-level processing of the event, if not stopped
        if myevent.propagate:
            pcpos = self._wm._em.get_component(self._wm._em.pc, components.PositionComponent)

            # Post-process Climb events
            if myevent.__class__ == ClimbDownEvent:
                # Descending to a deeper level
                self._depth += 1
                self.create_level()
                event.dispatch(MessageEvent("You descend the stairs..."))
            elif myevent.__class__ == ClimbUpEvent:
                # Ascending to a higher level
                self._depth = max(0, self._depth - 1)
                self.create_level()
                event.dispatch(MessageEvent("You climb the stairs..."))
            elif myevent.__class__ == MoveEvent:
                # Check if the entity is "bumping" into another
                epos = self._wm._em.get_component(myevent.entity, components.PositionComponent)

                tx = epos.x + myevent.dx
                ty = epos.y + myevent.dy

                for entity, comps in self._wm._em.get_entities_with_component(
                        components.PositionComponent):
                    pos = comps[components.PositionComponent]
                    if (tx,ty) == (pos.x,pos.y):
                        # Entity occupies target space, cancel movement
                        myevent.stop()
                        # "Bumping" someone else is an attack!
                        event.dispatch(AttackEvent(myevent.entity, entity))
                        # No need to continue searching entities
                        break

