#include <pch.h>
#include "D_CheckHuman.h"

void D_CheckHuman::on_enter()
{
    BehaviorNode::on_enter();
}

void D_CheckHuman::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode *child = children.front();


    //work with selector
    if (myGlobalBlackBoard->get_value<int>("humanCount") == 0){

        child->tick(dt);
        set_status(child->get_status());
        set_result(child->get_result());
    }
    else
    {
        //check for this in human agent
        if(!myGlobalBlackBoard->get_value<bool>("grabBoat"))
        {
			myGlobalBlackBoard->set_value("shootHuman?", true);
	        
        }

        myGlobalBlackBoard->set_value("forceMove", true);
        myGlobalBlackBoard->set_value("atCenter", false);
        //always true
        on_failure();
        
    }
    display_leaf_text();
}
