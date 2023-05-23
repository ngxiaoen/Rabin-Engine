#pragma once
#include "BehaviorNode.h"

class L_SpinVertically : public BaseNode<L_SpinVertically>
{
public:

protected:
    float currentDirection;
    float timer{0.f};

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};