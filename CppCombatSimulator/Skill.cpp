#include "Skill.h"

Skill::Skill(
	const std::string& skillName,
	int skillDamage,
	int cooldownTurns
)
	: name(skillName),
	damage(skillDamage),
	cooldown(cooldownTurns),
	remainingCooldown(0)
{
	if (damage < 1)
	{
		damage = 1;
	}

	if (cooldown < 0)
	{
		cooldown = 0;
	}
}

const std::string& Skill::getName() const
{
	return name;
}

int Skill::getDamage() const
{
	return damage;
}

int Skill::getCooldown() const
{
	return cooldown;
}

int Skill::getRemainingCooldown() const
{
	return remainingCooldown;
}

bool Skill::isReady() const
{
	return remainingCooldown == 0;
}

bool Skill::activate()
{
	if (!isReady())
	{
		return false;
	}

	remainingCooldown = cooldown;
	return true;
}

void Skill::reduceCooldown()
{
	if (remainingCooldown > 0)
	{
		remainingCooldown--;
	}
}