#ifndef InvisibleBombDefense_hpp
#define InvisibleBombDefense_hpp

#include "Defense.hpp"


class InvisibleBombDefense : public Defense {
public:
    //float timeTicks;
    //float timeSpan = 0.5;
    float x, y;
    bool isbomb = false;

    InvisibleBombDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
    void Update(float deltaTime) override;
};

#endif /* InvisibleBombDefense_hpp */
#pragma once
#pragma once
