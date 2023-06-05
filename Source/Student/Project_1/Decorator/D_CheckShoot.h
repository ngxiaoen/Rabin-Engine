#pragma once
#include "BehaviorNode.h"

class D_CheckShoot : public BaseNode<D_CheckShoot>
{
public:

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};