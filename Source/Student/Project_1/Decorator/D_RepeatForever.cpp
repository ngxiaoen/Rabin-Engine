#include <pch.h>
#include "D_RepeatForever.h"

void D_RepeatForever::on_enter()
{
    BehaviorNode::on_enter();
}

void D_RepeatForever::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        child->set_status(NodeStatus::READY);
    }
    if (child->failed() == true)
    {
        on_failure();
    }
}
