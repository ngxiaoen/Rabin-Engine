#include <pch.h>
#include "L_AlwaysTrue.h"


void L_AlwaysTrue::on_update(float dt)
{
    on_success();

    //std::cout << "always true";
    display_leaf_text();
}
