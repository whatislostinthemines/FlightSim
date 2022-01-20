#pragma once
#include <bitset>
#include <vector>
typedef uint32_t EntityIndex;
typedef uint32_t EntityVersion;
typedef uint64_t EntityId;
const int MAX_COMPONENTS = 32;
const int MAX_ENTITIES = 400;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

struct ComponentPool {
	ComponentPool(size_t elementsize) {
		elementSize = elementsize;
		poolData = new char[elementsize * MAX_ENTITIES];
	}

	~ComponentPool() {
		delete[] poolData;
	}

	void* get(size_t index) {
		return poolData + index * elementSize;
	}

	char* poolData{ nullptr };
	size_t elementSize{ 0 };
};

struct Scene {
	struct EntityDesc {
		EntityId id;
		ComponentMask mask;
	};

	std::vector<EntityDesc> entities;
	std::vector<EntityIndex> freeEntities;
	std::vector<ComponentPool> componentPools;

	EntityId newEntity();

	template<typename T>
	T* assign(EntityId id);

	template<typename T>
	T* get(EntityId id);

	template<typename T>
	void remove(EntityId id);

	void destroyEntity(EntityId id);
};

extern int componentCounter;
template <class T>
int getId();

int getId() {
	return -1;
}


EntityId createEntityId(EntityIndex index, EntityVersion version);
EntityIndex getEntityIndex(EntityId id);
EntityVersion getEntityVersion(EntityId id);
bool isEntityValid(EntityId id);

#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0);

template<typename ...ComponentTypes>
struct SceneView {
	SceneView(Scene& scene) : scene(&scene) {
		if (sizeof...(ComponentTypes) == 0) {
			all = true;
		} else {
			int componentIds[] = { 0, getId<ComponentTypes>() ... };
			for (int i = 1; i < sizeof...(ComponentTypes) + 1; ++i) {
				componentMask.set(componentIds[i]);
			}
		}
	}
	struct Iterator {
		Iterator();
		EntityId operator*() const;
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		Iterator& operator++();
		
	};
	const Iterator begin() const;
	const Iterator end() const;

	Scene* scene{ nullptr };
	ComponentMask componentMask;
	bool all{ false };
};