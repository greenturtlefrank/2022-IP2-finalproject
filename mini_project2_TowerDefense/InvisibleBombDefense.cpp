#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "iostream"
#include "InvisibleBombDefense.hpp"
#include "AudioHelper.hpp"
#include "InvisibleBombBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"
#include "Collider.hpp"


//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
InvisibleBombDefense::InvisibleBombDefense(float xx, float yy) :
    Defense("play/mine.png", xx, yy, 20, 0, 1, 4, 60), x(xx), y(yy) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void InvisibleBombDefense::CreateBullet(Engine::Point pt) {

}




void InvisibleBombDefense::Update(float deltaTime) {

	if (!isbomb)
	{
		for (auto& it : getPlayScene()->ArmyGroup->GetObjects()) {

			double xx = it->Position.x, yy = it->Position.y;
			//Army* a = nullptr;

			//std::cout << "hi" << xx << " " << x << " " << yy << " " << y << "hi" << std::endl;

			


			Army* army = dynamic_cast<Army*>(it);
			if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, army->Position, army->CollisionRadius) && army->id != 2 && army->id != 3) {


				std::cout << "hit" << std::endl;

				//Engine::Point p(x, y);

				for (auto& it : getPlayScene()->ArmyGroup->GetObjects())
				{
					Army* armyarmy = dynamic_cast<Army*>(it);

					armyarmy = dynamic_cast<Army*>(it);

					if (InShootingRange(armyarmy->Position))
					{
						armyarmy->Hit(INFINITY);
					}
				}
				isbomb = true;

				//army->Hit(INFINITY);
				getPlayScene()->DefenseGroup->RemoveObject(objectIterator);
				return;
			}

		}
	}
	














	Sprite::Update(deltaTime);
}