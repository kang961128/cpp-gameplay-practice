#include "SkillTests.h"
#include "Skill.h"

#include <cassert>
#include <iostream>

void runSkillTests()
{
	Skill skill("Power Strike", 50, 2);

	assert(skill.getName() == "Power Strike");
	assert(skill.getDamage() == 50);
	assert(skill.getCooldown() == 2);
	assert(skill.getRemainingCooldown() == 0);
	assert(skill.isReady());

	bool firstActivation = skill.activate();

	assert(firstActivation);
	assert(!skill.isReady());

	bool secondActivation = skill.activate();

	assert(!secondActivation);
	assert(skill.getRemainingCooldown() == 2);

	skill.reduceCooldown();

	assert(!skill.isReady());
	assert(skill.getRemainingCooldown() == 1);

	skill.reduceCooldown();

	assert(skill.isReady());
	assert(skill.getRemainingCooldown() == 0);

	std::cout << "[PASS] Skill cooldown works correctly" << '\n';

	Skill invalidSkill("Invalid", 0, -1);

	assert(invalidSkill.getDamage() == 1);
	assert(invalidSkill.getCooldown() == 0);
	assert(invalidSkill.isReady());

	std::cout << "[PASS] Invalid skill values corrected" << '\n';
}