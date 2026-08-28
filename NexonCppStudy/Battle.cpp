#include "Battle.h"

#include <iostream>

BattleResult runBattle(Character& attacker, Character& target, bool showLogs)
{
    int turn = 1;

    while (!attacker.isDead() && !target.isDead())
    {
        if (showLogs)
        {
            std::cout << '\n' << "=== Turn " << turn << " ===" << '\n';

            std::cout
                << attacker.getName() << " attacks "
                << target.getName() << " for "
                << attacker.getAttackPower() << " damage." << '\n';
        }

        attacker.attack(target);

        if (!target.isDead())
        {
            if (showLogs)
            {
                std::cout
                    << target.getName() << " attacks "
                    << attacker.getName() << " for "
                    << target.getAttackPower() << " damage." << '\n';
            }
            
            target.attack(attacker);
        }

        if (showLogs)
        {
            std::cout
                << attacker.getName() << " HP: "
                << attacker.getHp() << "/"
                << attacker.getMaxHp()<< '\n';

            std::cout
                << target.getName() << " HP: "
                << target.getHp() << "/"
                << target.getMaxHp() << '\n';
        }
        
        turn++;
    }

    BattleResult result;

    result.turnCount = turn - 1;

    if (attacker.isDead())
    {
        result.winnerId = target.getId();
    }
    else
    {
        result.winnerId = attacker.getId();
    }

    if (showLogs)
    {
        std::cout << '\n' << "=== Battle Result ===" << '\n';

        if (attacker.isDead())
        {
            std::cout << target.getName() << " wins." << '\n';
        }
        else
        {
            std::cout << attacker.getName() << " wins." << '\n';
        }
    }

    return result;
}