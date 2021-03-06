from roglick.engine import event
from roglick.engine.ecs import EntityManager,SystemManager
from roglick.engine.panels import PanelManager,PanelContext
from roglick.events import PreInputEvent,QuitEvent,NewMapEvent,SpawnEntityEvent
from roglick import components,systems
from roglick.world import WorldManager
from roglick import logging, panels


logger = logging.getLogger(__name__)


class GameMaster(object):
    def __init__(self):
        logger.info("Initializing game...")

        # We need an EntityManager of course
        logger.debug("Instantiating EntityManager")
        self._entities = EntityManager()

        # We need a world for the game to take place in
        logger.debug("Initializing world")
        self._init_world()

        # Systems make everything "go"
        logger.debug("Initializing systems")
        self._init_systems()

        # And of course we need a way to display it all
        logger.debug("Initializing display")
        self._init_display()

        # With all that done, now we can register event handlers
        logger.debug("Registering event handlers")
        self._register_event_handlers()

        # Generate a dungeon for us to play in
        # TODO: Eventually we're going to start in the Overworld instead...
        logger.debug("Generating Dungeon")
        self._world.generate_dungeon()

        # We need a PC, otherwise the player will be very bored!
        logger.debug("Initializing PC")
        self._init_pc()

        # This flag, when True, keeps our game loop running
        self._run = True

        logger.info("Game initialized!")

    @event.event_handler(PreInputEvent)
    def draw_handler(self, myevent):
        self._display.draw_panels()

    @event.event_handler(QuitEvent)
    def quit_handler(self, quitevent):
        self._run = False

    @event.event_handler(NewMapEvent)
    def redraw_handler(self, redrawevent):
        self._display.clear()

    def run(self):
        while self._run:
            self._systems.execute()

    def _init_world(self):
        self._world = WorldManager(self._entities)

    def _init_systems(self):
        self._systems = SystemManager(self._entities, self._world)

        # Populate our Systems
        self._systems.add_system(systems.FatigueSystem())
        self._systems.add_system(systems.MovementSystem())
        self._systems.add_system(systems.InteractionSystem())
        self._systems.add_system(systems.FoVSystem())
        self._systems.add_system(systems.SkillSystem())
        self._systems.add_system(systems.CombatSystem())
        self._systems.add_system(systems.HealthSystem())
        self._systems.add_system(systems.InputSystem())

    def _init_display(self):
        self._display = PanelManager('Ro\'glick')
        self._display.set_context(PanelContext.MapScreen)

        self._display.add_panel(
                panels.MapPanel(
                    self._entities, self._world, PanelContext.MapScreen))
        self._display.add_panel(panels.LogPanel(PanelContext.MapScreen, y=-5))

    def _register_event_handlers(self):
        # Start with ourself
        event.register(self)

        # WorldManager runs before our systems
        event.register(self._world)

        # Register system event handlers
        for system in self._systems.systems:
            event.register(system)

        # Finally register panels
        for panel in self._display.panels:
            event.register(panel)

    def _init_pc(self):
        # Get a random place to put the PC
        x,y = self._world.current_map.get_random_cell()
        pc_pos = components.PositionComponent(x, y)
        pc_sprite = components.SpriteComponent('@')

        self._entities.set_component(self._entities.pc, pc_pos)
        self._entities.set_component(self._entities.pc, pc_sprite)
        self._entities.set_component(self._entities.pc, components.FoVComponent())
        self._entities.set_component(self._entities.pc, components.FatigueComponent())
        self._entities.set_component(self._entities.pc, components.AttributesComponent(15,13,11,9))

        pc_skills = components.SkillsComponent()
        pc_skills['melee.swords.short_sword'] = components.SkillsComponent.Skill(12)
        self._entities.set_component(self._entities.pc, pc_skills)

        event.dispatch(SpawnEntityEvent(self._entities.pc))

