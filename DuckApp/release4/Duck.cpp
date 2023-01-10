//
// Created by shimm on 12/8/2022.
//

#include "Duck.hpp"
#include <iostream>
using namespace std;
namespace DuckSim {

    static int highestCounter = 0;

    void Duck::swim() {
        cout << "Look, I am swimming" << endl;
    }

    void Duck::performQuack() {
        sound->quack();
    }

    void Duck::performFly() {
        flight->fly();
    }

    void Duck::setFlyBehavior(FlyBehavior* flying) {
        flight = flying;
    }

    void Duck::setQuackBehavior(QuackBehavior* quacking) {
        sound = quacking;
    }

    int Duck::getIdentifier() {
        return identifier;
    }

    Duck::Duck(FlyBehavior* flying, QuackBehavior* quacking) :
    sound(quacking), flight(flying), identifier(++highestCounter){}

}