#include <pch.h>
#include "L_CollisionCheck.h"
#include "Agent/BehaviorAgent.h"

void L_CollisionCheck::on_enter()
{
    // set animation, speed, etc
    BehaviorNode::on_leaf_enter();
}

void L_CollisionCheck::on_update(float dt)
{
    //BehaviorNode* child = children.front();
    auto collisionCheck = [](Vec3 pos1, Vec3 pos2)
    {
        Vec3 temp = pos2 - pos1;
        float temp2 = sqrt((temp.x * temp.x) + (temp.y * temp.y) + (temp.z * temp.z));

        return (temp2 <= 20.f);
    };

    auto allAgents = agents->get_all_agents_by_type("boatAgent");
    for(auto a : allAgents)
    {
        //kraken->boat
        
        if ((agent->get_position() - a->get_position()).Length() <= 20.f)
        //if(collisionCheck(agent->get_position(), a->get_position()))
		{
			//check which direction
            //check if set previously
            if(!myGlobalBlackBoard->get_value<bool>("krakenCollDirty"))
            {
                myGlobalBlackBoard->set_value("collided", true);
                myGlobalBlackBoard->set_value("krakenCollDirty", true);
                myGlobalBlackBoard->set_value("takeControl", true);
                myGlobalBlackBoard->set_value("collidedDir", agent->get_blackboard().get_value<int>("direction"));
            	on_failure();
            }
            else
            on_success();

		    return;
		}
    }
    on_success();
    return;

    display_leaf_text();
}
