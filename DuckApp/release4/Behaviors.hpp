//
// Created by shimm on 12/8/2022.
//

#ifndef DUCKAPP_BEHAVIORS_HPP
#define DUCKAPP_BEHAVIORS_HPP

namespace DuckSim {
    class FlyBehavior {
    public:
        FlyBehavior();

        virtual void fly() = 0;
    };

    class QuackBehavior {
    public:
        QuackBehavior();

        virtual void quack() = 0;
    };

    class FlyWithWings : public FlyBehavior {
    public:
        explicit FlyWithWings(int speed = 1);

        void fly() override;

    private:
        int speed;
    };

    class FlyNoWay : public FlyBehavior {
    public:
        void fly() override;
    };

    class Quack : public QuackBehavior {
    public:
        Quack();

        void quack() override;
    };

    class Squeak : public QuackBehavior {
    public:
        void quack() override;
    };

    class MuteQuack : public QuackBehavior {
    public:
        void quack() override;
    };

    class QuackQuack : public QuackBehavior {
    public:
        void quack() override;
    };
}
#endif //DUCKAPP_BEHAVIORS_HPP
