#pragma once
#include "BehaviorNode.h"

class D_CheckCenter : public BaseNode<D_CheckCenter>
{
public:
    D_CheckCenter();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};