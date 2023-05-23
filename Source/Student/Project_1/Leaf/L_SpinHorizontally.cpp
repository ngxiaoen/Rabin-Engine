#include <pch.h>
#include "L_SpinHorizontally.h"
#include "Agent/BehaviorAgent.h"



void L_SpinHorizontally::on_enter()
{
	currentDirection = agent->get_yaw();

	BehaviorNode::on_leaf_enter();
}

void L_SpinHorizontally::on_update(float dt)
{
	timer += dt;
	auto lerpFunc = [](float start, float end, float percentage)
	{
		return start + (end - start) * percentage;
	};

	agent->set_yaw(lerpFunc(currentDirection, 
		currentDirection + 2 * PI, timer/4.f));

	if(timer >= 4.f)
	{
		timer = 0.f;
		on_success();
	}
	display_leaf_text();
}
