#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "iostream"
#include "Hide.hpp"
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
Hide::Hide(int x, int y) : Army("play/private.png", x, y, 120, 60, 0, 100, 7, 90), timeTicks(0) {
    // Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
    // and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}


void Hide::CreateBullet(Engine::Point pt)
{
    //std::cout << "hit" << std::endl;

    //Hit(INFINITY);
}



