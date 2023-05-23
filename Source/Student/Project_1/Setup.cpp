#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
    // Create your inital agents
   // auto tentacle1 = agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::test3);

   // tentacle1->get_blackboard().set_value("infertile", false);
   // tentacle1->get_blackboard().set_value("direction", 1);
   // tentacle1->get_blackboard().set_value("counter", 0);
   // 

   // auto tentacle2 = agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::test3);

   // tentacle2->get_blackboard().set_value("infertile", false);
   // tentacle2->get_blackboard().set_value("direction", 2);
   // tentacle2->get_blackboard().set_value("counter", 0);
   // 

   // auto tentacle3 = agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::test3);

   // tentacle3->get_blackboard().set_value("infertile", false);
   // tentacle3->get_blackboard().set_value("direction", 3);
   // tentacle3->get_blackboard().set_value("counter", 0);
   //);

   // auto tentacle4 = agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::test3);

   // tentacle4->get_blackboard().set_value("infertile", false);
   // tentacle4->get_blackboard().set_value("direction", 4);
   // tentacle4->get_blackboard().set_value("counter", 0);

    auto boat = agents->create_behavior_agent("boatAgent", BehaviorTreeTypes::boatTree);
    boat->set_scaling(Vec3{ 10.f, 0.4f, 50.f });
    boat->set_position(Vec3{ 0.f,0.f,0.f });

    auto human1 = agents->create_behavior_agent("humanAgent1", BehaviorTreeTypes::humanTree);
    auto human2 = agents->create_behavior_agent("humanAgent2", BehaviorTreeTypes::humanTree);

    std::vector<std::pair<std::wstring, Vec3>> humanPositions;
    humanPositions.emplace_back(std::pair<std::wstring, Vec3>(human1->get_debug_name(),
        Vec3{ 0.f, 0.f,0.f }));
    humanPositions.emplace_back(std::pair<std::wstring, Vec3>(human2->get_debug_name(),
        Vec3{ 0.f,0.f,0.f }));

    myGlobalBlackBoard->set_value("humanPositions", humanPositions);
    myGlobalBlackBoard->set_value("humanCount", 2);
    myGlobalBlackBoard->set_value("atCenter", false);


    //tentacle1->get_blackboard().set_value("loop",false);
    // you can technically load any map you want, even create your own map file,
    // but behavior agents won't actually avoid walls or anything special, unless you code that yourself
    // that's the realm of project 2 though
    terrain->goto_map(0);

    // you can also enable the pathing layer and set grid square colors as you see fit
    // works best with map 0, the completely blank map
    terrain->pathLayer.set_enabled(true);

    for (int i{ 0 }; i < terrain->get_map_width(); ++i)
        for (int j{ 0 }; j < terrain->get_map_height(); ++j)
            terrain->pathLayer.set_value(j, i, Colors::Blue);

    // camera position can be modified from this default as well
    auto camera = agents->get_camera_agent();
    camera->set_position(Vec3(-20.f, 70.0f, -20.f));
    camera->set_pitch(0.610865); // 35 degrees
    camera->set_yaw(0.785398); // 45 degrees

    //audioManager->SetVolume(0.5f);
    //audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
    // uncomment for example on playing music in the engine (must be .wav)
    // audioManager->PlayMusic(L"Assets\\Audio\\motivate.wav");
    // audioManager->PauseMusic(...);
    // audioManager->ResumeMusic(...);
    // audioManager->StopMusic(...);
}