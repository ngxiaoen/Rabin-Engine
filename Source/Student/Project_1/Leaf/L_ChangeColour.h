#pragma once
#include "BehaviorNode.h"

class L_ChangeColour : public BaseNode<L_ChangeColour>
{
private:

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};