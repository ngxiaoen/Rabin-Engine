#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Respawn: public BaseNode<L_Respawn>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:

};