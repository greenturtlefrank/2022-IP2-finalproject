#include <cmath>
#include <string>

#include "iostream"
#include "FrozenEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Resources.hpp"




PlayScene* FrozenEffect::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
FrozenEffect::FrozenEffect(float x, float y) : Sprite("play/iceed.png", x, y), timeTicks(0)
{
	for (auto& it : getPlayScene()->DefenseGroup->GetObjects()) {

		double xx = it->Position.x, yy = it->Position.y;

		tgt = nullptr;

		//std::cout << "hi" << xx << " " << x << " " << yy << " " << y << "hi" << std::endl;

		if (xx  == x  && yy  == y )
		{
			tgt = dynamic_cast<Defense*>(it);
			tgt -> Freeze = true;

			std::cout << "FREEZE" << std::endl;

			break;
		}
	}
	
}
void FrozenEffect::Update(float deltaTime) {
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) 
	{
		if (tgt != nullptr)
		{
			tgt -> Freeze = false;
		}
		

		getPlayScene()->GroundEffectGroup->RemoveObject(objectIterator);

		return;
	}

	if (tgt != nullptr)
	{
		tgt->Freeze = true;
	}
	
	Sprite::Update(deltaTime);
}
