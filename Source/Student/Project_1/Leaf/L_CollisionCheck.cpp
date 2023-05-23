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
    auto collisionCheck = [](Vec3 pos1, Vec3 pos2)
    {
        Vec3 temp = pos2 - pos1;
        float temp2 = sqrt((temp.x * temp.x) + (temp.y * temp.y) + (temp.z * temp.z));

        return temp2 <= FLT_EPSILON;
    };

    auto allAgents = agents->get_all_agents_by_type("tentacleAgent");
    for(auto a : allAgents)
    {
		if(collisionCheck(agent->get_position(), a->get_position()))
            on_success();
        return;
    }
    on_failure();
    return;

    display_leaf_text();
}
