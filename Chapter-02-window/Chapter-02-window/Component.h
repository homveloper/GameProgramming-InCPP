#pragma once

class Actor;

class Component
{
public:
	// 생성자
	// 업데이트 순서값(작을 수록 컴포넌트가 더 빨리 갱신된다)
	Component(Actor* owner, int updateOrder = 100);

	// 소멸자
	virtual ~Component();

	// 델타시간으로 이 컴포넌트를 업데이트
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const {return mUpdateOrder;}

private:
	// 소유자 액터
	Actor* mOwner;
	
	// 컴포넌트 업데이트 순서
	int mUpdateOrder;
};