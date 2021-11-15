#pragma once

class Actor;

class Component
{
public:
	// ������
	// ������Ʈ ������(���� ���� ������Ʈ�� �� ���� ���ŵȴ�)
	Component(Actor* owner, int updateOrder = 100);

	// �Ҹ���
	virtual ~Component();

	// ��Ÿ�ð����� �� ������Ʈ�� ������Ʈ
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const {return mUpdateOrder;}

private:
	// ������ ����
	Actor* mOwner;
	
	// ������Ʈ ������Ʈ ����
	int mUpdateOrder;
};