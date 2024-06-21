#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"


int main() {
    Player *player = new Player("Default", 100, 15, 5, 10);
    player->unserialize("playerInfo.txt");
    Enemy *enemy = new Enemy("Carmencita", 100, 10, 5, 5, 40);
    Enemy *enemy2 = new Enemy("Blanquita", 150, 10, 5, 5, 60);

    // Crear algunos ítems
    Item espada("Espada", "Una hoja afilada Que Aumenta Tu Ataque");
    Item pocionMin("Pocion de saludMin", "PocionMin Que Restaura Tu salud.");
    Item pocion("Pocion de salud", "PocionMax Que Restaura Tu salud.");
    Item armadura("Armadura", "Armadura Que Aumenta TU Defensa");

    // Agregar ítems al inventario del jugador
    player->addItemToInventory(espada);
    player->addItemToInventory(pocionMin);
    player->addItemToInventory(pocion);
    player->addItemToInventory(armadura);

    // Mostrar el inventario del jugador
    player->showInventory();

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;
    return 0;
}
