#include "SceneManager.h"
#include "DefaultAIUpdateSystem.h"

void defaultAIUpdateSystem(SceneManager* manager, EntityId id)
{
	auto ai = manager->scene.get<AIComponent>(id);
}