#include <pch.h>
#include "L_GrabMove.h"


void L_GrabMove::on_enter()
{
    index = 0;
    BehaviorNode::on_enter();
}

void L_GrabMove::on_update(float dt)
{
    std::vector<Vec3> temp = myGlobalBlackBoard->get_value<std::vector<Vec3>>("collidedNodePositions");

    if (myGlobalBlackBoard->get_value<bool>("atCenter") || myGlobalBlackBoard->get_value<int>("humanCount") == 0)
    {
        on_failure();
        return;
    }



	const auto result = agent->move_toward_point(temp[index], dt);
    //set boat position
    myGlobalBlackBoard->set_value("boatPos", agent->get_position());
    //set human position
    auto humPos = myGlobalBlackBoard->get_value<std::vector
        <std::pair<std::wstring, Vec3>>>("humanPositions");

    for (int i{ 0 }; i < myGlobalBlackBoard->get_value<int>("humanCount"); ++i)
    {
        humPos[i].second = agent->get_position() + static_cast<float>(i) * Vec3 { 5.f, 0.f, 0.f };
    }
    myGlobalBlackBoard->set_value("humanPositions", humPos);

    if (result)
    {
        ++index;
    }

    if(index >= temp.size())
    {
        auto pos = agent->get_position();
        myGlobalBlackBoard->set_value("forceMove", true);
        myGlobalBlackBoard->set_value("takeControl", false);
        myGlobalBlackBoard->set_value("grabMove", false);
        myGlobalBlackBoard->set_value("shootHuman?", true);
        myGlobalBlackBoard->set_value("collidedDir", 0);
        agent->set_color(Vec3{ 0.5f,0.5f,0.5f });
        agent->set_position(Vec3{ 0.f,0.f,0.f });
        index = 0;
        on_failure();
    }


    display_leaf_text();
    
}
