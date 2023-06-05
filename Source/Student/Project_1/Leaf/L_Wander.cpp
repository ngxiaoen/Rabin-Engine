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
    if (myGlobalBlackBoard->get_value<bool>("atCenter") || myGlobalBlackBoard->get_value<int>("humanCount") == 0 
        || myGlobalBlackBoard->get_value<bool>("takeControl"))
    {
        on_failure();
        return;
    }
    const auto result = agent->move_toward_point(targetPoint, dt);
    //set boat position
    myGlobalBlackBoard->set_value("boatPos", agent->get_position());
    auto temp = myGlobalBlackBoard->get_value<std::vector
        <std::pair<std::wstring, Vec3>>>("humanPositions");
    for (int i{ 0 }; i < myGlobalBlackBoard->get_value<int>("humanCount"); ++i)
    {
        //std::cout << i << std::endl;
        temp[i].second = agent->get_position() + static_cast<float>(i) * Vec3{ 5.f,0.f,0.f };
    }

    myGlobalBlackBoard->set_value("humanPositions", temp);
    if (result == true)
    {
        on_success();
        myGlobalBlackBoard->set_value("forceMove", false);

    }

    display_leaf_text();
}
