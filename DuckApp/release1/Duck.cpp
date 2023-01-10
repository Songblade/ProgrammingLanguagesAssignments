//
// Created by shimm on 12/8/2022.
//

#include "Duck.hpp"
#include <iostream>
using namespace std;
namespace DuckSim {
    void Duck::quack() {
        cout << "quack!" << endl;
    }

    void Duck::swim() {
        cout << "Look, I am swimming" << endl;
    }

    void Duck::fly() {
        cout << "I can fly" << endl;
    }
}

