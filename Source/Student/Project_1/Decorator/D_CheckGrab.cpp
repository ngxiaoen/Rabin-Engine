#include <pch.h>
#include "D_CheckGrab.h"

void D_CheckGrab::on_enter()
{
    BehaviorNode::on_enter();
}

void D_CheckGrab::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode *child = children.front();

    if(myGlobalBlackBoard->get_value<bool>("grabBoat"))
    {
        agent->set_color(Vec3{ 1.f,0.f,0.f });
        child->tick(dt);
        set_status(child->get_status());
        set_result(child->get_result());
    }
    else
    {
        on_failure();
    }

}
