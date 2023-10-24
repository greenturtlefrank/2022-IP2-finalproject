#include <cmath>
#include <string>

#include "iostream"
#include "Army.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Resources.hpp"
#include "MineBomb.hpp"




PlayScene* MineBomb::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
MineBomb::MineBomb(float xx, float yy) : Sprite("play/mine.png", xx, yy), timeTicks(0), x(xx), y(yy)
{
	
}
void MineBomb::Update(float deltaTime) {

	if (!isbomb)
	{
		for (auto& it : getPlayScene()->ArmyGroup->GetObjects()) {

			double xx = it->Position.x, yy = it->Position.y;
			Army* a = nullptr;

			//std::cout << "hi" << xx << " " << x << " " << yy << " " << y << "hi" << std::endl;

			if (xx == x && yy == y)
			{
				std::cout << "hit" << std::endl;

				Engine::Point p(x, y);

				for (auto& it : getPlayScene()->ArmyGroup->GetObjects()) 
				{
					a = dynamic_cast<Army*>(it);

					if (a->ManHattanDistance(p) < 5)
					{
						a->Hit(INFINITY);
					}
				}
				isbomb = 1;
			}
		}
	}
	else
	{
		std::cout << "die" << std::endl;

		timeTicks += deltaTime;
		if (timeTicks >= timeSpan)
		{
			getPlayScene()->DefenseGroup->RemoveObject(objectIterator);
			return;
		}
	}
	









	

	

	Sprite::Update(deltaTime);
}
