#pragma once
#include "BehaviorNode.h"

class L_Circle : public BaseNode<L_Circle>
{
	private:
        float timer;
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};