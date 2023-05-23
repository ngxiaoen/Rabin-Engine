#include <pch.h>
#include "L_Sink.h"
#include "Agent/BehaviorAgent.h"

void L_Sink::on_enter()
{
    // set animation, speed, etc

	BehaviorNode::on_leaf_enter();
}

void L_Sink::on_update(float dt)
{
	timer += dt;
	auto lerpFunc = [](Vec3 start, Vec3 end, float percentage)
	{
		return start + (end - start) * percentage;
	};

	agent->move_toward_point(lerpFunc(agent->get_position(),
		agent->get_position() - Vec3{ 0.f,20.f,0.f }, timer/2.f), dt);

	if(timer >= 2.f)
	{
		timer = 0.f;
		on_success();
	}

    display_leaf_text();
}
