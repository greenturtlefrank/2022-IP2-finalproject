#ifndef IceArmy_hpp
#define IceArmy_hpp

#include "Army.hpp"

class Ice : public Army {
public:
    double timeTicks;
    double timeSpan;
    Ice(int x, int y);

    void CreateBullet(Engine::Point pt) override;
    //void Freeze(double deltaTime);
    //void Update(float deltaTime);
};

#endif /* Ice_hpp */
#pragma once
#pragma once
