//
// Created by shimm on 12/8/2022.
//

#include "Behaviors.hpp"
#include <iostream>

using namespace std;
namespace DuckSim {

    void QuackBehavior::quack() {
        cout << "quack!" << endl;
    }

    void FlyBehavior::fly() {
        cout << "I can fly" << endl;
    }
}