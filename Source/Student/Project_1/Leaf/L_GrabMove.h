#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_GrabMove : public BaseNode<L_GrabMove>
{
protected:
	int index = 0;
	virtual void on_enter() override;
    virtual void on_update(float dt) override;

};