//
// Created by shimm on 12/8/2022.
//

#include "AllMyDucks.hpp"
#include <iostream>
using namespace std;
namespace DuckSim {
    void MarbledDuck::display() {
        cout << "Displaying a Marbled duck on the screen" << endl;
    }

    void MarbledDuck::performQuack() {
        quack();
    }

    void MarbledDuck::performFly() {
        fly();
    }

//------------------------------------------------------------------------------

    void WhitePekinDuck::quack() {
        cout << "quack, quack!" << endl;
    }

    void WhitePekinDuck::display() {
        cout <<  "Displaying a White Pekin duck on the screen" << endl;
    }

    void WhitePekinDuck::performFly() {
        fly();
    }

    void WhitePekinDuck::performQuack() {
        quack();
    }

    //-----------------------------------------------------------------------

    void RubberDuck::display() {
        cout << "Displaying a rubber duck on the screen" << endl;
    }

    void RubberDuck::quack() {
        cout << "squeak" << endl;
    }

    void RubberDuck::performQuack() {
        quack();
    }

    void RubberDuck::performFly() {} // does nothing

    //-----------------------------------------------------------------------

    void DecoyDuck::display() {
        cout << "Displaying a decoy duck on the screen" << endl;
    }

    void DecoyDuck::performFly() {} // does nothing

    void DecoyDuck::performQuack() {} // does nothing

}