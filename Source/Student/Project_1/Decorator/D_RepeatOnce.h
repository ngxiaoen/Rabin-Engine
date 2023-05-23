#pragma once
#include "BehaviorNode.h"

class D_RepeatOnce : public BaseNode<D_RepeatOnce>
{
public:
    D_RepeatOnce();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};