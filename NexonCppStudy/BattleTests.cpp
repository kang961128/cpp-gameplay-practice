#include "BattleTests.h"
#include "Character.h"
#include "Battle.h"

#include <cassert>
#include <iostream>

void runBattleTests()
{
	Character attacker(1, "Player", 100);
	Character target(2, "Mage", 80);

	BattleResult result = runBattle(attacker, target, 30, 20, false);

	assert(result.turnCount == 3);
	assert(result.winnerId == 1);
	assert(attacker.getHp() == 60);
	assert(target.getHp() == 0);

	std::cout << "[PASS] Battle result calculated correctly" << '\n';
}