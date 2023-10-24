#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "StrongCannonBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

class Defense;

//Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* defenseParent);
StrongCannonBullet::StrongCannonBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent) :
    Bullet("play/bullet-1.png", 1500, 3, position, forwardDirection, rotation, parent) {
}
