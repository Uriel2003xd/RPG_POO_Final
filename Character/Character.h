//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include <string>

using namespace std;

class Character {
protected:
    char name[30];
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    int Vida;
    bool isDefending = false;

public:
    Character(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    //TODO: Implementar metodo de defensa
    //Incrementar la defensa un 20% solo por el turno actual
    void defend(Character *const pCharacter);
    void resetDefensa();
    void resetHealth();
    bool flee(Character* target);
    char* getName();
    int getHealth();
    int getAttack();
    int getDefense();
    int getVidaBase();
    bool getIsPlayer();
    bool getDefender();
    int getSpeed();
    string toString();

    void defend();
    void subirAtaque();
    void subirDefensa();
    void subirVelocidad();

};


#endif //RPG_CHARACTER_H
