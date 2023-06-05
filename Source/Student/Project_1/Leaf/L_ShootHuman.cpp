#include <pch.h>
#include "L_ShootHuman.h"
#include "Agent/BehaviorAgent.h"

void L_ShootHuman::on_enter()
{
    // set animation, speed, etc
    //std::cout << "shoot me" << std::endl;
	ogSpeed = agent->get_movement_speed();
	BehaviorNode::on_leaf_enter();
}

void L_ShootHuman::on_update(float dt)
{

    //std::vector<std::pair<std::wstring, Vec3>> humanPositions;
    //humanPositions.emplace_back(std::pair<std::wstring, Vec3>(human1->get_debug_name(),
    //    Vec3{ 0.f, 0.f,0.f }));
    //humanPositions.emplace_back(std::pair<std::wstring, Vec3>(human2->get_debug_name(),
    //    Vec3{ 0.f,0.f,0.f }));
    std::vector<std::pair<std::wstring, Vec3>> temp = myGlobalBlackBoard->get_value<std::vector
        <std::pair<std::wstring, Vec3>>>("humanPositions");

    //if 2 humans
    myGlobalBlackBoard->set_value("shootHuman?", false);
    //std::cout << "shoot human" << std::endl;
    //std::wcout << agent->get_debug_name() << std::endl;
    if(myGlobalBlackBoard->get_value<int>("humanCount") == 2)
    {
        //if agent debug name is same as stored string
        if(agent->get_debug_name() == temp[1].first.c_str())
        {
            //std::cout << "shoot human1" << std::endl;

            //shoot player up
            Vec3 newPos = { temp[1].second.x,30.0f,temp[1].second.z };
            agent->set_movement_speed(ogSpeed * 4);
            const auto result = agent->move_toward_point(newPos, dt);
            if (result)
            {
                if(myGlobalBlackBoard->get_value<int>("humanCount") == 2)
                temp.erase(std::next(temp.begin()));
				myGlobalBlackBoard->set_value("humanCount", 1);

                myGlobalBlackBoard->set_value("humanPositions", temp);
                agents->destroy_agent(agent);
                //erase from stored vec of positions
                on_failure();
                return;
            }
            return;
        }

    }
    else
    {

        //if 1 human
        if (agent->get_debug_name() == temp[0].first.c_str())
        {
            //std::cout << "shoot human2" << std::endl;

            Vec3 newPos = { temp[0].second.x,30.0f,temp[0].second.z };
            agent->set_movement_speed(ogSpeed * 4);
            const auto result = agent->move_toward_point(newPos, dt);
            myGlobalBlackBoard->set_value("humanCount", 0);
            //myGlobalBlackBoard->set_value("shootHuman?", false);
            if (result)
            {
                temp.clear();
				myGlobalBlackBoard->set_value("humanPositions", temp);
                agent->set_movement_speed(ogSpeed);
                agents->destroy_agent(agent);
                on_failure();
                return;
            }
            return;
        }

        /*if(myGlobalBlackBoard->get_value<bool>("ignore"))
        myGlobalBlackBoard->set_value("ignore", false);*/
    }
    on_failure();

    display_leaf_text();
}
