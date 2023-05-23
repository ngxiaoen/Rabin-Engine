#include <pch.h>
#include "L_SpinVertically.h"
#include "Agent/BehaviorAgent.h"



void L_SpinVertically::on_enter()
{
	currentDirection = agent->get_pitch();

	BehaviorNode::on_leaf_enter();
}

void L_SpinVertically::on_update(float dt)
{
	timer += dt;
	auto lerpFunc = [](float start, float end, float percentage)
	{
		return start + (end - start) * percentage;
	};

	agent->set_pitch(lerpFunc(currentDirection, 
		currentDirection + 2 * PI, timer/4.f));

	if(timer >= 4.f)
	{
		timer = 0.f;
		on_success();
	}
	display_leaf_text();
}
