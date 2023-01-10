//
// Created by shimm on 12/8/2022.
//

#ifndef DUCKAPP_DUCK_HPP
#define DUCKAPP_DUCK_HPP


#include "Behaviors.hpp"

namespace DuckSim {


    class Duck {
    public:
        void performQuack();

        void swim();

        void performFly();

        virtual void display() = 0;

        void setFlyBehavior(FlyBehavior* flying);

        void setQuackBehavior(QuackBehavior* quacking);

        int getIdentifier();

    protected:
        FlyBehavior* flight;
        QuackBehavior* sound;
        Duck(FlyBehavior* flying, QuackBehavior* quacking);
    private:
        int identifier;
    };

}



#endif //DUCKAPP_DUCK_HPP