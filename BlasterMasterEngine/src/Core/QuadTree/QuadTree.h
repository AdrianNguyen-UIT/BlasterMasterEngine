#pragma once
#include "Object/Object.h"
class QuadTree
{
public:

    QuadTree(int level, RECT bound, RECT orignalBound);
    ~QuadTree();
    void Clear();
    void InsertObject(std::shared_ptr<Object2D>& object);
    void GetObjectsCollideAble(std::list<std::shared_ptr<Object2D>> &objectsOut, std::shared_ptr<Object2D>& object);


private:
    std::array<std::unique_ptr<QuadTree>, 4> mNodes;
    std::list<std::shared_ptr<Object2D>> mObjects;
    int mLevel;
    RECT mOriginalBound;
    RECT mBound;

private:
    int GetIndex(RECT body);

    void Split();

};