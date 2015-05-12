#ifndef ATTRIBUTEMANAGER_H_
#define ATTRIBUTEMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/components/LookupComponentManager.h"

/**
 * Data structure to represent current/maximum values of attributes.
 */
typedef struct
{
	int cur; ///< Current value
	int max; ///< Max value
} AttributeVal;

/**
 * Data structure for an attribute component.
 */
typedef struct
{
	AttributeVal Str; ///< Strength
	AttributeVal Dex; ///< Dexterity
	AttributeVal Sta; ///< Stamina
	AttributeVal Int; ///< Intelligence
	AttributeVal Per; ///< Perception
	AttributeVal Acu; ///< Acuity
} AttributeComponent;

/**
 * Enumeration for identifying different attributes.
 */
enum attrtype_t {
	Str,
	Dex,
	Sta,
	Int,
	Per,
	Acu
};

/**
 * AttributeManager is the ComponentManager for Attribute components.
 *
 * Attributes define the basic capabilities of an Entity.
 */
class AttributeManager : public LookupComponentManager
{
	public:
		/**
		 * Default and NULL-equivalent AttributeComponent value.
		 */
		static const AttributeComponent NULL_ATTRIBUTE;

		/**
		 * Constructor
		 */
		AttributeManager() {};

		/**
		 * Add the Component to the Entity.
		 *
		 * @param e The Entity to add the Component to.
		 */
		virtual void addComponent(Entity e);

		/**
		 * Remove the Component from the Entity.
		 *
		 * @param e The Entity to remove it from.
		 */
		virtual void removeComponent(Entity e);

		/**
		 * AttributeManager is the ComponentManager sub-class for Attribute.
		 *
		 * @return The Attribute enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Attribute; };

		/**
		 * Retrieve the attributes of the given Entity. Returns NULL_ATTRIBUTE
		 * if the Entity does not have a AttributeComponent.
		 *
		 * @param e Entity to get the attributes of.
		 *
		 * @return The Entity's Attributes
		 */
		AttributeComponent getAttribute(Entity e);
		/**
		 * Set the AttributeComponent for the given Entity.
		 *
		 * @param e The Entity
		 * @param pos Attributes of this Entity
		 */
		void setAttribute(Entity e, AttributeComponent attrs);

		/**
		 * Get the specified attribute for the given Entity.
		 *
		 * @param e The Entity to get the attribute of
		 * @param attr The specific attribute to get
		 *
		 * @return The current and maximum values of the specified attribute
		 */
		AttributeVal getAttribute(Entity e, attrtype_t attr);
		/**
		 * Set the specified attribute for the given Entity.
		 *
		 * @param e The Entity to set the attribute of
		 * @param attr The specific attribute to set
		 * @param val The value to set it to
		 */
		void setAttribute(Entity e, attrtype_t attr, AttributeVal val);

	private:
		std::vector<AttributeComponent> _attributes;
};

#endif