#include <pch.h>
#include "L_AlwaysTrue.h"


void L_AlwaysTrue::on_update(float dt)
{
    on_success();

    display_leaf_text();
}
