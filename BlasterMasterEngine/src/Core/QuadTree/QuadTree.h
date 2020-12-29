#pragma once
#include "Object/Object.h"
class QuadTree
{
public:

    QuadTree(int pLevel, RECT pBound);
    ~QuadTree();
    void Clear();
    void Insert(std::shared_ptr<Object2D>& object);
    void Retrieve(std::list<std::shared_ptr<Object2D>> &objectsOut, std::shared_ptr<Object2D>& object);


private:
    std::array<std::unique_ptr<QuadTree>, 4> nodes;
    std::list<std::shared_ptr<Object2D>> objects;
    int level;
    RECT bound;

private:
    int GetIndex(RECT body);

    void Split();

};