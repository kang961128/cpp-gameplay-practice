#pragma once

#include <string>

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
	);

	int getId() const;
	int getHp() const;
	const std::string& getName() const;

	void takeDamage(int amount);
	void heal(int amount);
	void revive();
	void attack(Character& target, int damage);

	bool isDead() const;
	void printStatus() const;
};