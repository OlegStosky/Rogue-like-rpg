#pragma once

#include<map>
#include "Actor.h"
#include "Map.h"
#include "Const.h"
#include "Vec2i.h"
#include "Item.h"

class Character : public Actor
{
public:
	Character(Vec2i coords, int hp, char symb, int damage) : 
		Actor(coords, symb),
		_hp(hp),
		_damage(damage)
		{
		}

	int hitPoints() const { return _hp; }
	int damage() const { return _damage; };
	Vec2i direction() const { return _direction; }
	Vec2i newCoordinates() const { return Vec2i(_coords) + Vec2i(_direction); }
	void setDamage(int damage){ _damage = damage; }
	void setDirection(Vec2i dir){ _direction = dir; }
	inline bool isDead(){ return (_hp <= 0 ? true : false); }
	
	void act(Map *map) override { move(map); }
	virtual void recieveDamage(int damage) { _hp -= damage; }
	virtual void heal(int ammount) {}
	void collide(Map *map, Actor *target) override { target->collide(map, this); }
	void collide(Map *map, Character *target) override {}
	virtual void collide(Map *map, Knight *target) {}
	virtual void collide(Map *map, Princess *target) {}
	virtual void collide(Map *map, Monster *target) {}
	virtual void collide(Map *map, Medkit *target) {}

protected:
	Vec2i _direction;
	int _hp;
	int _damage;

	virtual void move(Map *map) {}
};

class Knight : public Character
{
public:
	Knight(Vec2i coords, int hp, char symb, int damage);

	void heal(int ammount) override;
	void setDirection(char direction);
	void recieveDamage(int damage) override;
	void collide(Map *map, Actor *target) override { target->collide(map, this); }
	void collide(Map *map, Character *target) override { target->collide(map, this); }
	void collide(Map *map, Medkit *target) override { target->collide(map, this); }
	void collide(Map *map, Monster *target);
	void collide(Map *map, Princess *target);

private:
	std::map<char, Vec2i> _directions;

	void move(Map *map) override;
};


class Princess : public Character
{
public:
	Princess(Vec2i coords, int hp, char symb, int damage) :
		Character(coords, hp, symb, damage)
	{
	}

	void collide(Map *map, Character *target) override { target->collide(map, this); }
	void recieveDamage(int damage) override;
};

class Monster : public Character
{
public:
	Monster(Vec2i coords, int hp, char symb, int damage) :
		Character(coords, hp, symb, damage)
	{
	}

	void collide(Map *map, Actor *target) override { target->collide(map, this); }
	void collide(Map *map, Character *target) override { target->collide(map, this); }
	void collide(Map *map, Knight *target) override;
	void collide(Map *map, Princess *target) override;

private:
	void move(Map *map) override;
};

class Zombie : public Monster
{
public:
	Zombie(Vec2i coords, int hp, char symb, int damage) :
		Monster(coords, hp, symb, damage)
	{
	}

	void heal(int ammount) override;
	void recieveDamage(int damage) override;
};

class Dragon : public Monster
{
public:
	Dragon(Vec2i coords, int hp, char symb, int damage) :
		Monster(coords, hp, symb, damage)
	{
	}

	void heal(int ammount) override;
	void recieveDamage(int damage){};
};

