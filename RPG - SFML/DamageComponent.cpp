#include "stdafx.h"
#include "DamageComponent.h"

DamageComponent::DamageComponent(std::string key, int damage)
{
	this->damageAttack[key] = damage;
}
DamageComponent::~DamageComponent()
{
}

int DamageComponent::getDamage(const std::string& type) const
{
	return this->damageAttack.at(type);
}
void DamageComponent::setDamage(const std::string& type, int damage)
{
	this->damageAttack[type] = damage;
}