#pragma once

#include <string>
#include "Skill.h"

class Character
{
private:
	std::string name;
	int hp;
	int maxHp;
	int id;
	int attackPower;
	Skill skill;

public:
	Character(
		int characterId,
		const std::string& characterName,
		int maximumHp,
		int initialAttackPower = 10,
		const Skill& characterSkill = Skill("Special Attack", 20, 2)
	);

	int getId() const;
	int getHp() const;
	int getMaxHp() const;
	int getAttackPower() const;
	const std::string& getName() const;

	void takeDamage(int amount);
	void heal(int amount);
	void revive();
	void attack(Character& target);
	void attack(Character& target, int damage);

	bool isDead() const;
	void printStatus() const;

	const Skill& getSkill() const;
	bool useSkill(Character& target);
	void reduceSkillCooldown();
};