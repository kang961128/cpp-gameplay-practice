#include "Character.h"
#include "CharacterSearch.h"
#include "CharacterTests.h"
#include "Battle.h"

#include <iostream>
#include <vector>
#include <limits>
#include <string>

int readPositiveInt(const std::string& prompt)
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
        int attackerId = readPositiveInt("Enter attacker ID: ");
        int targetId = readPositiveInt("Enter target ID: ");

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

    int attackerDamage = readPositiveInt("Enter attacker damage: ");

    runBattle(*attacker, *target, attackerDamage, 20);
    
    return 0;
}