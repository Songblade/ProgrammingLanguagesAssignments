//
// Created by shimm on 12/8/2022.
//

#include "Behaviors.hpp"
#include <iostream>

using namespace std;
namespace DuckSim {

    FlyBehavior::FlyBehavior() = default;

    QuackBehavior::QuackBehavior() = default;

    Quack::Quack() = default;

    void FlyWithWings::fly() {
        cout << "I can fly" << endl;
    }

    void FlyNoWay::fly() {} // prints nothing

    void Quack::quack() {
        cout << "quack!" << endl;
    }

    void Squeak::quack() {
        cout << "squeak" << endl;
    }

    void MuteQuack::quack() {} // prints nothing

    void QuackQuack::quack() {
        cout << "quack, quack!" << endl;
    }

}