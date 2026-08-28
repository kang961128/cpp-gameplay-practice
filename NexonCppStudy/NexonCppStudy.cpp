#include "Character.h"
#include "CharacterSearch.h"
#include "CharacterTests.h"

#include <iostream>
#include <vector>
#include <limits>
#include <string>

int readPositiveint(const std::string& prompt)
{
    int value = 0;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (!std::cin.fail() && value > 0)
        {
            break;
        }

        std::cout << "Invalid value." << '\n';

        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

void runBattle(Character& attacker, Character& target, int attackerDamage, int targetDamage)
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

    if (attacker.isDead())
    {
        std::cout << target.getName() << " wins." << '\n';
    }
    else
    {
        std::cout << attacker.getName() << " wins." << '\n';
    }
}

int main()
{
    runCharacterTests();
    runFindCharacterTests();

    std::vector<Character> party;

    party.emplace_back(1, "Player", 100);
    party.emplace_back(2, "Mage", 80);
    party.emplace_back(3, "Tank", 150);

    std::cout << '\n' << "=== Character List ===" << '\n';

    for (const Character& member : party)
    {
        member.printStatus();
    }

    Character* attacker = nullptr;
    Character* target = nullptr;

    while (true)
    {
        int attackerId = readPositiveint("Enter attacker ID: ");
        int targetId = readPositiveint("Enter target ID: ");

        attacker = findCharacterById(party, attackerId);
        target = findCharacterById(party, targetId);

        if (attacker == nullptr || target == nullptr)
        {
            std::cout << "Combat character not found." << '\n';
            continue;
        }

        if (attacker == target)
        {
            std::cout << "Attacker and target must be different." << '\n';
            continue;
        }

        break;
    }        

    int attackerDamage = readPositiveint("Enter attacker damage: ");

    runBattle(*attacker, *target, attackerDamage, 20);
    
    return 0;
}