#ifndef MineBomb_HPP
#define MineBomb_HPP
#include <allegro5/bitmap.h>
#include <memory>
//#include <vector>

#include "Sprite.hpp"
#include "Defense.hpp"


class PlayScene;

class MineBomb : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	//std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 0.5;
	float x, y;

public:

	
	Defense* tgt = nullptr;

	MineBomb(float x, float y);
	void Update(float deltaTime) override;

	bool isbomb = false;
};



#endif // MineBomb_HPP
#pragma once
#pragma once
