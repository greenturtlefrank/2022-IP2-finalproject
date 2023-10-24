#ifndef InvisibleBombBullet_hpp
#define InvisibleBombBullet_hpp

#include "Bullet.hpp"

class Army;
class Defense;
namespace Engine {
    struct Point;
}  // namespace Engine

class InvisibleBombBullet : public Bullet {
public:
    explicit InvisibleBombBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent);
};

#endif /* InvisibleBombBullet_hpp */
#pragma once
#pragma once
