#pragma once

#include "Character.h"

struct BattleResult
{
	int turnCount;
	int winnerId;
};

BattleResult runBattle(Character& attacker, Character& target, bool showLogs = true);