#include "gtest/gtest.h"
#include "entity/managers/SkillManager.h"

TEST(SkillManagerTest, SkillManagerIsCorrectType)
{
	SkillManager sm;

	EXPECT_EQ(Skill, sm.getComponentType());
}

TEST(SkillManagerTest, EntityDoesNotHaveComponent)
{
	SkillManager sm;
	Entity e = 5;

	EXPECT_FALSE(sm.entityHasComponent(e));
}

TEST(SkillManagerTest, AddedEntityHasComponent)
{
	SkillManager sm;
	Entity e = 5;

	sm.addComponent(e);

	EXPECT_TRUE(sm.entityHasComponent(e));
}

TEST(SkillManagerTest, RemoveComponent)
{
	SkillManager sm;
	Entity e = 5;

	sm.addComponent(e);

	ASSERT_TRUE(sm.entityHasComponent(e));

	sm.removeComponent(e);

	EXPECT_FALSE(sm.entityHasComponent(e));
}

TEST(SkillManagerTest, SkillDefaultsToNULL)
{
	SkillManager sm;
	Entity e = 5;

	sm.addComponent(e);

	EXPECT_EQ(sm.getNullComponent().size(), sm.getComponent(e).size());
}

TEST(SkillManagerTest, SetSkill)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent melee = {1,2};
	SkillComponent swords = {5,4};

	sm.setComponent(e, Melee, melee);
	sm.setComponent(e, Swords, swords);

	EXPECT_EQ(melee.ranks, sm.getComponent(e, Melee).ranks);
	EXPECT_EQ(melee.xp, sm.getComponent(e, Melee).xp);

	EXPECT_EQ(swords.ranks, sm.getComponent(e, Swords).ranks);
	EXPECT_EQ(swords.xp, sm.getComponent(e, Swords).xp);

	++melee.ranks;
	++melee.xp;
	++swords.ranks;
	++swords.xp;

	sm.setComponent(e, Melee, melee);
	sm.setComponent(e, Swords, swords);

	EXPECT_EQ(melee.ranks, sm.getComponent(e, Melee).ranks);
	EXPECT_EQ(melee.xp, sm.getComponent(e, Melee).xp);

	EXPECT_EQ(swords.ranks, sm.getComponent(e, Swords).ranks);
	EXPECT_EQ(swords.xp, sm.getComponent(e, Swords).xp);
}

TEST(SkillManagerTest, SkillLevel)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent melee = {3,2};
	SkillComponent swords = {6,4};
	SkillComponent bsword = {8,4};

	sm.setComponent(e, Melee, melee);
	sm.setComponent(e, Swords, swords);
	sm.setComponent(e, BastardSword, bsword);

	EXPECT_EQ(3, sm.getSkillLevel(e, Melee));
	EXPECT_EQ(7, sm.getSkillLevel(e, Swords));
	EXPECT_EQ(11, sm.getSkillLevel(e, BastardSword));
}

TEST(SkillManagerTest, AddXP)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent bsword = {5,0};

	sm.setComponent(e, BastardSword, bsword);

	EXPECT_EQ(0, sm.getComponent(e, Melee).xp);
	EXPECT_EQ(0, sm.getComponent(e, Swords).xp);
	EXPECT_EQ(0, sm.getComponent(e, BastardSword).xp);

	sm.addXP(e, BastardSword, 4);

	//Remember we scale XP so that we can reliably halve it a few times
	EXPECT_EQ(1000, sm.getComponent(e, Melee).xp);
	EXPECT_EQ(2000, sm.getComponent(e, Swords).xp);
	EXPECT_EQ(4000, sm.getComponent(e, BastardSword).xp);
}

TEST(SkillManagerTest, SkillChecksFollowExpectedOdds)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent bsword = {9,0};

	sm.setComponent(e, BastardSword, bsword);

	int iters = 3000;
	int successes = 0;
	float ratio = 0.3750;

	/**
	 * Based on calculations from AnyDice, a 3d6 roll should come in at 9 or
	 * lower 37.50% of the time. We allow some fudge because random.
	 */
	int upper_bound = iters * (ratio + 0.03);
	int lower_bound = iters * (ratio - 0.03);

	for(int i = 0; i < iters; i++)
	{
		if(sm.check(e, BastardSword))
		{
			++successes;
		}
	}

	EXPECT_GE(upper_bound, successes);
	EXPECT_LE(lower_bound, successes);
}

TEST(SkillManagerTest, ModifiedSkillChecksFollowExpectedOdds)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent bsword = {7,0};

	sm.setComponent(e, BastardSword, bsword);

	int iters = 3000;
	int successes = 0;
	float ratio = 0.3750;

	/**
	 * Based on calculations from AnyDice, a 3d6 roll should come in at 9 or
	 * lower 37.50% of the time. We allow some fudge because random.
	 */
	int upper_bound = iters * (ratio + 0.03);
	int lower_bound = iters * (ratio - 0.03);

	for(int i = 0; i < iters; i++)
	{
		if(sm.check(e, BastardSword, 2))
		{
			++successes;
		}
	}

	EXPECT_GE(upper_bound, successes);
	EXPECT_LE(lower_bound, successes);
}

