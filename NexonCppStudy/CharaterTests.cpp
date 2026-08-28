#include "CharacterTests.h"
#include "Character.h"
#include "CharacterSearch.h"

#include <cassert>
#include <iostream>
#include <vector>

void runCharacterTests()
{
    Character attackPowerCharacter(775, "Test", 100, 30);
    assert(attackPowerCharacter.getAttackPower() == 30);
    std::cout << "[PASS] Attack power initialized" << '\n';

    Character invalidAttackPowerCharacter(776, "Test", 100, 0);
    assert(invalidAttackPowerCharacter.getAttackPower() == 1);
    std::cout << "[PASS] Invalid attack power corrected" << '\n';

    Character invalidMaxHpCharacter(777, "Test", 0);
    assert(invalidMaxHpCharacter.getHp() == 1);
    assert(invalidMaxHpCharacter.getMaxHp() == 1);
    assert(!invalidMaxHpCharacter.isDead());
    std::cout << "[PASS] Invalid max HP corrected" << '\n';

    Character testCharacter(999, "Test", 100);
    testCharacter.takeDamage(30);
    assert(testCharacter.getHp() == 70);
    std::cout << "[PASS] Normal damage" << '\n';

    Character excessiveDamageCharacter(998, "Test", 100);
    excessiveDamageCharacter.takeDamage(150);
    assert(excessiveDamageCharacter.getHp() == 0);
    std::cout << "[PASS] Excessive damage" << '\n';

    Character negativeDamageCharacter(997, "Test", 100);
    negativeDamageCharacter.takeDamage(-10);
    assert(negativeDamageCharacter.getHp() == 100);
    std::cout << "[PASS] Negative damage ignored" << '\n';

    Character zeroDamageCharacter(996, "Test", 100);
    zeroDamageCharacter.takeDamage(0);
    assert(zeroDamageCharacter.getHp() == 100);
    std::cout << "[PASS] Zero damage has no effect" << '\n';

    Character normalHealingCharacter(995, "Test", 100);
    normalHealingCharacter.takeDamage(50);
    normalHealingCharacter.heal(20);
    assert(normalHealingCharacter.getHp() == 70);
    std::cout << "[PASS] Normal healing" << '\n';

    Character excessiveHealingCharacter(994, "Test", 100);
    excessiveHealingCharacter.takeDamage(20);
    excessiveHealingCharacter.heal(50);
    assert(excessiveHealingCharacter.getHp() == 100);
    std::cout << "[PASS] Healing capped at max HP" << '\n';

    Character deadHealingCharacter(993, "Test", 100);
    deadHealingCharacter.takeDamage(100);
    assert(deadHealingCharacter.isDead());
    deadHealingCharacter.heal(50);
    assert(deadHealingCharacter.isDead());
    assert(deadHealingCharacter.getHp() == 0);
    std::cout << "[PASS] Dead character cannot heal" << '\n';

    Character reviveCharacter(992, "Test", 100);
    reviveCharacter.takeDamage(100);
    assert(reviveCharacter.isDead());
    assert(reviveCharacter.getHp() == 0);
    reviveCharacter.revive();
    assert(reviveCharacter.getHp() == 100);
    assert(!reviveCharacter.isDead());
    std::cout << "[PASS] Revive restores max HP" << '\n';

    Character livingAttacker(991, "Test", 100, 30);
    Character attackTarget(990, "Test", 100);
    livingAttacker.attack(attackTarget);
    assert(livingAttacker.getHp() == 100);
    assert(attackTarget.getHp() == 70);
    std::cout << "[PASS] Living character uses its attack power" << '\n';

    Character deadAttacker(989, "Test", 100, 30);
    Character protectedTarget(988, "Test", 100);
    deadAttacker.takeDamage(100);
    assert(deadAttacker.isDead());
    deadAttacker.attack(protectedTarget);
    assert(protectedTarget.getHp() == 100);
    std::cout << "[PASS] Dead character cannot attack" << '\n';
}

void runFindCharacterTests()
{
    std::vector<Character> testParty;

    testParty.emplace_back(1, "Player", 100);
    testParty.emplace_back(2, "Mage", 80);
    testParty.emplace_back(3, "Tank", 150);

    Character* foundCharacter =
        findCharacterById(testParty, 2);

    assert(foundCharacter != nullptr);
    assert(foundCharacter->getId() == 2);
    assert(foundCharacter->getName() == "Mage");

    std::cout << "[PASS] Existing character found by ID" << '\n';

    Character* missingCharacter =
        findCharacterById(testParty, 99);

    assert(missingCharacter == nullptr);

    std::cout << "[PASS] Missing character returns nullptr" << '\n';
}