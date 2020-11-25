#include "d3dpch.h"
#include "QuadTree.h"

QuadTree::~QuadTree()
{
}

QuadTree::QuadTree(int level, RECT bound, RECT originalBound)
{
    mBound = bound;
    mLevel = level;
    mOriginalBound = originalBound;
}

void QuadTree::Clear()
{
}

void QuadTree::InsertObject(std::shared_ptr<Object2D>& object)
{
    RECT objectBound = { object->transform->position.x - object->boxCollider->size.width / 2,
        mOriginalBound.bottom - object->transform->position.y - object->boxCollider->size.height / 2,
        objectBound.left + object->boxCollider->size.width,
        objectBound.top + object->boxCollider->size.height};

    if (mNodes[0])
    {
        int index = GetIndex(objectBound);

        if (index != -1)
        {
            mNodes[index]->InsertObject(object);
            return;
        }
    }

    mObjects.emplace_back(object);
    if (mObjects.size() > MAX_OBJECTS_QUADTREE && mLevel < MAX_LEVELS_QUADTREE) 
    {
        if (!mNodes[0])
        {
            Split();
        }

        for (auto it = mObjects.begin(); it != mObjects.end();)
        {
            RECT bound = { (*it)->transform->position.x - (*it)->boxCollider->size.width / 2,
                mOriginalBound.bottom - (*it)->transform->position.y - (*it)->boxCollider->size.height / 2,
                bound.left + (*it)->boxCollider->size.width,
                bound.top + (*it)->boxCollider->size.height };

            int index = GetIndex(bound);
            if (index != -1)
            {
                mNodes[index]->InsertObject(*it);
                it = mObjects.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void QuadTree::Split()
{
    RECT bound;

    int width = (mBound.right - mBound.left) / 2;
    int height = (mBound.bottom - mBound.top) / 2;

    bound.left = mBound.left;
    bound.right = bound.left + width;
    bound.top = mBound.top;
    bound.bottom = bound.top + height;
    mNodes[0] = std::make_unique<QuadTree>(mLevel + 1, bound, mOriginalBound);

    bound.left = mBound.left + width;
    bound.right = bound.left + width;
    bound.top = mBound.top;
    bound.bottom = bound.top + height;
    mNodes[1] = std::make_unique<QuadTree>(mLevel + 1, bound, mOriginalBound);

    bound.left = mBound.left;
    bound.right = bound.left + width;
    bound.top = mBound.top + height;
    bound.bottom = bound.top + height;
    mNodes[2] = std::make_unique<QuadTree>(mLevel + 1, bound, mOriginalBound);

    bound.left = mBound.left + width;
    bound.right = bound.left + width;
    bound.top = mBound.top + height;
    bound.bottom = bound.top + height;
    mNodes[3] = std::make_unique<QuadTree>(mLevel + 1, bound, mOriginalBound);
}


int QuadTree::GetIndex(RECT body)
{
    float middleVerticle = mBound.left + (mBound.right - mBound.left) / 2.0f;
    float middleHorizontal = mBound.top + (mBound.bottom - mBound.top) / 2.0f;

    if (body.top > mBound.top && body.bottom < middleHorizontal)
    {
        if (body.left > mBound.left && body.right < middleVerticle)
        {
            return 0;
        }
        else if (body.left > middleVerticle && body.right < mBound.right)
        {
            return 1;
        }
    }
    else if (body.top > middleHorizontal && body.bottom < mBound.bottom)
    {
        if (body.left > mBound.left && body.right < middleVerticle)
        {
            return 2;
        }
        else if (body.left > middleVerticle && body.right < mBound.right)
        {
            return 3;
        }
    }

    return -1;
}

void QuadTree::GetObjectsCollideAble(std::list<std::shared_ptr<Object2D>>& objectsOut, std::shared_ptr<Object2D>& object)
{
    RECT objectBound = { object->transform->position.x - object->boxCollider->size.width / 2,
        mOriginalBound.bottom - object->transform->position.y - object->boxCollider->size.height / 2,
        objectBound.left + object->boxCollider->size.width,
        objectBound.top + object->boxCollider->size.height};

    int index = GetIndex(objectBound);

    if (index != -1 && mNodes[0]) 
    {
        mNodes[index]->GetObjectsCollideAble(objectsOut, object);
    }

    for (auto child : mObjects)
    {
        objectsOut.emplace_back(child);
    }
}