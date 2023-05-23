#include <pch.h>
#include "L_FollowPath.h"
#include "Agent/BehaviorAgent.h"
#include "TreeInfo.h"
void L_FollowPath::on_enter()
{
    // set animation, speed, etc

    auto sinLerp = [](float amp, float frequency, float time, float shift)
    {
        return amp * sin(2 * PI * frequency * time + shift);
    };

    dir = agent->get_blackboard().get_value<int>("direction");
    agent->set_scaling(Vec3{1.f,1.f,1.f});
    //agent->set_pitch(80.f);

    //y(t) = A * sin(2 * PI * f * t + shift)
    agent->set_position(Vec3{ 50.f,0.f,50.f });

    switch (dir)
    {
    case 1:
        for (int i{ 50 }; i < 150; ++i)
        {
            nodes.emplace_back(Vec3{ static_cast<float>(i),
                sinLerp(25.f, 1.f, static_cast<float>(i) * deltaTime, 0.f), 50.f });
        }
        break;
    case 2:
        for (int i{ 50 }; i < 150; ++i)
        {
            nodes.emplace_back(Vec3{ 50.f,
                sinLerp(25.f, 1.f, static_cast<float>(i) * deltaTime, 0.f), static_cast<float>(i) });
        }
        break;
    case 3:
        for (int i{ 50 }; i > -50; --i)
        {
            nodes.emplace_back(Vec3{ static_cast<float>(i),
                sinLerp(25.f, 1.f, static_cast<float>(i) * deltaTime, 0.f), 50.f });
        }
        break;
    case 4:
        for (int i{ 50 }; i > -50; --i)
        {
            nodes.emplace_back(Vec3{ 50.f,
                sinLerp(25.f, 1.f, static_cast<float>(i) * deltaTime, 0.f), static_cast<float>(i) });
        }
        break;
    }
    BehaviorNode::on_leaf_enter();
}

void L_FollowPath::on_update(float dt)
{

    int i = agent->get_blackboard().get_value<int>("counter");

    auto result = agent->move_toward_point(nodes[i], dt);

    //agent->set_scaling(Vec3{ ogScale.x - i, ogScale.y - i, ogScale.z - i });
    if (result == true)
    {
        ++i;
        agent->get_blackboard().set_value("counter", i);
        if (!agent->get_blackboard().get_value<bool>("infertile"))
        {
            auto newAgent = agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::test3);
            newAgent->get_blackboard().set_value("infertile", true);
            newAgent->get_blackboard().set_value("direction", 
                agent->get_blackboard().get_value<int>("direction"));
            newAgent->get_blackboard().set_value("counter", 0);
            //newAgent->get_blackboard().set_value("timer", 0.f);
            //newAgent->get_blackboard().set_value("loop", false);
        }
        if (i == nodes.size() - 1)
        {
            on_success();
        }
    }




    display_leaf_text();
}