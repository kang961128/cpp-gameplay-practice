#include <iostream>
#include <string>
#include <vector>
#include <limits>

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
        if (amount < 0)
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

int main()
{
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

    int turn = 1;

    while (!attacker->isDead() && !target->isDead())
    {
        std::cout << '\n' << "=== Turn " << turn << " ===" << '\n';

        std::cout << attacker->getName() << " attacks " << target->getName() << " for " << playerDamage << " damage." << '\n';

        attacker->attack(*target, playerDamage);

        if (!target->isDead())
        {
            std::cout << target->getName() << " attacks " << attacker->getName() << " for 20 damage." << '\n';
            target->attack(*attacker, 20);
        }

        std::cout << attacker->getName() << " HP: " << attacker->getHp() << '\n';
        std::cout << target->getName() << " HP: " << target->getHp() << '\n';
        turn++;
    }

    std::cout << '\n' << "=== Battle Result ===" << '\n';

    if (attacker->isDead())
    {
        std::cout << target->getName() << " wins." << '\n';
    }
    else
    {
        std::cout << attacker->getName() << " wins." << '\n';
    }
    
    /*Character* missingTarget =
        findCharacterById(party, 99);

    if (missingTarget == nullptr)
    {
        std::cout << "Character 99 not found." << '\n';
    }

    for (const Character& member : party)
    {
        member.printStatus();
    }*/
    
    return 0;
}