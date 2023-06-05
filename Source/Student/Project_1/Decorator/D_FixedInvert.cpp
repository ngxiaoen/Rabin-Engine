#include <pch.h>
#include "D_FixedInvert.h"

void D_FixedInvert::on_enter()
{
    BehaviorNode::on_enter();
}

void D_FixedInvert::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode *child = children.front();
    bool invert = !myGlobalBlackBoard->get_value<bool>("collided");
	if(invert)
    {
		child->tick(dt);
        set_status(child->get_status());
        set_result(child->get_result());
        on_success();
    }
    else
    {
        on_failure();
    }
}
