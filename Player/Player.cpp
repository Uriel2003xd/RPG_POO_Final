//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>
#include "../Character/Character.h"
#include "../Inventario/inventory.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Combat.h"
#include <cstdlib>
#include <fstream>

using namespace std;

void Player::addItemToInventory(const Item &item) {
    inventory.addItem(item);
}


void Player::removeItemFromInventory(const std::string &itemName) {
    inventory.removeItem(itemName);
}


void Player::useItemFromInventory(const std::string &itemName) {
    inventory.useItem(itemName);
}


void Player::showInventory() const {
    inventory.listItems();
}

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience) : Character(_name, _health, _attack, _defense, _speed, _isPlayer) {
    level = _level;
    experience = _experience;
}


void Player::doAttack(Character *target) {
    target->takeDamage(attack);

    if (target->getHealth() <= 0)
    {
        auto enemyTarget = dynamic_cast<Enemy*>(target);

        if (enemyTarget != nullptr) {
            gainExperience(enemyTarget->getExperience());
        }
    }
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (trueDamage < 0) {
        trueDamage = 0;
    }
    health-= trueDamage;

    cout << name << " Recibio " << trueDamage << " De Ataque!" << endl;

    if(health <= 0) {
        cout << name << " Ha Sido Derrotado!" << endl;
    }
}


Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Selecciona al enemigo que vas atacar: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    cout << getName() << "\nSigue el turno de: " << endl
         << "1. Atacar" << endl
         << "2. Defenderse\n"
         << "3. Inventario" << endl;

    // TODO: Validate input
    cin >> action;
    Action currentAction;
    Character* target = nullptr;

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
                cout << "Vida Restante: " << health << "\n";
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.target = this;
            currentAction.action = [this](){
                defend();
                cout << "Vida Restante: " << health << "\n";
            };
            currentAction.speed = DEFENSA_MAX;
            break;
        case 3:
             handleInventoryAction(enemies);
        default:
            cout << "Accion no valida(1-3)" << endl;

    }

    return currentAction;
}

Action Player::handleInventoryAction(vector<Enemy*> enemies) {
    int inventarioo = 0;
    cout << getName() << "\nInventario: " << endl
         << "1. Hoja afilada   | +5 de Ataque" << endl
         << "2. Pocion de salud| +20 De Vida\n"
         << "3. Pocion de Salud| +50 De Vida\n"
         << "4. Armadura Debil | +3 De Defensa" << endl;

    // TODO: Validate input
    cin >> inventarioo;

    switch(inventarioo) {
        case 1:
            useItemFromInventory("Espada");
            attack += 5;
            cout << "Has usado Hoja Afilada. Aumento actual de ataque: " << attack << "\n";
            removeItemFromInventory("Espada");
            showInventory();
            return takeAction(enemies);
            break;
        case 2:
            useItemFromInventory("Pocion de saludMin");
            health += 20;
            cout << "Has usado una pocionMin de salud. Vida actual: " << health << "\n";
            removeItemFromInventory("Pocion de saludMin");
            showInventory();
            return takeAction(enemies);
        case 3:
            useItemFromInventory("Pocion de salud");
            health += 50;
            cout << "Has usado una pocionMax de salud. Vida actual: " << health << "\n";
            removeItemFromInventory("Pocion de salud");
            showInventory();
            return takeAction(enemies);
        case 4:
            useItemFromInventory("Armadura");
            defense += 3;
            cout << "Has usado una Armadura. Armadura actual: " << defense << "\n";
            removeItemFromInventory("Armadura");
            showInventory();
            return takeAction(enemies);
        default:
            cout << "Accion no valida(1-4)" << endl;
            return takeAction(enemies);
    }

    Action dummyAction;
    return dummyAction;  // This line is just to return something in all code paths.
}

void Player::levelUp() {
    level++;
    cout << getName() << " Acaba de alcanzar un nuevo nivel (Lvl " << level << ")" << endl;

    upgradeStats();
}

void Player::upgradeStats() {

    int statOption;
    while(true) {
        cout << "\nElija una estadistica para actualizar " << getName() << ":" << endl;
        cout << "1. Ataque" << endl << "2. Defensa" << endl << "3. Velocidad" << endl;
        cin >> statOption;

        if (statOption > 0 && statOption < 4) {
            break;
        }
        else {
            cout << "Esa opcion no existe, intentalo de nuevo." << endl;
        }
    }

    int prevAttack, prevDefense, prevSpeed;

    switch (statOption) {
        case 1:
            prevAttack = getAttack();
            subirAtaque();
            cout << getName() << " Aumento el ataque de " << prevAttack << " a " << getAttack() << endl;
            break;
        case 2:
            prevDefense = getDefense();
            subirDefensa();
            cout << getName() << " Aumento la defensa de " << prevDefense << " a " << getDefense() << endl;
            break;
        case 3:
            prevSpeed = getSpeed();
            subirVelocidad();
            cout << getName() << " Aumento la velocidad de " << prevSpeed << " a " << getSpeed() << endl;
            break;
        default:
            cout << " Opcion invalida." << endl;
            break;
    }
}

void Player::gainExperience(int exp) {
    cout << getName() << " Recibio " << exp << " de xp" << endl;

    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}


void Player::serialize(const char* filename) {
    std::ofstream file(filename); {
        if (file.is_open()) {
            file << name << std::endl;
            file << Vida << std::endl;
            file << attack << std::endl;
            file << defense << std::endl;
            file << speed << std::endl;
            file << isPlayer << std::endl;
            file << level << std::endl;
            file << experience << std::endl;
        } else {
            std::cout << "Error al abrir el archivo" << std::endl;
        }
    }
}

// Unserialize the player's attributes
void Player::unserialize(const char *filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> name;
        file >> Vida;
        health = Vida;
        file >> attack;
        file >> defense;
        file >> speed;
        file >> isPlayer;
        file >> level;
        file >> experience;
        file.close();

        cout << "El jugador se cargo exitosamente!" << endl;
        cout << toString() << endl;
    } else {
        std::cerr << "No se pudo abrir el archivo. En su lugar, se utilizarán datos predefinidos." << std::endl;
        while (true) {
            cout << "Introduce el nombre de tu jugador: ";
            cin >> name;
            cout << "¿Estas seguro de que quieres crear un nuevo jugador con el nombre " << name << "? (s/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 's') {
                break;
            }
        }
        Vida = 100;
        health = Vida;
        attack = 15;
        defense = 8;
        speed = 10;
        isPlayer = true;
        level = 1;
        experience = 0;
    }
}