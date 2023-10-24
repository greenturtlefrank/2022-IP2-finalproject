#ifndef FROZENEFFECT_HPP
#define FROZENEFFECT_HPP
#include <allegro5/bitmap.h>
#include <memory>
//#include <vector>

#include "Sprite.hpp"
#include "Defense.hpp"

class PlayScene;

class FrozenEffect : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	//std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 2.0;

	
public:

	Defense* tgt = nullptr;

	FrozenEffect(float x, float y);
	void Update(float deltaTime) override;
};



#endif // FROZENEFFECT_HPP
#pragma once
