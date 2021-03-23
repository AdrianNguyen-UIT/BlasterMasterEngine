#pragma once
#include "Core/DeviceResources/DeviceResources.h"
#include "Core/SpriteResources/SpriteResources.h"
#include "Core/Time/Time.h"
#include "Component/Component.h"
#include "Core/Input/Input.h"

enum class Direction
{
	NONE,
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum class Tag
{
	Default,
	Player,
	Enemy,
	Boss,
	Item,
	Terrain,
	PlayerBullet,
	EnemyBullet,
	CheckPoint,
	Gate,
	Trap,
	Ladder,
	Punji
};

enum class Layer
{
	Ladder,
	Projectile,
	Sophia,
	Jason,
	Enemy,
	Particle,
	Gate
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
	D3DXVECTOR3 subPosition;
	D3DXVECTOR3 subRotation;
	D3DXVECTOR3 subScale;

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
	Color color;
	Layer layer;

	//Instances define
	std::unique_ptr<SpriteRenderer> spriteRenderer;
	std::unique_ptr<AnimationController> animationController;
	std::unique_ptr<Rigidbody> rigidbody;
	std::unique_ptr<BoxCollider2D> boxCollider;
	std::shared_ptr<Object2D> parentObject;
	std::list<std::shared_ptr<Object2D>> childObjects;

public:
	virtual void Start() {}
	virtual void Update() {}
	virtual void CreateResources() {}

	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) {}
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) {}
	virtual void OnCollisionStay(std::shared_ptr<Object2D> object) {}
	virtual void OnTriggerStay(std::shared_ptr<Object2D> object) {}
	virtual void OnCollisionExit(std::shared_ptr<Object2D> object) {}
	virtual void OnTriggerExit(std::shared_ptr<Object2D> object) {}

public:
	template <class T>
	std::unique_ptr<T> GetComponent() { return std::make_unique<T>(); }
	std::shared_ptr<Object2D> GetPtr() { return shared_from_this(); }

	void SetEnable(bool p_Enable) { enable = p_Enable; }
	bool GetEnable() { return enable; }

	void RenderDebugRectangle(const D3DXMATRIX& worldToViewportMat);
	void AddChildObject(const std::shared_ptr<Object2D> child);
	bool NoCollision();

private:
	void Draw(DWORD flags);
	void InnerUpdate(const D3DXMATRIX& worldToViewportMat);
	void InnerStart();
	void DoCollision(std::shared_ptr<Object2D> object);
	bool CheckCollision(std::unique_ptr<BoxCollider2D>& col1, std::unique_ptr<BoxCollider2D>& col2);
	float SweptAABB(std::unique_ptr<BoxCollider2D>& col, Direction& result);
	BoxCollider2D GetSweptBroadphaseBox();
	bool IsCollidable(std::shared_ptr<Object2D>& object);
};