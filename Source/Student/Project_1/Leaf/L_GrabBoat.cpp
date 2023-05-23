#include <pch.h>
#include "L_GrabBoat.h"
#include "Agent/BehaviorAgent.h"
#include "TreeInfo.h"
void L_GrabBoat::on_enter()
{
    // set animation, speed, etc
    BoatPos = myGlobalBlackBoard->get_value<Vec3>("boatPos");
	BehaviorNode::on_leaf_enter();
}

void L_GrabBoat::on_update(float dt)
{
    agent->move_toward_point(BoatPos, dt);
    for(int i{0}; i<100; ++i)
    {
        if (!agent->get_blackboard().get_value<bool>("infertile"))
        {
            //create kraken agent but state set as grabbing
            auto newAgent = agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::test3);
            newAgent->get_blackboard().set_value("infertile", true);
            newAgent->get_blackboard().set_value("direction",
                agent->get_blackboard().get_value<int>("direction"));
            newAgent->get_blackboard().set_value("counter", 0);
        }
    }
    auto checkCenter = [](Vec3 pos, Vec3 cpos, float radius)
    {
        return (powf(pos.x - cpos.x, 2.f)
            + powf(pos.z - cpos.z, 2.f))
            <= powf(radius, 2.f);
    };

    if (checkCenter(agent->get_position(), BoatPos, 10.f))
    {
	    //reaching boat
        //check if boatpos is near centerpos if so stop
        //else continue circling
        //m_OrbitTime += particleComponent.m_Speed * Time::m_DeltaTime;
        //if ((m_OrbitTime * m_CurrentAngle) >= (2 * PI))
        //{
        //    m_OrbitTime = 0.f;
        //}
        //float dirx = ps.m_OffsetVelo.x * cos(m_CurrentAngle * m_OrbitTime);;
        //float diry = ps.m_OffsetVelo.y * sin(m_CurrentAngle * m_OrbitTime);;
        //float dirz = ps.m_OffsetVelo.z * cos(m_CurrentAngle * m_OrbitTime) * cos(m_CurrentAngle * m_OrbitTime);
        ////float dirz = 0.f;

        //particleComponent.m_Direction.x = dirx;
        //particleComponent.m_Direction.y = diry;
        //particleComponent.m_Direction.z = dirz;


        //transformComponent.SetLocalPosition(particleComponent.m_Direction);
        timer += dt;
        auto lerpFunc = [](Vec3 start, Vec3 end, float percentage)
        {
            return start + (end - start) * percentage;
        };

        std::vector<Vec3> fourPoints;
        fourPoints.emplace_back(BoatPos + Vec3{ offset.x, 0.f, offset.z });
        fourPoints.emplace_back(BoatPos + Vec3{ offset.x, 0.f, -offset.z });
        fourPoints.emplace_back(BoatPos + Vec3{ -offset.x, 0.f, -offset.z });
        fourPoints.emplace_back(BoatPos + Vec3{ -offset.x, 0.f, offset.z });

        for(size_t i{0}; i< fourPoints.size()-1; )
        {
            agent->move_toward_point(lerpFunc(agent->get_position(), 
                fourPoints[i], timer/4.f), dt);
            if(timer >= 4.f)
            {
                ++i;
            }
        }

        if (myGlobalBlackBoard->get_value<bool>("atCenter"))
            on_success();
        return;
    }
    display_leaf_text();
}
