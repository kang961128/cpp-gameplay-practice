#include "Character.h"

#include <iostream> //std::cout

Character::Character(
	int characterId,
	const std::string& characterName,
	int maximumHp,
    int initialAttackPower,
    const Skill& characterSkill
)
	: name(characterName),
	hp(maximumHp),
	maxHp(maximumHp),
	id(characterId),
    attackPower(initialAttackPower),
    skill(characterSkill)
{
	if (maxHp < 1)
	{
		maxHp = 1;
		hp = maxHp;
	}

    if (attackPower < 1)
    {
        attackPower = 1;
    }
}

int Character::getId() const
{
	return id;
}

int Character::getHp() const
{
	return hp;
}

int Character::getMaxHp() const
{
    return maxHp;
}

int Character::getAttackPower() const
{
    return attackPower;
}

const std::string& Character::getName() const
{
	return name;
}

void Character::takeDamage(int amount)
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

void Character::heal(int amount)
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

void Character::revive()
{
    if (isDead())
    {
        hp = maxHp;
    }
}

void Character::attack(Character& target)
{
    attack(target, attackPower);
}

void Character::attack(Character& target, int damage)
{
    if (isDead())
    {
        return;
    }

    target.takeDamage(damage);
}

bool Character::isDead() const
{
    return hp == 0;
}

void Character::printStatus() const
{
    std::cout
        << "[" << id << "] "
        << name
        << " HP: " << hp << "/" << maxHp
        << " Attack: " << attackPower
        << '\n';

    std::cout
        << "    Skill: " << skill.getName()
        << " Damage: " << skill.getDamage()
        << " Cooldown: " << skill.getCooldown()
        << '\n';

    if (isDead())
    {
        std::cout << name << " died." << '\n';
    }
}

const Skill& Character::getSkill() const
{
    return skill;
}

bool Character::useSkill(Character& target)
{
    if (isDead() || target.isDead())
    {
        return false;
    }

    if (!skill.activate())
    {
        return false;
    }

    target.takeDamage(skill.getDamage());
    return true;
}

void Character::reduceSkillCooldown()
{
    skill.reduceCooldown();
}