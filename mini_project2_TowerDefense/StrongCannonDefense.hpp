#ifndef StrongCannonDefense_hpp
#define StrongCannonDefense_hpp

#include "Defense.hpp"

class StrongCannonDefense : public Defense {
public:
    StrongCannonDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* StrongCannonDefense_hpp */
#pragma once
