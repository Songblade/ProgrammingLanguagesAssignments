//
// Created by shimm on 12/8/2022.
//

#ifndef DUCKAPP_ALLMYDUCKS_HPP
#define DUCKAPP_ALLMYDUCKS_HPP


#include "Duck.hpp"
#include "Behaviors.hpp"

namespace DuckSim {
    class MarbledDuck : public Duck, protected QuackBehavior, protected FlyBehavior {
    public:
        void display() override;
        void performQuack() override;
        void performFly() override;
    };

    class WhitePekinDuck : public Duck, protected QuackBehavior, protected FlyBehavior {
    public:
        void display() override;
        void performQuack() override;
        void performFly() override;
    private:
        void quack() override;
    };

    class RubberDuck : public Duck, protected QuackBehavior {
    public:
        void display() override;
        void performQuack() override;
        void performFly() override;
    private:
        void quack() override;
    };

    class DecoyDuck : public Duck {
    public:
        void display() override;
        void performQuack() override;
        void performFly() override;
    };
}



#endif //DUCKAPP_ALLMYDUCKS_HPP
