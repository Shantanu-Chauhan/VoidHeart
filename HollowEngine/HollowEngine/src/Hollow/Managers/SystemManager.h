#pragma once
#include <vector>


namespace Hollow
{
	class GameObject;
	class System;
	class GameEvent;
	class SystemManager
	{
		SINGLETON(SystemManager)
	public:
		~SystemManager();

		void RegisterSystem(System* system)
		{
			mSystems.push_back(system);
		}

		void Init();
		void Update();
		void AddObjectToSystems(GameObject* GameObject);
		void BroadcastEventToSystems(GameEvent* event);
		void DeleteGameObejectInSystems(GameObject* GameObject);
		void DeleteAllGameObjectsInSystems();

	private:
		std::vector<System*> mSystems;
	};
}