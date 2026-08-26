#include <iostream>
#include <string>
#include <vector>

class Character
{
private:
    std::string name;
    int hp;
    int maxHp;
    int id;

public:
    // TODO 1:
    // 이름과 최대 HP를 받는 생성자
    // name은 전달받은 이름으로 초기화
    // hp와 maxHp는 maximumHp로 초기화
    // maximumHp가 1보다 작으면 hp와 maxHp를 모두 1로 변경
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

    // TODO 2:
    // 음수 피해는 무시
    // HP에서 피해량 차감
    // HP가 0보다 작으면 0으로 제한

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
        // TODO:
        // member의 ID가 targetId와 같으면
        // member의 주소를 반환
        if (member.getId() == targetId)
        {
            return &member;
        }
    }

    // TODO:
    // 끝까지 찾지 못하면 nullptr 반환
    return nullptr;
}

int main()
{
    std::vector<Character> party;

    party.emplace_back(1, "Player", 100);
    party.emplace_back(2, "Mage", 80);
    party.emplace_back(3, "Tank", 150);

    Character* target =
        findCharacterById(party, 2);

    if (target != nullptr)
    {
        target->takeDamage(100);
    }

    Character* missingTarget =
        findCharacterById(party, 99);

    if (missingTarget == nullptr)
    {
        std::cout << "Character 99 not found." << '\n';
    }

    for (const Character& member : party)
    {
        member.printStatus();
    }

    return 0;
}