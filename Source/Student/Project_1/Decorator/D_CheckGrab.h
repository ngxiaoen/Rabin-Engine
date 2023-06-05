#pragma once
#include "BehaviorNode.h"

class D_CheckGrab : public BaseNode<D_CheckGrab>
{
public:

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};