#include <pch.h>
#include "L_FollowBoat.h"
#include "Agent/BehaviorAgent.h"

void L_FollowBoat::on_enter()
{
	BehaviorNode::on_leaf_enter();
}

void L_FollowBoat::on_update(float dt)
{
	//std::cout << "papa" << std::endl;
	if(myGlobalBlackBoard->get_value<int>("humanCount") > 0 && !myGlobalBlackBoard->get_value<bool>("shootHuman?"))
	{
		std::vector<std::pair<std::wstring, Vec3>> temp = myGlobalBlackBoard->get_value<std::vector
			<std::pair<std::wstring, Vec3>>>("humanPositions");

		//set human position
		for (int i{ 0 }; i < static_cast<int>(temp.size()); ++i)
		{
			if (agent->get_debug_name() == temp[i].first)
			{
				agent->set_position(temp[i].second);
				break;
			}
		}

		display_leaf_text();
	}
	//on_failure();
}
