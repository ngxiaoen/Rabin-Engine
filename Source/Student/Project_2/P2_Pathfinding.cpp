#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"
//check corner cutting diagonal check
//set parent node to nullptr
//settings.debug colour for terrain colouring
#pragma region Extra Credit
bool ProjectTwo::implemented_floyd_warshall()
{
    return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
    return false;
}

bool ProjectTwo::implemented_jps_plus()
{
    return false;
}
#pragma endregion

AStarPather::AStarPather()
{
    std::function<float(GridPos, GridPos)> ManhattanFunc;
    ManhattanFunc = [](GridPos lhs, GridPos rhs) ->float
    {
        return static_cast<float>(abs(lhs.col - rhs.col) + abs(lhs.row - rhs.row));
    };

    std::function<float(GridPos, GridPos)> ChebyshevFunc;
    ChebyshevFunc = [](GridPos lhs, GridPos rhs) ->float
    {
        return static_cast<float>(std::max(abs(lhs.col - rhs.col), abs(lhs.row - rhs.row)));
    };

    std::function<float(GridPos, GridPos)> EuclideanFunc;
    EuclideanFunc = [](GridPos lhs, GridPos rhs) ->float
    {
        return static_cast<float>(std::sqrt((abs(lhs.col - rhs.col) * abs(lhs.col - rhs.col))
            + (abs(lhs.row - rhs.row) * abs(lhs.row - rhs.row))));
    };
    std::function<float(GridPos, GridPos)> OctileFunc;
    OctileFunc = [](GridPos lhs, GridPos rhs) ->float
    {
        return static_cast<float>(std::min(abs(lhs.col - rhs.col), abs(lhs.row - rhs.row)) * 1.41 + std::max(abs(lhs.col - rhs.col),
            abs(lhs.row - rhs.row)) - std::min(abs(lhs.col - rhs.col), abs(lhs.row - rhs.row)));
    };
    std::function<float(GridPos, GridPos)> InconsistentFunc;
    InconsistentFunc = [](GridPos lhs, GridPos rhs) ->float
    {
        if ((lhs.row + lhs.col) % 2 > 0)
        {
            return static_cast<float>(std::sqrt((abs(lhs.col - rhs.col) * abs(lhs.col - rhs.col))
                + (abs(lhs.row - rhs.row) * abs(lhs.row - rhs.row))));
        }
        return 0;
    };

    heuristicArray =
    {
        OctileFunc,
        ChebyshevFunc,
        InconsistentFunc,
        ManhattanFunc,
        EuclideanFunc
    };

}

