#pragma once
#include "BehaviorNode.h"

class D_RepeatForever : public BaseNode<D_RepeatForever>
{
public:


protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};