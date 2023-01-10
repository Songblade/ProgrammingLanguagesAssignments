//
// Created by shimm on 12/8/2022.
//

#include "AllMyDucks.hpp"
#include <iostream>
using namespace std;
namespace DuckSim {

    MarbledDuck::MarbledDuck() : Duck(new FlyWithWings(), new Quack()) {}

    MarbledDuck::MarbledDuck(FlyBehavior* flying, QuackBehavior* quacking) : Duck(flying, quacking){}

    MarbledDuck::~MarbledDuck() {
        delete flight;
        delete sound;
    }

    void MarbledDuck::display() {
        cout << "Displaying a Marbled duck on the screen" << endl;
    }

//------------------------------------------------------------------------------

    WhitePekinDuck::WhitePekinDuck() : Duck(new FlyWithWings(), new QuackQuack()) {}

    WhitePekinDuck::WhitePekinDuck(FlyBehavior* flying, QuackBehavior* quacking) : Duck(flying, quacking){}

    WhitePekinDuck::~WhitePekinDuck() {
        delete sound;
        delete flight;
    }

    void WhitePekinDuck::display() {
        cout <<  "Displaying a White Pekin duck on the screen" << endl;
    }

    //-----------------------------------------------------------------------

    RubberDuck::RubberDuck() : Duck(new FlyNoWay(), new Squeak()) {}

    RubberDuck::RubberDuck(FlyBehavior* flying, QuackBehavior* quacking) : Duck(flying, quacking){}

    RubberDuck::~RubberDuck() {
        delete sound;
        delete flight;
    }

    void RubberDuck::display() {
        cout << "Displaying a rubber duck on the screen" << endl;
    }


    //-----------------------------------------------------------------------

    DecoyDuck::DecoyDuck() : Duck(new FlyNoWay(), new MuteQuack()) {}

    DecoyDuck::DecoyDuck(FlyBehavior* flying, QuackBehavior* quacking) : Duck(flying, quacking){}

    DecoyDuck::~DecoyDuck() {
        delete sound;
        delete flight;
    }

    void DecoyDuck::display() {
        cout << "Displaying a decoy duck on the screen" << endl;
    }


}