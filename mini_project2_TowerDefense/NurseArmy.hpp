#ifndef NurseArmy_hpp
#define NurseArmy_hpp

#include "Army.hpp"

class NurseArmy : public Army {
public:
    NurseArmy(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

#endif /* NurseArmy_hpp */
#pragma once




