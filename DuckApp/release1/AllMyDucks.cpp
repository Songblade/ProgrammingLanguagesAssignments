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


void WhitePekinDuck::quack() {
    cout << "quack, quack!" << endl;
}

void WhitePekinDuck::display() {
    cout <<  "Displaying a White Pekin duck on the screen" << endl;
}

}