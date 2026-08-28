#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cassert>

class Character
{
private:
    std::string name;
    int hp;
    int maxHp;
    int id;

public:
    Character(
        int characterId,
        const std::string& characterName,
        int maximumHp
    )
        : name(characterName),
        hp(maximumHp),
        maxHp(maximumHp),
        id(characterId)
    {
        if (maxHp < 1)
        {
            maxHp = 1;
            hp = maxHp;
        }
    }

    int getId() const
    {
        return id;
    }

    int getHp() const
    {
        return hp;
    }

    const std::string& getName() const
    {
        return name;
    }

    void takeDamage(int amount)
    {
        if (amount <= 0)
        {
            return;
        }

        hp -= amount;

        if (hp < 0)
        {
            hp = 0;
        }
    }

    void heal(int amount)
    {
        if (amount <= 0)
        {
            return;
        }

        if (hp == 0)
        {
            return;
        }

        hp += amount;

        if (hp > maxHp)
        {
            hp = maxHp;
        }
    }

    void revive()
    {
        if (isDead())
        {
            hp = maxHp;
        }
    }

    void attack(Character& target, int damage)
    {
        if (isDead())
        {
            return;
        }

        target.takeDamage(damage);
    }

    bool isDead() const
    {
        return hp == 0;
    }

    void printStatus() const
    {
        std::cout << "[" << id << "] " << name << " HP: " << hp << '\n';

        if (isDead())
        {
            std::cout << name << " died." << '\n';
        }
    }
};

void runCharacterTests()
{
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

    Character livingAttacker(991, "Test", 100);
    Character attackTarget(990, "Test", 100);
    livingAttacker.attack(attackTarget, 30);
    assert(livingAttacker.getHp() == 100);
    assert(attackTarget.getHp() == 70);
    std::cout << "[PASS] Living character can attack" << '\n';

    Character deadAttacker(989, "Test", 100);
    Character protectedTarget(988, "Test", 100);
    deadAttacker.takeDamage(100);
    assert(deadAttacker.isDead());
    deadAttacker.attack(protectedTarget, 30);
    assert(protectedTarget.getHp() == 100);
    std::cout << "[PASS] Dead character cannot attack" << '\n';
}

int readPositiveDamage()
{
    int playerDamage = 0;

    while (true)
    {
        std::cout << "Enter Player damage: ";
        std::cin >> playerDamage;

        if (!std::cin.fail() && playerDamage > 0)
        {
            break;
        }

        std::cout << "Invalid damage." << '\n';

        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return playerDamage;
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

        std::cout << attacker.getName() << " HP: " << attacker.getHp() << '\n';
        std::cout << target.getName() << " HP: " << target.getHp() << '\n';
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

Character* findCharacterById(
    std::vector<Character>& party,
    int targetId
)
{
    for (Character& member : party)
    {
        if (member.getId() == targetId)
        {
            return &member;
        }
    }

    return nullptr;
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

int main()
{
    runCharacterTests();
    runFindCharacterTests();

    std::vector<Character> party;

    party.emplace_back(1, "Player", 100);
    party.emplace_back(2, "Mage", 80);
    party.emplace_back(3, "Tank", 150);

    Character* attacker =
        findCharacterById(party, 1);

    Character* target =
        findCharacterById(party, 2);

    if (attacker == nullptr || target == nullptr)
    {
        std::cout << "Combat character not found." << '\n';
        return 1;
    }

    int playerDamage = readPositiveDamage();

    runBattle(*attacker, *target, playerDamage, 20);
    
    return 0;
}