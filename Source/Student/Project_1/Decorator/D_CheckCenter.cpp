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

    auto checkCenter = [](Vec2 pos, Vec2 cpos, float radius)
    {
        return (pos - cpos).Length()
            <= radius;
    };

    if(myGlobalBlackBoard->get_value<bool>("forceMove"))
    {
		//std::cout << "forced" << std::endl;
        child->tick(dt);
        set_status(child->get_status());
        set_result(child->get_result());
        return;
    }
    //work with selector
    if (checkCenter(Vec2{ agent->get_position().x, agent->get_position().z}, Vec2{ 50.f,50.f }, 20.f))
    {
        std::wstring temp = agent->get_debug_name();
        myGlobalBlackBoard->set_value("atCenter", true);
        myGlobalBlackBoard->set_value("krakenCollDirty", false);
        on_failure();
    }
    else
    {
		child->tick(dt);
        set_status(child->get_status());
        set_result(child->get_result());
    }
}
