//
// Created by shimm on 12/8/2022.
//

#ifndef DUCKAPP_ALLMYDUCKS_HPP
#define DUCKAPP_ALLMYDUCKS_HPP

#include "Duck.hpp"

namespace DuckSim {
    class MarbledDuck : public Duck {
    public:
        void display() override;
    };

    class WhitePekinDuck : public Duck {
    public:
        void quack() override;

        void display() override;
    };
}


#endif //DUCKAPP_ALLMYDUCKS_HPP
