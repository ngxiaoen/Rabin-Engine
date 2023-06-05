#include <pch.h>
#include "L_Sway.h"
#include "Agent/BehaviorAgent.h"

void L_Sway::on_enter()
{
    // set animation, speed, etc
    currRoll = agent->get_roll();

	BehaviorNode::on_leaf_enter();
}

void L_Sway::on_update(float dt)
{
	if (myGlobalBlackBoard->get_value<bool>("atCenter"))
	{
		on_failure();
		return;
	}

	timer += dt;
	auto lerpFunc = [](float start, float end, float percentage)
	{
		return start + (end - start) * percentage;
	};

	agent->set_roll(lerpFunc(currRoll,
		currRoll + PI * 0.01f, timer / 2.f));

	if(timer >= 2.f)
	{
		agent->set_roll(lerpFunc(currRoll + PI * 0.01f,
			currRoll, timer / 4.f));
	}
	if(timer >= 4.f)
	{
		timer = 0.f;
		on_success();
	}


    display_leaf_text();
}
