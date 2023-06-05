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

	//auto a = agent->move_toward_point(lerpFunc(agent->get_position(),
	//	agent->get_position() - Vec3{ 0.f,20.f,0.f }, timer/5.f), dt);

	const auto pos = agent->get_position();
	auto a = agent->move_toward_point(
		 { pos.x,-20.f,pos.z }, dt);

	if(a)
	{
		timer = 0.f;
		on_success();
	}

    display_leaf_text();
}
