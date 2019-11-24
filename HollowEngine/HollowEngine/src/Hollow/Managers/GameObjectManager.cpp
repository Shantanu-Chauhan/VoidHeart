#include "hollowpch.h"

#include "GameObjectManager.h"
#include "SystemManager.h"
#include "MemoryManager.h"

#include "Hollow/Core/GameObject.h"

namespace Hollow {
	void GameObjectManager::AddGameObject(GameObject* GameObject)
	{
#if HW_DEBUG
		auto itr = std::find(mGameObjects.begin(), mGameObjects.end(), GameObject);
		if (itr == mGameObjects.end())
		{
#endif
			mGameObjects.push_back(GameObject);
#if HW_DEBUG
		}
#endif
		SystemManager::Instance().AddObjectToSystems(GameObject);
	}

	void GameObjectManager::DeleteGameObject(GameObject* GameObject)
	{
		GameObject->Destroy();
		mGameObjects.erase(std::find(mGameObjects.begin(), mGameObjects.end(), GameObject));
		SystemManager::Instance().DeleteGameObejectInSystems(GameObject);
		MemoryManager::Instance().DeleteGameObject(GameObject);
	}

	void GameObjectManager::DeleteAllGameObjects()
	{
		for (unsigned int i = 0; i < mGameObjects.size(); ++i)
		{
			mGameObjects[i]->Destroy();
			MemoryManager::Instance().DeleteGameObject(mGameObjects[i]);
		}
		mGameObjects.clear();
		SystemManager::Instance().DeleteAllGameObjectsInSystems();
	}

}
