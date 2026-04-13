#pragma once
class DamageComponent
{
private:
	std::map<std::string, int> damageAttack;

public:
	DamageComponent(std::string key, int damage = 10);
	~DamageComponent();

	int getDamage(const std::string& type) const;
	void setDamage(const std::string& type, int damage);
};

