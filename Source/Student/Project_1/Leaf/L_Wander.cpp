#include <pch.h>
#include "L_Wander.h"
#include "Agent/BehaviorAgent.h"

void L_Wander::on_enter()
{
    // set animation, speed, etc

    targetPoint = Vec3{ RNG::range(0.f, 
        static_cast<float>(terrain->get_map_width()*5)), 0.0f,
        RNG::range(0.f,static_cast<float>(terrain->get_map_height() * 5)) };
    
	BehaviorNode::on_leaf_enter();
}

void L_Wander::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);
    //set boat position
    myGlobalBlackBoard->set_value("boatPos", agent->get_position());
    auto temp = myGlobalBlackBoard->get_value<std::vector
        <std::pair<std::wstring, Vec3>>>("humanPositions");
    temp[0].second = agent->get_position();
    temp[1].second = agent->get_position() + Vec3{ 10.f,0.f,10.f };

    myGlobalBlackBoard->set_value("humanPositions", temp);
    if (result == true)
    {
        on_success();
    }
    if(myGlobalBlackBoard->get_value<bool>("atCenter"))
    {
        on_failure();
    }

    display_leaf_text();
}
