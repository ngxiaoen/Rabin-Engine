#include <pch.h>
#include "D_CheckShoot.h"

void D_CheckShoot::on_enter()
{
    BehaviorNode::on_enter();
}

void D_CheckShoot::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode *child = children.front();

    //work with selector
    if (myGlobalBlackBoard->get_value<bool>("shootHuman?"))
    {
        //myGlobalBlackBoard->set_value("shootHuman?", false);
        std::cout << "check_shoot" << std::endl;
        on_failure();
    }
    else
    {
		child->tick(dt);
        set_status(child->get_status());
        set_result(child->get_result());
    }
}
