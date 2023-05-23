#include <pch.h>
#include "L_CheckCenter.h"

void L_CheckCenter::on_update(float dt)
{
    auto checkCenter = [](Vec3 pos, Vec3 cpos, float radius)
    {
        return (pos-cpos).Length()
            <= powf(radius, 2.f);
    };

    if(agent->get_type() == "boat")
    {
        //check if agentpos is within radius
		//(x - center_x)� + (y - center_y)� < radius�

        if(checkCenter(agent->get_position(), centerPos, radius))
        {
            myGlobalBlackBoard->set_value("atCenter", true);
            on_success();
            return;
        }

        on_failure();
    }
}
