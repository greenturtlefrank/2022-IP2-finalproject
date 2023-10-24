#include <cmath>
#include <string>

#include "iostream"
#include "HideEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Resources.hpp"




PlayScene* HideEffect::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
HideEffect::HideEffect(float x, float y) : Sprite("play/private.png", x, y), timeTicks(0), x(x), y(y), here(x,y)
{
	std::cout << "Hide" << std::endl;
}
void HideEffect::Update(float deltaTime) {
	timeTicks += deltaTime;


	for (auto& it : getPlayScene()->ArmyGroup->GetObjects()) {

		double xx = it->Position.x, yy = it->Position.y;

		tgt = nullptr;
		tgt = dynamic_cast<Army*>(it);

		//std::cout << "hi" << xx << " " << x << " " << yy << " " << y << "hi" << std::endl;

		

		if (InShootingRange(it->Position))
		{
			//std::cout << "in" << std::endl;

			tgt -> Hide = true;

			//std::cout << "Hide" << std::endl;

		}
		
	}






	if (timeTicks >= timeSpan)
	{
		for (auto& it : getPlayScene()->ArmyGroup->GetObjects()) {

			double xx = it->Position.x, yy = it->Position.y;

			tgt = dynamic_cast<Army*>(it);

			tgt->Hide = false;
		}

		getPlayScene()->GroundEffectGroup->RemoveObject(objectIterator);

		return;
	}

	Sprite::Update(deltaTime);
}


bool HideEffect::InShootingRange(Engine::Point obj) {
	return (pow(abs(Position.x - obj.x), 2) + pow(abs(Position.y - obj.y), 2) <= pow(90, 2));
}