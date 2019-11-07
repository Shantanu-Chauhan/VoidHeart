#pragma once
#include "Component.h"

namespace Hollow
{
	class FrameBuffer;

	enum LightType
	{
		GLOBAL,
		LOCAL,
		LIGHT_NUM
	};

	class Light : public Component
	{
		REGISTERCOMPONENT(Light);
	public:
		HOLLOW_API void Init();
		HOLLOW_API void Serialize(rapidjson::Value::Object data);
		HOLLOW_API void DeSerialize(rapidjson::Writer<rapidjson::StringBuffer>& writer);
		HOLLOW_API void Clear();
		HOLLOW_API void DebugDisplay();

	public:
		glm::vec3 mPosition; // Position of light or offset from the objects center position ?
		float mRadius;
		glm::vec3 mColor;
		LightType mType;

		// Shadow information
		bool mCastShadow;
		FrameBuffer* mpShadowMap;
		glm::vec2 mShadowMapSize;
		float mShadowMapNearPlane;
		float mShadowMapFarPlane;

		// Moment shadow map information
		unsigned int mBlurDistance;
		float mAlpha;
		float mMD; // Hopefully can find a good constant or formula to get this
	};
}