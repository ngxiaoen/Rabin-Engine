#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_FollowPath: public BaseNode<L_FollowPath>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

public:
    int dir;
    Vec3 ogScale;
    std::vector<Vec3> nodes;
};