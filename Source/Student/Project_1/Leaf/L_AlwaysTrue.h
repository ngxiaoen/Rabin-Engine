#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_AlwaysTrue : public BaseNode<L_AlwaysTrue>
{
protected:
    virtual void on_update(float dt) override;

};