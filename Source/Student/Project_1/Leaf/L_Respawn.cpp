#include <pch.h>
#include "L_Respawn.h"
#include "Agent/BehaviorAgent.h"
#include "TreeInfo.h"
void L_Respawn::on_enter()
{
    // set animation, speed, etc
    printf("Entered\n");
	BehaviorNode::on_leaf_enter();
}

void L_Respawn::on_update(float dt)
{
    agents->get_all_agents_by_type("boatAgent");
    

    auto human1 = agents->create_behavior_agent("humanAgent1", BehaviorTreeTypes::humanTree);
    auto human2 = agents->create_behavior_agent("humanAgent2", BehaviorTreeTypes::humanTree);
    human1->set_scaling(Vec3{ 1.f, 1.f, 1.f });
    human2->set_scaling(Vec3{ 1.f, 1.f, 1.f });
    std::vector<std::pair<std::wstring, Vec3>> humanPositions;
    humanPositions.emplace_back(std::pair<std::wstring, Vec3>(human1->get_debug_name(),
        Vec3{ 0.f, 0.f,0.f }));
    humanPositions.emplace_back(std::pair<std::wstring, Vec3>(human2->get_debug_name(),
        Vec3{ 0.f,0.f,0.f }));

    myGlobalBlackBoard->set_value("humanPositions", humanPositions);
    myGlobalBlackBoard->set_value("humanCount", 2);

    on_success();
    display_leaf_text();
}
