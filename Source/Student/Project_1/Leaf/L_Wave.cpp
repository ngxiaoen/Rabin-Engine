#include <pch.h>
#include "L_Wave.h"
#include "Projects/ProjectOne.h"


void L_Wave::on_enter()
{
    // set animation, speed, etc

	BehaviorNode::on_leaf_enter();
}

void L_Wave::on_update(float dt)
{
	timer += dt;
	auto lerpFunc = [](Vec3 start, Vec3 end, float percentage)
	{
		return start + (end - start) * percentage;
	};

	for(int i{0}; i < terrain->get_map_width();)
	{
		int numSquares = i + 1;
		//even
		//if(i%2 == 0)
		//{
		//	//set one in the middle
		//	terrain->pathLayer.set_value(i/2, i / 2, Colors::Blue);

		//	for (int j{ 0 }; j <= i; ++j)
		//	{
		//		terrain->pathLayer.set_value(j, i, Colors::Blue);
		//	}
		//}

		for(int j{0}; j<i; ++j)
		{
			for(int k{i}; k>0; --k)
			{
				terrain->set_color(k, j, Colors::White);
			}
		}

		
	}

	//auto a = agent->move_toward_point(lerpFunc(agent->get_position(),
	//	agent->get_position() - Vec3{ 0.f,20.f,0.f }, timer/5.f), dt);

	/*const auto pos = agent->get_position();
	auto a = agent->move_toward_point(
		 { pos.x,-20.f,pos.z }, dt);

	if(a)
	{
		timer = 0.f;
		on_success();
	}*/

    display_leaf_text();
}
