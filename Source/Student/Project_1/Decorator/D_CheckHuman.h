#pragma once
#include "BehaviorNode.h"

class D_CheckHuman : public BaseNode<D_CheckHuman>
{
public:
    D_CheckHuman();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};