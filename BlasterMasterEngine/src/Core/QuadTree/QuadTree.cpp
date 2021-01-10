#include "d3dpch.h"
#include "QuadTree.h"
#include "Core/SceneManager/SceneManager.h"
QuadTree::~QuadTree()
{
}

QuadTree::QuadTree(int pLevel, RECT pBound)
{
    bound = pBound;
    level = pLevel;
}

void QuadTree::Clear()
{
    objects.clear();

    for (size_t index = 0; index < nodes.size(); index++)
    {
        if (nodes[index] != NULL)
        {
            nodes[index]->Clear();
            nodes[index] = NULL;
        }
    }
}

void QuadTree::Insert(std::shared_ptr<Object2D>& object)
{
    if (object->boxCollider == NULL)
        return;

    float mapHeight = SceneManager::GetActiveScene()->GetMapSize().height;

    RECT objectBound = {0, 0, 0, 0};
    objectBound.left = object->boxCollider->topLeft.x;
    objectBound.top = mapHeight - object->boxCollider->topLeft.y;
    objectBound.right = objectBound.left + object->boxCollider->size.width;
    objectBound.bottom = objectBound.top + object->boxCollider->size.height;

    if (nodes[0] != NULL)
    {
        int index = GetIndex(objectBound);

        if (index != -1)
        {
            nodes[index]->Insert(object);
            return;
        }
    }

    objects.emplace_back(object);
    if (objects.size() > MAX_OBJECTS_QUADTREE && level < MAX_LEVELS_QUADTREE) 
    {
        if (nodes[0] == NULL)
        {
            Split();
        }

        for (auto it = objects.begin(); it != objects.end();)
        {
            RECT objectBound = { 0, 0, 0, 0 };
            objectBound.left = (*it)->boxCollider->topLeft.x;
            objectBound.top = mapHeight - (*it)->boxCollider->topLeft.y;
            objectBound.right = objectBound.left + (*it)->boxCollider->size.width;
            objectBound.bottom = objectBound.top + (*it)->boxCollider->size.height;

            int index = GetIndex(bound);

            if (index != -1)
            {
                nodes[index]->Insert(*it);
                it = objects.erase(it);
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
       //     ||
       //  1  ||  0
       //_____||_____
       //  2  ||  3
       //     ||

    RECT subBound = {0, 0, 0, 0};

    int width = (bound.right - bound.left) / 2;
    int height = (bound.bottom - bound.top) / 2;

    //top right

    subBound.left = bound.left + width;
    subBound.right = subBound.left + width;
    subBound.top = bound.top;
    subBound.bottom = subBound.top + height;
    nodes[0] = std::make_unique<QuadTree>(level + 1, subBound);

    //top left
    subBound.left = bound.left;
    subBound.right = subBound.left + width;
    subBound.top = bound.top;
    subBound.bottom = subBound.top + height;
    nodes[1] = std::make_unique<QuadTree>(level + 1, subBound);

    //bottom left
    subBound.left = bound.left;
    subBound.right = subBound.left + width;
    subBound.top = bound.top + height;
    subBound.bottom = subBound.top + height;
    nodes[2] = std::make_unique<QuadTree>(level + 1, subBound);

    //bottom right
    subBound.left = bound.left + width;
    subBound.right = subBound.left + width;
    subBound.top = bound.top + height;
    subBound.bottom = subBound.top + height;
    nodes[3] = std::make_unique<QuadTree>(level + 1, subBound);
}

int QuadTree::GetIndex(RECT body)
{
    int index = -1;

    float verticalMidpoint = bound.left + (bound.right - bound.left) / 2.0f;
    float horizontalMidpoint = bound.top + (bound.bottom - bound.top) / 2.0f;

    bool topQuadrant = (body.bottom < horizontalMidpoint);

    bool bottomQuadrant = (body.top > horizontalMidpoint);

    if (body.right < verticalMidpoint)
    {
        if (topQuadrant)
        {
            index = 1;
        }
        else if (bottomQuadrant)
        {
            index = 2;
        }
    }
    else if (body.left > verticalMidpoint)
    {
        if (topQuadrant)
        {
            index = 0;
        }
        else if (bottomQuadrant)
        {
            index = 3;
        }
    }

    return index;
}

void QuadTree::Retrieve(std::list<std::shared_ptr<Object2D>>& objectsOut, std::shared_ptr<Object2D>& object)
{
    float mapHeight = SceneManager::GetActiveScene()->GetMapSize().height;

    RECT objectBound = { 0, 0, 0, 0 };
    objectBound.left = object->boxCollider->topLeft.x;
    objectBound.top = mapHeight - object->boxCollider->topLeft.y;
    objectBound.right = objectBound.left + object->boxCollider->size.width;
    objectBound.bottom = objectBound.top + object->boxCollider->size.height;

    int index = GetIndex(objectBound);

    if (nodes[0] != NULL)
    {
        if (index != -1)
        {
            nodes[index]->Retrieve(objectsOut, object);
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                nodes[i]->Retrieve(objectsOut, object);
            }
        }
    }

    for (auto innerObject : objects)
    {
        objectsOut.emplace_back(innerObject);
    }
}