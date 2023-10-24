#ifndef HideEffect_HPP
#define HideEffect_HPP
#include <allegro5/bitmap.h>
#include <memory>
//#include <vector>

#include "Sprite.hpp"
#include "Army.hpp"

class PlayScene;

class HideEffect : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	Engine::Point here;
	float timeTicks;
	//std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 3.0;
	float x;
	float y;

public:

	Army* tgt = nullptr;

	HideEffect(float x, float y);
	void Update(float deltaTime) override;
	bool InShootingRange(Engine::Point obj);
};



#endif // HideEffect_HPP
#pragma once
#pragma once
