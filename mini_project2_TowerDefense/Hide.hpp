#ifndef HideArmy_hpp
#define HideArmy_hpp

#include "Army.hpp"

class Hide : public Army {
public:
    double timeTicks;
    double timeSpan;
    Hide(int x, int y);

    void CreateBullet(Engine::Point pt) override;
    
};

#endif /* Hide_hpp */
#pragma once
#pragma once
#pragma once
