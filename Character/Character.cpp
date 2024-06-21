//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include <string.h>
Character::Character(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    strcpy(name, _name);
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

char* Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getVidaBase() {
    return Vida;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::getDefender() {
    return isDefending;
}

string Character::toString() {
    return "Nombre: " + string(name) + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}


void Character::subirAtaque() {
    attack = attack + 2;
}

void Character::subirDefensa() {
    defense = defense + 2;
}

void Character::subirVelocidad() {
    speed = speed + 3;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}

void Character::defend() {
    defense = defense * 2;
    isDefending = true;
}

void Character::resetDefensa() {
    defense = defense / 2;
    isDefending = false;
}

void Character::resetHealth() {
    health = Vida;
}

