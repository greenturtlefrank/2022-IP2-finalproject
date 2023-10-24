#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "NurseBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Defense.hpp"
#include "ExplosionEffect.hpp"

class Defense;

//ArmyBullet::ArmyBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent)
NurseBullet::NurseBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent) :
    ArmyBullet("play/rocket.png", 30, 40, position, forwardDirection, rotation + ALLEGRO_PI / 2, parent) {
}

void NurseBullet::OnExplode(Defense* defense) {
    // TODO 3 (1/2): Add a ShootEffect here. Remember you need to include the class.

    getPlayScene()->EffectGroup->AddNewObject(new ShootEffect(Position.x, Position.y));

}
