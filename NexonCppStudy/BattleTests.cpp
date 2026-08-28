#include "BattleTests.h"
#include "Character.h"
#include "Battle.h"

#include <cassert>
#include <iostream>

void runBattleTests()
{
	Character attacker(1, "Player", 200, 30, Skill("Power Shot", 50, 2));
	Character target(2, "Mage", 200, 20, Skill("Fireball", 40, 2));

	BattleResult result = runBattle(attacker, target, false);

	assert(result.turnCount == 6);
	assert(result.winnerId == 1);
	assert(attacker.getHp() == 60);
	assert(target.getHp() == 0);

	std::cout << "[PASS] Battle uses skills and cooldowns correctly" << '\n';
}