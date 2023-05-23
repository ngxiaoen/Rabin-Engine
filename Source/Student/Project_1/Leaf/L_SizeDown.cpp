#include <pch.h>
#include "L_SizeDown.h"
#include "Agent/BehaviorAgent.h"

void L_SizeDown::on_enter()
{
    // set animation, speed, etc
    ogScale = agent->get_scaling();

	BehaviorNode::on_leaf_enter();
}

void L_SizeDown::on_update(float dt)
{
    timer += dt;
    auto lerp = [](float start, float end, float percentage)
    {
        return start + (end - start) * percentage;
    };
    agent->set_scaling(Vec3{ lerp(ogScale.x, 0.5f, timer / 30.f),
        lerp(ogScale.y, 0.5f, timer/30.f), lerp(ogScale.z, 0.5f, timer / 30.f) });

    if(ogScale.y == 0.5f)
    {
        timer = 0.f;
        on_success();
    }

    display_leaf_text();
}
