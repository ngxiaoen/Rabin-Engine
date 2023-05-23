#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_GrabBoat : public BaseNode<L_GrabBoat>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 BoatPos;
    float timer;
    Vec3 offset{ 30.f, 0.f, 30.f };
};