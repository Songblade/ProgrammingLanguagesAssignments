//
// Created by shimm on 12/8/2022.
//

#ifndef DUCKAPP_BEHAVIORS_HPP
#define DUCKAPP_BEHAVIORS_HPP

namespace DuckSim {
    class FlyBehavior {
    protected:
        virtual void fly();
    };

    class QuackBehavior {
    protected:
        virtual void quack();

    };

}
#endif //DUCKAPP_BEHAVIORS_HPP

/* Assignment write-up:
 * By the way, Professor Leff has us answer these types of questions in a separate PDF, which would probably
 * make it easier for you to find and grade them (so all 3 release write-ups would be in one place).
 *
 * One of the reasons I had to write a lot of duplicate code is that I decided to have each duck subclass
 * inherit the behavior classes individually, so they would only need to inherit the ones they need. I could
 * have instead made the Duck class itself inherit the behaviors directly, in which case the descendants would
 * override them as needed, but I didn't do that because it would be too similar to the release1 implementation.
 * Instead, I had each subclass inherit the behaviors individually, and only if they needed it. Had I had Duck
 * implement the subclasses, it could have defined performQuack and performFly for all the subclasses, and the
 * subclasses could have overridden quack and fly as appropriate to change things.
 *
 * Another reason for this is that our inheritance tree doesn't have enough layers. If we had a LivingDuck
 * class that defined fly and provided a default quack, there would be much less overriding in its children if
 * we had enough living ducks.
 *
 * If the ducks implemented Java interfaces, I don't think the issue would have changed. Modern java interfaces
 * can define default methods, so that wouldn't have changed. But in general, I think our problem is that we are
 * defining a fly method in Duck when we have subclasses of Duck that can't fly, which is also a problem in
 * releases 3 and 4. That violates 2 of the 5 SOLID principles: Liskov Substitution, because DecoyDuck isn't
 * substitutable for Duck because it can't quack and fly; and Interface Segregation, because clients are forced
 * to implement performFly and performQuack even if their duck doesn't actually fly or swim.
 *
 * */
