#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Wander: public BaseNode<L_Wander>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
};