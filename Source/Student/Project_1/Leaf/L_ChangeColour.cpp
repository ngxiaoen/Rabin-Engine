#include <pch.h>
#include "L_ChangeColour.h"
#include "../Agent/BehaviorAgent.h"

void L_ChangeColour::on_enter()
{
	BehaviorNode::on_leaf_enter();
}

void L_ChangeColour::on_update(float dt)
{
	agent->set_color(Vec3{ RNG::range(0.f, 1.f), RNG::range(0.f, 1.f), RNG::range(0.f, 1.f) });
	on_success();
}

