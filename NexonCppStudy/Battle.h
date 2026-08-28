#pragma once

#include "Character.h"

struct BattleResult
{
	int turnCount;
	int winnerId;
};

BattleResult runBattle(Character& attacker, Character& target, int attackerDamage, int targetDamage, bool showLogs = true);