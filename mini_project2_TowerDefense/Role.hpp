#ifndef ROLE_HPP
#define ROLE_HPP
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Role : public Engine::Sprite {
protected:
	
	PlayScene* getPlayScene();
	virtual void OnExplode();
public:
	float HP;
	float MAXHP;
	Role(std::string img, float x, float y);
 	virtual void Hit(float damage);

};
#endif // ROLE_HPP
