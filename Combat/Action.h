//
// Created by Victor Navarro on 29/02/24.
//

#ifndef RPG_ACTION_H
#define RPG_ACTION_H
#include <functional>
#include "../Character/Character.h"

using namespace std;

const int DEFENSA_MAX = 999;

class Action {
public:
    Action(int _speed, function<void(void)> _action, Character *_subscriber, Character *_target,
           Character *_inventario);

//velocidad de quien realiza la accion
    int speed = 0;

    //Quien recibe de la accion
    Character* target = nullptr;

    //Quien realiza la accion
    Character* subscriber = nullptr;

    //Puntero a una función que no recibe parametros y no devuelve nada
    function<void(void)> action = nullptr;
    Action(int _speed, function<void(void)> _action, Character* _subscriber, Character* _target);
    Action();

    bool operator<(const Action& other) const;
};


#endif //RPG_ACTION_H
