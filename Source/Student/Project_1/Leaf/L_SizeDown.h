#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_SizeDown: public BaseNode<L_SizeDown>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float timer{0.f};
    Vec3 ogScale;
};