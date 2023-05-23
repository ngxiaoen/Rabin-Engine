#pragma once
#include "BehaviorNode.h"

class L_SpinHorizontally : public BaseNode<L_SpinHorizontally>
{
public:

protected:
    float currentDirection;
    float timer{0.f};

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};