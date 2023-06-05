#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Wave: public BaseNode<L_Wave>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float timer{ 0.f };
};