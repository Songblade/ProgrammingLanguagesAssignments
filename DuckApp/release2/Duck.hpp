//
// Created by shimm on 12/8/2022.
//

#ifndef DUCKAPP_DUCK_HPP
#define DUCKAPP_DUCK_HPP


namespace DuckSim {


    class Duck {
    public:
        virtual void performQuack() = 0;

        void swim();

        virtual void performFly() = 0;

        virtual void display() = 0;
    };
}



#endif //DUCKAPP_DUCK_HPP
