#pragma once
#include <unordered_set>

class Component;

class GameObject
{
public:
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
private:
	std::unordered_set<Component*> mComponents;
};