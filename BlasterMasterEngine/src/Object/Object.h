#pragma once
#include "Core/DeviceResources/DeviceResources.h"
#include "Core/Time/Time.h"
#include "Component/Component.h"
#include "Core/Input/Input.h"

enum class Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum class Tag
{
	Default,
	Player,
	Monster,
	Boss,
	Item,
	Terrain
};

class Object2D : public std::enable_shared_from_this<Object2D>
{
public:
	Object2D(float x = 0, float y = 0);
	virtual ~Object2D() = default;

	friend class Renderer;
	friend class SceneManager;

private:
	bool readyToBeDestroy;
	D3DXVECTOR3 positionAsChild;
	D3DXVECTOR3 rotationAsChild;
	D3DXVECTOR3 scaleAsChild;
protected:
	int upCollision;
	int downCollision;
	int leftCollision;
	int rightCollision;
	BoxCollider2D broadphaseBox;
	std::list<std::pair<std::shared_ptr<Object2D>, Direction>> collidedObjects;

public:
	std::shared_ptr<Transform> transform;
	std::string name;
	Tag tag;
	bool enable;

	//Instances define
	std::unique_ptr<SpriteRenderer> spriteRenderer;
	std::unique_ptr<AnimationController> animationController;
	std::unique_ptr<Rigidbody> rigidbody;
	std::unique_ptr<BoxCollider2D> boxCollider;
	std::shared_ptr<Object2D> parentObject;
	std::list<std::shared_ptr<Object2D>> childObjects;

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void CreateResources() = 0;

	virtual void OnCollisionEnter() = 0;
	virtual void OnTriggerEnter() = 0;

public:
	template <class T>
	std::unique_ptr<T> GetComponent() { return std::make_unique<T>(); }
	std::shared_ptr<Object2D> GetPtr() { return shared_from_this(); }

	void SetEnable(bool p_Enable) { enable = p_Enable; }
	bool GetEnable() { return enable; }

	void RenderDebugRectangle(const D3DXMATRIX& worldToViewportMat);
	void AddChildObject(const std::shared_ptr<Object2D> child);
private:
	void Draw(DWORD flags);
	void InnerUpdate(const D3DXMATRIX& worldToViewportMat);
	void InnerStart();
	void DoCollision(std::shared_ptr<Object2D> object);
	bool CheckCollision(std::unique_ptr<BoxCollider2D>& col1, std::unique_ptr<BoxCollider2D>& col2);
	float SweptAABB(std::unique_ptr<BoxCollider2D>& col, Direction& result);
	BoxCollider2D GetSweptBroadphaseBox();
};