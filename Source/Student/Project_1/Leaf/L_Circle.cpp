#include <pch.h>
#include "L_Circle.h"
#include "Agent/BehaviorAgent.h"

void L_Circle::on_enter()
{
	BehaviorNode::on_leaf_enter();
}

void L_Circle::on_update(float dt)
{
	auto lerpFunc = [](float start, float end, float percentage)
	{
		return start + (end - start) * percentage;
	};
	timer += dt;

	float temp = lerpFunc(0.f, 2 * PI, timer / 10.f);
	Vec3 newDir = { cos(temp), 0.0f, sin(temp) };
	Vec3 newPos = Vec3{ 50.f, 0.f, 50.f } + newDir * 30.f;

	agent->move_toward_point(newPos, dt);
	if(timer >= 20.f)
	{
		timer = 0.f;
		on_success();
	}
}
