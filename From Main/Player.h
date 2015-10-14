#pragma once


class Player
{
public:
	int getMissileAmmo() { return MissileAmmo; }
	int getHealth() { return nHealth; }
	int getMaxHealth() { return maxHealth; }
private:
	//regular bullets are infinite
	int MissileAmmo;//no max for missile ammo
	int nHealth;
	int maxHealth;

}
