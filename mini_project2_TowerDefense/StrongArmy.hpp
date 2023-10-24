#ifndef StrongArmy_hpp
#define StrongArmy_hpp

#include "Army.hpp"

class StrongArmy : public Army {
public:
    StrongArmy(int x, int y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* StrongArmy_hpp */
#pragma once
