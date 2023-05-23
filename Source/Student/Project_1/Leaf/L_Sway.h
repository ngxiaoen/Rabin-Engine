#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Sway: public BaseNode<L_Sway>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float timer{ 0.f };
    float currRoll{0.f};
};