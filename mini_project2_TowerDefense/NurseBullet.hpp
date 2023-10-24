#ifndef NurseBullet_hpp
#define NurseBullet_hpp

#include "ArmyBullet.hpp"

class Army;
class Defense;
namespace Engine {
    struct Point;
}  // namespace Engine

class NurseBullet : public ArmyBullet {
public:
    explicit NurseBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent);
    void OnExplode(Defense* defense) override;
};


#endif /* NurseBullet_hpp */
#pragma once