bool AStarPather::initialize()
{
    // handle any one-time setup requirements you have

    /*
        If you want to do any map-preprocessing, you'll need to listen
        for the map change message.  It'll look something like this:

        Callback cb = std::bind(&AStarPather::your_function_name, this);
        Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

        There are other alternatives to using std::bind, so feel free to mix it up.
        Callback is just a typedef for std::function<void(void)>, so any std::invoke'able
        object that std::function can wrap will suffice.
    */
    Callback cb = std::bind(&AStarPather::preprocess, this);
    Messenger::listen_for_message(Messages::MAP_CHANGE, cb);
    return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::preprocess()
{
    initArray();
    //change all data back to original
    if (allNodes == nullptr)
        return;

    //if neighbour is wall set flag 1
    //row = y
    //col = x

    for (int row{ 0 }; row < terrain->get_map_height(); ++row)
    {
        for (int col{ 0 }; col < terrain->get_map_width(); ++col)
        {
            unsigned char temp = 0;
            //============ NEIGHBOUR ============//
            //bottom left is 0,0

            //top
            if ((row + 1) >= terrain->get_map_height() || terrain->is_wall(GridPos{ row + 1, col })) //check if out of bounds
            {
                temp |= BITTOP;
            }
            //down
            if ((row - 1 < 0) || terrain->is_wall(GridPos{ row - 1, col })) //check if out of bounds
            {
                temp |= BITBOTTOM;
            }
            //left
            if ((col - 1 < 0) || terrain->is_wall(GridPos{ row , col - 1 }))
            {
                temp |= BITLEFT;
            }
            //right
            if ((col + 1 >= terrain->get_map_width()) || terrain->is_wall(GridPos{ row, col + 1 }))
            {
                temp |= BITRIGHT;
            }
            //topleft
            if ((col - 1 < 0 || row + 1 >= terrain->get_map_height()) || terrain->is_wall(GridPos{ row + 1, col - 1 }) ||
                temp & (BITTOP + BITLEFT))
            {
                temp |= BITTOPLEFT;
            }
            //topright
            if ((col + 1 >= terrain->get_map_width() || row + 1 >= terrain->get_map_height()) || terrain->is_wall(GridPos{ row + 1, col + 1 }) ||
                temp & (BITTOP + BITRIGHT))
            {
                temp |= BITTOPRIGHT;
            }
            //bottomleft
            if ((col - 1 < 0 || row - 1 < 0) || terrain->is_wall(GridPos{ row - 1, col - 1 }) ||
                temp & (BITBOTTOM + BITLEFT))
            {
                temp |= BITBOTTOMLEFT;
            }
            //bottomright
            if ((col + 1 >= terrain->get_map_width() || row - 1 < 0) || terrain->is_wall(GridPos{ row - 1, col + 1 }) ||
                temp & (BITBOTTOM + BITRIGHT))
            {
                temp |= BITBOTTOMRIGHT;
            }

            //============ NEIGHBOUR ============//

            allNodes[row * terrain->get_map_width() + col] = Node{ nullptr, GridPos{row,col},
                 0.f,0.f, ON_LIST::NOTLISTED, temp };
        }
    }
}

void AStarPather::initArray()
{
    allNodes = new Node[1600];
    for (int row{ 0 }; row < 40; ++row)
    {
        for (int col{ 0 }; col < 40; ++col)
        {
            *(allNodes + row * terrain->get_map_width() + col) = Node{ nullptr, GridPos{row,col},
                0.f,0.f, ON_LIST::NOTLISTED };
        }
    }
}

void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */
    free(allNodes);
}


