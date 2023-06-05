#pragma once
#include "Misc/PathfindingDetails.hpp"

#define BITTOP 0b10000000
#define BITBOTTOM 0b01000000
#define BITLEFT 0b00100000
#define BITRIGHT 0b00010000
#define BITTOPLEFT 0b00001000
#define BITTOPRIGHT 0b00000100
#define BITBOTTOMLEFT 0b00000010
#define BITBOTTOMRIGHT 0b00000001

enum ON_LIST
{
    NOTLISTED,
    OPENLIST,
    CLOSEDLIST
};
struct MyGridPos
{
    std::uint8_t row;
    std::uint8_t col;
    MyGridPos() = default;
    MyGridPos(int& row, int& col)
    {
        this->row = row;
        this->col = col;
    }

    bool operator==(const GridPos& rhs) const
    {
        return row == rhs.row && col == rhs.col;
    }

    bool operator!=(const GridPos& rhs) const
    {
        return row != rhs.row || col != rhs.col;
    }

    MyGridPos& operator=(GridPos& rhs)
    {
        row = rhs.row;
        col = rhs.col;
        return *this;
    }

    void clear()
    {
        row = 0;
        col = 0;
    }
};


struct Node
{
    Node* parent;       // 8 Bytes
    GridPos gridPos;    // 8 Bytes
    float finalCost;    // 4 Bytes
    float givenCost;    // 4 Bytes
    ON_LIST onList;     // 1 Byte

    //unsigned char bit size is 8
    unsigned char neighbourBits;

};

//struct rubberNode
//{
//    rubberNode* parent;
//    Vec3 worldPos;
//};

class UnorderedListFastArray
{
public:
    UnorderedListFastArray();
    int filledSize;
    Node* nodeArray[800] = {};
    void PushNode(Node* toPush);
    Node* PopCheapest();
};

class AStarPather
{
public:
    /*
        The class should be default constructible, so you may need to define a constructor.
        If needed, you can modify the framework where the class is constructed in the
        initialize functions of ProjectTwo and ProjectThree.
    */

    AStarPather();
    /* ************************************************** */
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    void preprocess();
    void initArray();

    PathResult compute_path(PathRequest& request);
    /* ************************************************** */

    /*
        You should create whatever functions, variables, or classes you need.
        It doesn't all need to be in this header and cpp, structure it whatever way
        makes sense to you.
    */
    std::array<std::function<float(GridPos, GridPos)>, 5> heuristicArray;
    Vec3 catMullRom(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, float t);
    float time;
    ////std::array<std::pair<int, int>, 8> offsetArray =
    ////{
    ////    std::pair{1, -1},
    ////    std::pair{-1, -1},
    ////    std::pair{1, 1},
    ////    std::pair{-1, 1},
    ////    std::pair{1, 0},
    ////    std::pair{-1, 0},
    ////    std::pair{0, -1},
    ////    std::pair{0, 1}
    ////};

    ////typedef std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> pQueue;
    Node* allNodes;
    UnorderedListFastArray nodeList;
    //std::vector<rubberNode*> rubberList;
    //pQueue nodeQueue;
    //std::set<Node*> nodeSet;

};