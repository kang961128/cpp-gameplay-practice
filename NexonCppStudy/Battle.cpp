#include "Battle.h"

#include <iostream>

BattleResult runBattle(Character& attacker, Character& target, int attackerDamage, int targetDamage)
{
    int turn = 1;

    while (!attacker.isDead() && !target.isDead())
    {
        std::cout << '\n' << "=== Turn " << turn << " ===" << '\n';

        std::cout << attacker.getName() << " attacks " << target.getName() << " for " << attackerDamage << " damage." << '\n';

        attacker.attack(target, attackerDamage);

        if (!target.isDead())
        {
            std::cout << target.getName() << " attacks " << attacker.getName() << " for " << targetDamage << " damage." << '\n';
            target.attack(attacker, targetDamage);
        }

        std::cout << attacker.getName() << " HP: " << attacker.getHp() << "/" << attacker.getMaxHp() << '\n';
        std::cout << target.getName() << " HP: " << target.getHp() << "/" << target.getMaxHp() << '\n';
        turn++;
    }

    std::cout << '\n' << "=== Battle Result ===" << '\n';

    BattleResult result;

    result.turnCount = turn - 1;

    if (attacker.isDead())
    {
        result.winnerId = target.getId();
        std::cout << target.getName() << " wins." << '\n';
    }
    else
    {
        result.winnerId = attacker.getId();
        std::cout << attacker.getName() << " wins." << '\n';
    }

    return result;
}