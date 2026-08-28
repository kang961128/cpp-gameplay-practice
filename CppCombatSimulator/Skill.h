#pragma once

#include <string>

class Skill
{
private:
	std::string name;
	int damage;
	int cooldown;
	int remainingCooldown;

public:
	Skill(
		const std::string& skillName,
		int skillDamage,
		int cooldownTurns
	);

	const std::string& getName() const;
	int getDamage() const;
	int getCooldown() const;
	int getRemainingCooldown() const;

	bool isReady() const;
	bool activate();
	void reduceCooldown();
};