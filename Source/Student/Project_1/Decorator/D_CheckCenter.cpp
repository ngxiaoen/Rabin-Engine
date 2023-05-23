#include <pch.h>
#include "D_CheckCenter.h"

void D_CheckCenter::on_enter()
{
    BehaviorNode::on_enter();
}

void D_CheckCenter::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode *child = children.front();

    auto checkCenter = [](Vec3 pos, Vec3 cpos, float radius)
    {
        return (pos - cpos).Length()
            <= powf(radius, 2.f);
    };

    //work with selector
    if (checkCenter(agent->get_position(), Vec3{50.f, 0.f, 50.f}, 10.f))
    {
        myGlobalBlackBoard->set_value("atCenter", true);
        on_failure();
    }
    else
    {
		child->tick(dt);
        set_status(child->get_status());
        set_result(child->get_result());
    }
}
