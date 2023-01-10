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

    FlyWithWings::FlyWithWings(int speed) {
        if (speed < 1 || speed > 5) {
            throw std::out_of_range("Speed out of range");
        }
        FlyWithWings::speed = speed;
    }

    void FlyWithWings::fly() {
        cout << "I can";
        for (int i = 0; i < speed; i++) {
            cout << " fly";
        }
        cout << endl;
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