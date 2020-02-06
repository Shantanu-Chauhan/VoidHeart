#include <hollowpch.h>
#include "ScriptingManager.h"

#include "Hollow/Components/Body.h"
#include "Hollow/Components/Camera.h"
#include "Hollow/Components/Transform.h"
#include "Hollow/Components/Material.h"
#include "Hollow/Components/Light.h"
#include "Hollow/Components/Script.h"

#include "Hollow/Managers/ResourceManager.h"
#include "Hollow/Managers/InputManager.h"
#include "Hollow/Managers/PhysicsManager.h"
#include "Hollow/Managers/AudioManager.h"

namespace Hollow
{
	void ScriptingManager::Init(rapidjson::Value::Object& data)
	{
		rootPath = data["FilePath"].GetString();
		ext = data["FileExtension"].GetString();

		lua.open_libraries(sol::lib::base, sol::lib::math);

		// Controller
		lua["CONTROLLER"] = lua.create_table_with(
			"A", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A,
			"B", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B,
			"X", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X,
			"Y", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y,
			"Back", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK,
			"Home", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_GUIDE,
			"Start", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_START,
			"LS", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSTICK,
			"RS", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSTICK,
			"LB", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
			"RB", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
			"DUP", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP,
			"DDOWN", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN,
			"DLEFT", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT,
			"DRIGHT", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
			"LX",SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX,
			"LY",SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY,
			"RX",SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX,
			"RY",SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY,
			"LT",SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT,
			"RT",SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT
		);

		// COMMON DATA TYPES
		auto mult_overloads = sol::overload(
			[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
			[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 * f; },
			[](float f, const glm::vec3& v1) -> glm::vec3 { return f * v1; }
		);
		
		lua.new_usertype<glm::vec3>("vec3",
			sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
			"x", &glm::vec3::x,
			"y", &glm::vec3::y,
			"z", &glm::vec3::z,
			"__add", [](const glm::vec3& l, const glm::vec3& r) { return glm::vec3(l.x + r.x, l.y + r.y, l.z + r.z); },
			"__sub", [](const glm::vec3& l, const glm::vec3& r) { return glm::vec3(l.x - r.x, l.y - r.y, l.z - r.z); },
			sol::meta_function::multiplication, mult_overloads
			);

		lua.new_usertype<glm::vec2>("vec2",
			sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
			"x", &glm::vec2::x,
			"y", &glm::vec2::y,
			"__add", [](const glm::vec2& l, const glm::vec2& r) { return glm::vec2(l.x + r.x, l.y + r.y); },
			"__sub", [](const glm::vec2& l, const glm::vec2& r) { return glm::vec2(l.x - r.x, l.y - r.y); }
			);

		// COMPONENTS
		lua.new_usertype<Body>("RigidBody",
			sol::constructors<Body()>(),
			"velocity", &Body::mVelocity,
			"angularVelocity", &Body::mAngularVelocity,
			"position", &Body::mPosition
		);

		lua.new_usertype<Transform>("Transform",
			sol::constructors<Transform()>(),
			"position", &Transform::mPosition,
			"scale", &Transform::mScale
			);

		lua.new_usertype<Camera>("Camera",
			sol::constructors<Camera()>(),
			"frontDirection", &Camera::mFront,
			"rightDirection", &Camera::mRight,
			"yaw", &Camera::mYaw,
			"pitch", &Camera::mPitch
			);

		lua.new_usertype<Material>("Material",
			sol::constructors<Material()>(),
			"diffuse", &Material::mDiffuseColor
			);

		// GAMEOBJECT
		mGameObjectType = lua.new_usertype<GameObject>("GameObject",
			sol::constructors<GameObject()>(),
			"GetBody", &GameObject::GetComponent<Body>,
			"GetTransform", &GameObject::GetComponent<Transform>,
			"GetMaterial", &GameObject::GetComponent<Material>,
			"GetScript", &GameObject::GetComponent<Script>
			);

		lua.set_function("CreateGameObject", &ResourceManager::LoadGameObjectFromFile, std::ref(ResourceManager::Instance()));

		// PHYSICS
		lua.set_function("ApplyLinearImpulse", &PhysicsManager::ApplyLinearImpulse, std::ref(PhysicsManager::Instance()));
		lua.set_function("ApplyAngularImpulse", &PhysicsManager::ApplyAngularImpulse, std::ref(PhysicsManager::Instance()));

		// AUDIO
		lua.set_function("PlaySFX", &AudioManager::PlayEffect, std::ref(AudioManager::Instance()));

		// INPUT
		lua.set_function("IsKeyPressed", &InputManager::IsKeyPressed, std::ref(InputManager::Instance()));
		lua.set_function("IsKeyTriggered", &InputManager::IsKeyTriggered, std::ref(InputManager::Instance()));
		lua.set_function("IsKeyReleased", &InputManager::IsKeyReleased, std::ref(InputManager::Instance()));
		lua.set_function("GetAxis", &InputManager::GetAxisValue, std::ref(InputManager::Instance()));
		lua.set_function("IsControllerButtonPressed", &InputManager::IsControllerButtonPressed, std::ref(InputManager::Instance()));
		lua.set_function("IsControllerButtonTriggered", &InputManager::IsControllerButtonTriggered, std::ref(InputManager::Instance()));
		lua.set_function("IsControllerButtonReleased", &InputManager::IsControllerButtonReleased, std::ref(InputManager::Instance()));
		lua.set_function("IsControllerTriggerPressed", &InputManager::IsControllerTriggerPressed, std::ref(InputManager::Instance()));
		lua.set_function("IsControllerTriggerTriggered", &InputManager::IsControllerTriggerTriggered, std::ref(InputManager::Instance()));
		lua.set_function("IsControllerTriggerReleased", &InputManager::IsControllerTriggerReleased, std::ref(InputManager::Instance()));


	}

}
