#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "iostream"
#include "Ice.hpp"
#include "AudioHelper.hpp"
#include "DirtyEffect.hpp"
#include "PlayScene.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"
//#include "GameEngine.hpp"
//#include "ArcherBullet.hpp"

//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
Ice::Ice(int x, int y) : Army("play/ice.png", x, y, 120, 60, 0, 100, 6, 90) , timeTicks(0) {
    // Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
    // and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}


void Ice::CreateBullet(Engine::Point pt) 
{
    
}

/*
void Ice::Freeze(double deltaTime) 
{
	
}

void Ice::Update(float deltaTime) {
	
}*/

