//
// Created by shimm on 12/8/2022.
//

#ifndef DUCKAPP_ALLMYDUCKS_HPP
#define DUCKAPP_ALLMYDUCKS_HPP


#include "Duck.hpp"
#include "Behaviors.hpp"

namespace DuckSim {
    class MarbledDuck : public Duck {
    public:
        MarbledDuck();
        MarbledDuck(FlyBehavior* flying, QuackBehavior* quacking);
        ~MarbledDuck();
        void display() override;
    };

    class WhitePekinDuck : public Duck {
    public:
        WhitePekinDuck();
        WhitePekinDuck(FlyBehavior* flying, QuackBehavior* quacking);
        ~WhitePekinDuck();
        void display() override;
    };

    class RubberDuck : public Duck {
    public:
        RubberDuck();
        RubberDuck(FlyBehavior* flying, QuackBehavior* quacking);
        ~RubberDuck();
        void display() override;
    };

    class DecoyDuck : public Duck {
    public:
        DecoyDuck();
        DecoyDuck(FlyBehavior* flying, QuackBehavior* quacking);
        ~DecoyDuck();
        void display() override;
    };
}



#endif //DUCKAPP_ALLMYDUCKS_HPP
