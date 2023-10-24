#ifndef StrongCannonBullet_hpp
#define StrongCannonBullet_hpp

#include "Bullet.hpp"

class Army;
class Defense;
namespace Engine {
    struct Point;
}  // namespace Engine

class StrongCannonBullet : public Bullet {
public:
    explicit StrongCannonBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent);
};

#endif /* StrongCannonBullet_hpp */
#pragma once
