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
    protected:
        FlyBehavior* flight;
        QuackBehavior* sound;
        Duck(FlyBehavior* flying, QuackBehavior* quacking);
        Duck()=default;
    };
}



#endif //DUCKAPP_DUCK_HPP

/* If I needed to handle ducks that could quack in multiple ways, which you said on Piazza was that when
 * performQuack() is called, multiple different types of quacks are called, then we wouldn't have to change the API
 * at all. We could make setQuackBehavior add the new sound to an array instead of replacing it. We would then have
 * performQuack() traverse the array and call each QuackBehavior on the array. But we would probably also want a
 * method that deletes a sound from the array, which would be changing the API, because otherwise, ducks could only
 * gain sounds, never lose them. But there is no way to have a traditional set/replace here like we have now, where
 * adding one sound gets rid of the old sound, because we would need to specify which sound we are replacing.
 * Or, we could add to the parameters the additional sound (or index) that is being replaced.
 * */