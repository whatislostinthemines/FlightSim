#include "ECS.h"

int componentCounter = 0;

EntityId Scene::newEntity() {
	if (!freeEntities.empty()) {
		EntityIndex newIndex = freeEntities.back();
		freeEntities.pop_back();
		EntityId newId = createEntityId(newIndex, getEntityVersion(entities[newIndex].id));
		entities[newIndex].id = newId;
		return entities[newIndex].id;
	}
	entities.push_back({ createEntityId(EntityIndex(entities.size()), 0), ComponentMask() });
	return entities.back().id;
}

template<typename T>
T* Scene::assign(EntityId id) {
	if (entities[GetEntityIndex(id)].id != id)
		return nullptr;

	int componentId = getId<T>();
	if (componentPools.size() <= componentId) {
		componentPools.resize(componentId + 1, nullptr);
	}
	if (componentPools[componentId] == nullptr) {
		componentPools[componentId] = new ComponentPool(sizeof(T));
	}

	T* component = new (componentPools[componentId]->get(getEntityIndex(id))) T();
	entities[getEntityIndex(id)].mask.set(componentId);
	
}

template <class T>
int getId() {
	static int componentId = componentCounter++;
	return componentId;
}

template<typename T>
T* Scene::get(EntityId entityId) {
	if (entities[GetEntityIndex(entityId)].id != entityId)
		return nullptr;
	int componentId = getId<T>();
	if (!entities[getEntityIndex(entityId)].mask.test(componentId))
		return nullptr;
	T* component = static_cast<T*>(componentPools[componentId]->get());
	return component;
}
template<typename T>
void Scene::remove(EntityId id) {
	if (entities[getEntityIndex(id)].id != id)
		return;
	int componentId = getId<T>();
	entities[getEntityIndex(id)].mask.reset(componentId);
}

void Scene::destroyEntity(EntityId id) {
	EntityId newId = createEntityId(EntityIndex(-1), getEntityVersion(id) + 1);
	entities[getEntityIndex(id)].id = newId;
	entities[getEntityIndex(id)].mask.reset();
	freeEntities.push_back(getEntityIndex(id));
}

EntityId createEntityId(EntityIndex index, EntityVersion version) {
	return ((EntityId)index << 32) | ((EntityId)version);
}
EntityIndex getEntityIndex(EntityId id) {
	return id >> 32;
}
EntityVersion getEntityVersion(EntityId id) {
	return (EntityVersion)id;
}
bool isEntityValid(EntityId id) {
	return (id >> 32) != EntityIndex(-1);
}