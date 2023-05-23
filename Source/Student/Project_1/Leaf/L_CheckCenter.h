#pragma once
#include "BehaviorNode.h"

class L_CheckCenter : public BaseNode<L_CheckCenter>
{
public:
    float radius{10.f};
    Vec3 centerPos{50.f,0.f,50.f};
protected:

    virtual void on_update(float dt) override;
};