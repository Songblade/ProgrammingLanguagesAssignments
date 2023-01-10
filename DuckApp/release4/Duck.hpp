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

/* If I needed to handle ducks that could quack in multiple ways, then first I would need to know
 * what exactly you meant by that. Do you mean that when performQuack() is called, multiple different
 * types of quacks are called, or that performQuack could be called with different parameters and
 * get multiple types of quacks?
 *
 * If you mean the first, then we wouldn't have to change the API at all, and we could make
 * setQuackBehavior add the new sound to an array instead of replacing it. But we would probably also want a method
 * that deletes a sound from the array. But there is no way to have a traditional set/replace here, because we would
 * need to specify which sound we are replacing. Or, we could put in the parameters and additional sound (or index)
 * for what is being replaced.
 *
 * If instead we mean the duck has different options, the question is, how does the user specify which option?
 * We could have the Duck class store a list (probably static) that contains each sound, and the user would have
 * to specify which one they want, whether by index or name, while the default would be whatever was set for that
 * duck. Or we could instead add sounds to a list for the duck, and then specify which one we want each time we
 * call the method.
 *
 * Either way, it is only possible to do this without altering the API if the duck says every sound at once,
 * because otherwise it would need to be specified which sound was being called.
 * */