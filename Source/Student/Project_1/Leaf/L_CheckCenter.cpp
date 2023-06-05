#include <pch.h>
#include "L_CheckCenter.h"
#include "../Agent/BehaviorAgent.h"

void L_CheckCenter::on_update(float dt)
{
    auto checkCenter = [](Vec3 pos, Vec3 cpos, float radius)
    {
        return (pos-cpos).Length()
            <= powf(radius, 2.f);
    };

    std::wstring wstr = L"boatAgent";

    if(agent->get_debug_name() == wstr)
    {
        //check if agentpos is within radius
		//(x - center_x)² + (y - center_y)² < radius²

        if(checkCenter(agent->get_position(), centerPos, radius))
        {
            myGlobalBlackBoard->set_value("atCenter", true);
            on_success();
            return;
        }

        on_failure();
    }
    display_leaf_text();
}
