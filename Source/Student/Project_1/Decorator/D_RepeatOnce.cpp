#include <pch.h>
#include "D_RepeatOnce.h"

void D_RepeatOnce::on_enter()
{
    BehaviorNode::on_enter();
}

void D_RepeatOnce::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        on_success();
    }
    else if (child->failed() == true)
    {
        on_failure();
    }
}
