#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_ShootHuman : public BaseNode<L_ShootHuman>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float ogSpeed;
};