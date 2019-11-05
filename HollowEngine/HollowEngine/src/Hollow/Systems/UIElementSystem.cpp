#include <hollowpch.h>
#include "UIElementSystem.h"

#include "Hollow/Components/UITransform.h"
#include "Hollow/Components/UIImage.h"

#include "Hollow/Managers/RenderManager.h"

namespace Hollow
{
	UIElementSystem UIElementSystem::instance;

	void UIElementSystem::Init()
	{
	}

	void UIElementSystem::AddGameObject(GameObject* object)
	{
		CheckAllComponents<UITransform, UIImage>(object);
	}

	void UIElementSystem::Update()
	{
		for (unsigned int i = 0; i < mGameObjects.size(); ++i)
		{
			UITransform* uitransform = mGameObjects[i]->GetComponent<UITransform>();
			UIImage* uiimage = mGameObjects[i]->GetComponent<UIImage>();

			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(uitransform->mPosition, 1.0f));
			if (uitransform->mRotation != 0.0f)
			{
				model = glm::rotate(model, uitransform->mRotation, glm::vec3(0.0f, 0.0f, 1.0f));
			}
			if (uitransform->mTilt != 0.0f)
			{
				model = glm::rotate(model, uitransform->mTilt, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			model = glm::scale(model, glm::vec3(uitransform->mScale, 0.0f));

			UIRenderData uidata;

			uidata.mModelTransform = model;
			uidata.mpTexture = uiimage->mpTexture;
			uidata.mpShape = uiimage->mpShapeData;

			RenderManager::Instance().mUIRenderData.emplace_back(uidata);
		}
	}
}