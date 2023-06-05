#pragma once
#include "BehaviorNode.h"

class D_FixedInvert : public BaseNode<D_FixedInvert>
{
public:

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};