Vec3 AStarPather::catMullRom(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, float t)
{
    Vec3 temp = p1 * ((-0.5f * t * t * t) + (t * t) - (0.5f * t)) +
        p2 * ((1.5f * t * t * t) - (2.5f * t * t) + 1.0f) +
        p3 * ((-1.5f * t * t * t) + (2.0f * t * t) + 0.5f * t) +
        p4 * ((0.5f * t * t * t) - (0.5f * t * t));

    return temp;
}
PathResult AStarPather::compute_path(PathRequest& request)
{
    /*
        This is where you handle pathing requests, each request has several fields:

        start/goal - start and goal world positions
        path - where you will build the path upon completion, path should be
            start to goal, not goal to start
        heuristic - which heuristic calculation to use
        weight - the heuristic weight to be applied
        newRequest - whether this is the first request for this path, should generally
            be true, unless single step is on

        smoothing - whether to apply smoothing to the path
        rubberBanding - whether to apply rubber banding
        singleStep - whether to perform only a single A* step
        debugColoring - whether to color the grid based on the A* state:
            closed list nodes - yellow
            open list nodes - blue

            use terrain->set_color(row, col, Colors::YourColor);
            also it can be helpful to temporarily use other colors for specific states
            when you are testing your algorithms

        method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
            will be A* generally, unless you implement extra credit features

        The return values are:
            PROCESSING - a path hasn't been found yet, should only be returned in
                single step mode until a path is found
            COMPLETE - a path to the goal was found and has been built in request.path
            IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path
    */

    // WRITE YOUR CODE HERE
    //If(request.newRequest) {
    //    Initialize everything.
    //    Clear Open / Closed Lists.
    //        Push Start Node onto the Open List with cost of f(x) = g(x) + (h(x) * weight).
    //}
    //While(Open List is not empty) {
    //    parentNode = Pop cheapest node off Open List.
    //        If parentNode is the Goal Node, then path found(return PathResult::COMPLETE).
    //        Place parentNode on the Closed List.
    //        For(all valid neighboring child nodes of parentNode) {
    //        Compute its cost, f(x) = g(x) + (h(x) * weight)
    //            If child node isn�t on Open or Closed list, put it on Open List.
    //            Else if child node is on Open or Closed List, AND this new one is cheaper,
    //            then take the old expensive one off both lists and put this new
    //            cheaper one on the Open List.
    //    }
    //    If taken too much time this frame(or if request.settings.singleStep == true),
    //        abort search for now and resume next frame(return PathResult::PROCESSING).
    //}
    //Open List empty, thus no path possible(return PathResult::IMPOSSIBLE).
    if (request.newRequest) {
        request.path.clear();
        GridPos start = terrain->get_grid_position(request.start);
        GridPos goal = terrain->get_grid_position(request.goal);
        //request.settings.rubberBanding


        //reset list
        nodeList = UnorderedListFastArray();

        for (int i{ 0 }; i < 1600; ++i)
        {
            allNodes[i].onList = NOTLISTED;
            allNodes[i].parent = nullptr;
        }

        //initialize start node
        Node& temp = allNodes[start.row * terrain->get_map_width() + start.col];
        temp.onList = OPENLIST;
        temp.finalCost = (heuristicArray[static_cast<int>(request.settings.heuristic)])(start, goal) * request.settings.weight;
        temp.givenCost = 0.f;

        //put in starting node
        nodeList.PushNode(&temp);

    }
    auto setNodes = [&](Node& _childNode, Node* _parentNode, float gcost)
    {
        const float cost = gcost + (heuristicArray[static_cast<int>(request.settings.heuristic)])(_childNode.gridPos, terrain->get_grid_position(request.goal)) * request.settings.weight;

        if (_childNode.onList == NOTLISTED)
        {
            _childNode.parent = _parentNode;
            _childNode.onList = OPENLIST;
            _childNode.givenCost = gcost;
            _childNode.finalCost = cost;
            nodeList.PushNode(&_childNode);
            if (request.settings.debugColoring)
            {
                terrain->set_color(_childNode.gridPos, Colors::Blue);
            }
        }
        else
        {
            if (cost < _childNode.finalCost)
            {
                _childNode.parent = _parentNode;
                _childNode.givenCost = gcost;
                _childNode.finalCost = cost;
                if (_childNode.onList == CLOSEDLIST)
                {
                    _childNode.onList = OPENLIST;
                    nodeList.PushNode(&_childNode);
                    if (request.settings.debugColoring)
                    {
                        terrain->set_color(_childNode.gridPos, Colors::Blue);
                    }
                }
                _childNode.onList = OPENLIST;

            }
        }
    };

    while (nodeList.filledSize != 0)
    {
        Node* parentNode = nodeList.PopCheapest();
        if (request.settings.debugColoring)
        {
            terrain->set_color(parentNode->gridPos, Colors::Yellow);
        }
        if (parentNode->gridPos == terrain->get_grid_position(request.goal))
        {
            //if rubberbanding on
            if (request.settings.rubberBanding)
            {
                std::vector<Node*> finalBandArray;

                Node* first = parentNode;
                Node* second = parentNode->parent;
                Node* third = parentNode->parent->parent;

                //check difference for col and row
                //needs 3 points

                while (third != nullptr)
                {
                    int tempMaxY = std::max(first->gridPos.row, third->gridPos.row);
                    int tempMaxX = std::max(first->gridPos.col, third->gridPos.col);
                    int tempMinY = std::min(first->gridPos.row, third->gridPos.row);
                    int tempMinX = std::min(first->gridPos.col, third->gridPos.col);

                    bool hasWall{ false };

                    for (int i{ tempMinX }; i < tempMaxX + 1; ++i)
                    {
                        for (int j{ tempMinY }; j < tempMaxY + 1; ++j)
                        {
                            if (terrain->is_wall(allNodes[j * terrain->get_map_width() + i].gridPos))
                            {
                                hasWall = true;
                            }
                        }
                    }

                    if (hasWall == false)
                    {
                        //skip one
                        second = third;
                        third = third->parent;
                    }
                    else
                    {
                        //correct positions so place
                        finalBandArray.emplace_back(first);
                        first = second;
                        second = third;
                        third = third->parent;
                        hasWall = false;
                    }
                }
                finalBandArray.emplace_back(first);
                finalBandArray.emplace_back(second);

                ////before put into final check if smoothing
                //if (request.settings.smoothing)
                //{
                //    auto findMiddle = [&](Vec3 lhs, Vec3 rhs)->Vec3
                //    {
                //        float heuristic = static_cast<float>(std::sqrt((abs(lhs.x - rhs.x) * abs(lhs.x - rhs.x))
                //            + (abs(lhs.z - rhs.z) * abs(lhs.z - rhs.z))));

                //        if (heuristic > 1.5f)
                //        {
                //            Vec3 temp = (lhs + rhs) * 0.5f;
                //            return findMiddle(lhs, temp);
                //        }

                //    };
                //    //check each point against each other
                //    for (int i{ 0 }; i < finalBandArray.size(); ++i)
                //    {
                //        for (int j{ 1 }; j < finalBandArray.size() - 1; ++j)
                //        {
                //            //if dist too high

                //        }
                //    }
                //}
                //else
                //{
                //}
                for (int i{ 0 }; i < finalBandArray.size(); ++i)
                {
                    request.path.push_front(terrain->get_world_position(finalBandArray[i]->gridPos));
                }
                return PathResult::COMPLETE;
            }

            if (request.settings.smoothing)
            {
                std::vector<Vec3> finalSmoothArray;

                //Node* first, * second, * third, * fourth;
                //if (request.settings.rubberBanding)
                //{

                //}
                //else
                //{
                //}
                Node* first = parentNode;
                Node* second = parentNode->parent;
                Node* third = parentNode->parent->parent;
                Node* fourth = parentNode->parent->parent->parent;
                


                while (fourth != nullptr)
                {
                    //if end when p4 is at start
                    if (fourth->gridPos == terrain->get_grid_position(request.start))
                    {
                        //do last 2 iterations
                        //return the path
                        finalSmoothArray.emplace_back(terrain->get_world_position(second->gridPos));
                        for (int k{ 1 }; k < 4; ++k)
                        {
                            finalSmoothArray.emplace_back(catMullRom(
                                terrain->get_world_position(first->gridPos),
                                terrain->get_world_position(second->gridPos),
                                terrain->get_world_position(third->gridPos),
                                terrain->get_world_position(fourth->gridPos), k * 0.25f));
                        }

                        for (int i{ 1 }; i < 4; ++i)
                        {
                            finalSmoothArray.emplace_back(catMullRom(
                                terrain->get_world_position(second->gridPos),
                                terrain->get_world_position(third->gridPos),
                                terrain->get_world_position(fourth->gridPos),
                                terrain->get_world_position(fourth->gridPos), i * 0.25f));
                        }
                        finalSmoothArray.emplace_back(terrain->get_world_position(fourth->gridPos));

                        for (int j{ 0 }; j < finalSmoothArray.size(); ++j)
                        {
                            request.path.push_front(finalSmoothArray[j]);
                        }
                        return PathResult::COMPLETE;
                    }
                    //if start when smooth array is empty
                    if (finalSmoothArray.size() == 0)
                    {
                        finalSmoothArray.emplace_back(terrain->get_world_position(first->gridPos));
                        for (int i{ 1 }; i < 4; ++i)
                        {
                            finalSmoothArray.emplace_back(catMullRom(
                                terrain->get_world_position(first->gridPos),
                                terrain->get_world_position(first->gridPos),
                                terrain->get_world_position(second->gridPos),
                                terrain->get_world_position(third->gridPos), i * 0.25f));
                        }
                    }
                    else
                    {
                        finalSmoothArray.emplace_back(terrain->get_world_position(second->gridPos));
                        //normal scenario
                        for (int i{ 1 }; i < 4; ++i)
                        {
                            finalSmoothArray.emplace_back(catMullRom(
                                terrain->get_world_position(first->gridPos),
                                terrain->get_world_position(second->gridPos),
                                terrain->get_world_position(third->gridPos),
                                terrain->get_world_position(fourth->gridPos), i * 0.25f));
                        }
                        //move forward after completion
                        first = second;
                        second = third;
                        third = fourth;
                        fourth = fourth->parent;
                    }
                }

            }
            //making final path
            while (parentNode != nullptr)
            {
                request.path.push_front(terrain->get_world_position(parentNode->gridPos));
                parentNode = parentNode->parent;
            }
            return PathResult::COMPLETE;
        }

        parentNode->onList = CLOSEDLIST;
        if (request.settings.debugColoring)
        {
            terrain->set_color(parentNode->gridPos, Colors::Yellow);
        }

        if (!(parentNode->neighbourBits & BITBOTTOMRIGHT))
        {
            Node& childNode = allNodes[(parentNode->gridPos.row - 1) * terrain->get_map_width() + (parentNode->gridPos.col + 1)];
            setNodes(childNode, parentNode, parentNode->givenCost + 1.41f);
        }
        if (!(parentNode->neighbourBits & BITBOTTOMLEFT))
        {
            Node& childNode = allNodes[(parentNode->gridPos.row - 1) * terrain->get_map_width() + (parentNode->gridPos.col - 1)];
            setNodes(childNode, parentNode, parentNode->givenCost + 1.41f);
        }
        if (!(parentNode->neighbourBits & BITTOPRIGHT))
        {
            Node& childNode = allNodes[(parentNode->gridPos.row + 1) * terrain->get_map_width() + (parentNode->gridPos.col + 1)];
            setNodes(childNode, parentNode, parentNode->givenCost + 1.41f);
        }
        if (!(parentNode->neighbourBits & BITTOPLEFT))
        {
            Node& childNode = allNodes[(parentNode->gridPos.row + 1) * terrain->get_map_width() + (parentNode->gridPos.col - 1)];
            setNodes(childNode, parentNode, parentNode->givenCost + 1.41f);
        }
        if (!(parentNode->neighbourBits & BITRIGHT))
        {
            Node& childNode = allNodes[(parentNode->gridPos.row) * terrain->get_map_width() + (parentNode->gridPos.col + 1)];
            setNodes(childNode, parentNode, parentNode->givenCost + 1.f);
        }
        if (!(parentNode->neighbourBits & BITLEFT))
        {
            Node& childNode = allNodes[(parentNode->gridPos.row) * terrain->get_map_width() + (parentNode->gridPos.col - 1)];
            setNodes(childNode, parentNode, parentNode->givenCost + 1.f);
        }
        if (!(parentNode->neighbourBits & BITBOTTOM))
        {
            Node& childNode = allNodes[(parentNode->gridPos.row - 1) * terrain->get_map_width() + (parentNode->gridPos.col)];
            setNodes(childNode, parentNode, parentNode->givenCost + 1.f);
        }
        if (!(parentNode->neighbourBits & BITTOP))
        {
            Node& childNode = allNodes[(parentNode->gridPos.row + 1) * terrain->get_map_width() + (parentNode->gridPos.col)];
            setNodes(childNode, parentNode, parentNode->givenCost + 1.f);
        }

        if (request.settings.singleStep == true)
        {
            return PathResult::PROCESSING;
        }
    }

    //Just sample code, safe to delete
    return PathResult::IMPOSSIBLE;
}

UnorderedListFastArray::UnorderedListFastArray()
{
    filledSize = 0;
}

void UnorderedListFastArray::PushNode(Node* toPush)
{
    if (nodeArray == nullptr)
        return;

    nodeArray[filledSize++] = toPush;

}

Node* UnorderedListFastArray::PopCheapest()
{
    int minIndex{ 0 };

    for (int i{ 0 }; i < filledSize; ++i)
    {
        if (nodeArray[i]->finalCost < nodeArray[minIndex]->finalCost)
        {
            minIndex = i;
        }
    }
    //swaps pointer val in the 2 positions
    filledSize--;
    std::swap(nodeArray[minIndex], nodeArray[filledSize]);
    return nodeArray[filledSize];
}

