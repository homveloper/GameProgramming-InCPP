#pragma once

#include <vector>
#include "Math.h"

class Game;
class Component;

class Actor
{
public:
	// ������ ���¸� ����
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	// ������ & �Ҹ���
	Actor(Game* game);

	virtual ~Actor();

	// ���͸� �����ϱ� ���� �����Ӹ��� ȣ��
	void Update(float deltaTime);

	// ���Ϳ� ������ ��� ������Ʈ�� ������Ʈ
	void UpdateComponents(float deltaTime);

	// Ư�� ���Ϳ� Ưȭ�� ������Ʈ �ڵ�
	virtual void UpdateActor(float deltaTime);

	// ���͸� �׸��� ���� �����Ӹ��� ȣ��
	virtual void Draw();

	// ������Ʈ �߰� ����
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	// getter & setter
	State GetState() { return mState;}

	const Vector2& GetPosition() const {return mPosition;}
	void SetPosition(const Vector2& position){mPosition = position;}



private:
	// ������ ����
	State mState;
	// Ʈ������
	Vector2 mPosition;
	float mScale;
	float mRotation;

	// ���Ͱ� ������ ������Ʈ��
	std::vector<Component*> mComponents;
	Game* game;

};