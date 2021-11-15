#pragma once

#include <vector>
#include "Math.h"

class Game;
class Component;

class Actor
{
public:
	// 액터의 상태를 추적
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	// 생성자 & 소멸자
	Actor(Game* game);

	virtual ~Actor();

	// 액터를 갱신하기 위해 프레임마다 호출
	void Update(float deltaTime);

	// 액터에 부착된 모든 컴포넌트를 업데이트
	void UpdateComponents(float deltaTime);

	// 특정 액터에 특화된 업데이트 코드
	virtual void UpdateActor(float deltaTime);

	// 액터를 그리기 위해 프레임마다 호출
	virtual void Draw();

	// 컴포넌트 추가 제거
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	// getter & setter
	State GetState() { return mState;}

	const Vector2& GetPosition() const {return mPosition;}
	void SetPosition(const Vector2& position){mPosition = position;}



private:
	// 액터의 상태
	State mState;
	// 트랜스폼
	Vector2 mPosition;
	float mScale;
	float mRotation;

	// 액터가 보유한 컴포넌트들
	std::vector<Component*> mComponents;
	Game* game;

};