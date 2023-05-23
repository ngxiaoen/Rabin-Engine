#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_FollowBoat: public BaseNode<L_FollowBoat>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:

};