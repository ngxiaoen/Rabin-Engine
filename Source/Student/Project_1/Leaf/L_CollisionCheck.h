#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_CollisionCheck : public BaseNode<L_CollisionCheck>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:

};