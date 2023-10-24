#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Army.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "NurseArmy.hpp"
#include "NurseBullet.hpp"
#include "Defense.hpp"


//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
NurseArmy::NurseArmy(float x, float y) :
    Army("play/plane-1.png", x, y, 20, 3, 10, 80, 3, 40) {
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void NurseArmy::Update(float deltaTime) {
    // PlayScene
    PlayScene* scene = getPlayScene();

    if (isPreview) return;

    reloadplus += deltaTime;

    if (reloadplus >= 0.5)
    {
        float plus = 10;

        if (HP + plus > MAXHP)
        {
            HP = MAXHP;
        }
        else
        {
            HP += plus;
        }

        reloadplus = 0;
    }






    // position
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));

    if (!Target) {
        
        int maxDis = INT_MAX;
        Defense *tgt = nullptr, *bef = nullptr;

        

        if (tgt == nullptr)
        {
            for (auto& it : scene->DefenseGroup->GetObjects()) {
                int dis = ManHattanDistance(it->Position);

                bef = dynamic_cast<Defense*>(it);
                if (bef->id == 4) {
                    bef = nullptr;
                    continue;
                }

                if (dis < maxDis) {
                    maxDis = dis;
                    tgt = dynamic_cast<Defense*>(it);
                }
            }
        }

        // TODO 2 (7/8): Store the closet target in Target, and update lockedArmyIterator. You can imitate the same part in Defense::Update().
        // Also, record the target is wall or a noraml defense.


        if (tgt) {
            Target = tgt;
            Target->lockedArmies.push_back(this);
            lockedArmyIterator = std::prev(Target->lockedArmies.end());
        }


    }
    if (Target) {
        Rotation = UpdateRotation(deltaTime, Target->Position);
        // Bomb cannot shoot, so the reload time just set as coolDown.
        reload += deltaTime;
        

        

            // TODO 2 (8/8): If bomb army is on the same block with target. Explode itself to deal damage to the target. Otherwise, move toward the target.
            if (InShootingRange(Target->Position) && reload >= coolDown) {
                // Notice that bomb army deals different damage to wall and normal target.

                CreateBullet(Target->Position);

                reload = 0;
            }


            if (InShootingRange(Target->Position)) {
                Velocity = Engine::Point(0, 0);
            }
            else {
                int dx = Target->Position.x - Position.x;
                int dy = Target->Position.y - Position.y;
                double len = sqrt(pow(dx, 2) + pow(dy, 2));
                Velocity = speed * Engine::Point(dx / len, dy / len);
            }
        

    }

    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
}

// Since the bomb army cannot shoot, the function doesn't need to do anything.
void NurseArmy::CreateBullet(Engine::Point pt) {
    int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new NurseBullet(Position, diff, rotation, this));
    AudioHelper::PlayAudio("missile.wav");
}

// TODO 2 (5/8): You can imitate the hit function in Army class. Notice that the bomb army won't have explosion effect.
void NurseArmy::Hit(float damage) {
    HP -= damage;
    if (HP <= 0) {
        // OnExplode();
        // Remove all Defense's reference to target.
        for (auto& it : lockedDefenses)
            it->Target = nullptr;
        getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}




/*



void ArcherArmy::CreateBullet(Engine::Point pt) {
    int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new ArcherBullet(Position, diff, rotation, this));
    AudioHelper::PlayAudio("missile.wav");
}
*/