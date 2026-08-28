#include "Battle.h"
#include "Character.h"
#include "Skill.h"

#include <iostream>

namespace
{
    void performAction(Character& actor, Character& opponent, bool showLogs)
    {
        if (actor.getSkill().isReady())
        {
            if (showLogs)
            {
                std::cout
                    << actor.getName()
                    << " uses "
                    << actor.getSkill().getName()
                    << " on "
                    << opponent.getName()
                    << " for "
                    << actor.getSkill().getDamage()
                    << " damage."
                    << '\n';
            }

            actor.useSkill(opponent);
            return;
        }

        if (showLogs)
        {
            std::cout
                << actor.getName()
                << " attacks "
                << opponent.getName()
                << " for "
                << actor.getAttackPower()
                << " damage."
                << '\n';
        }

        actor.attack(opponent);
        actor.reduceSkillCooldown();
    }
}


BattleResult runBattle(Character& attacker, Character& target, bool showLogs)
{
    int turn = 1;

    while (!attacker.isDead() && !target.isDead())
    {
        if (showLogs)
        {
            std::cout << '\n' << "=== Turn " << turn << " ===" << '\n';
        }

        performAction(attacker, target, showLogs);

        if (!target.isDead())
        {
            performAction(target, attacker, showLogs);
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