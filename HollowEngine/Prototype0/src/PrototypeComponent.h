#pragma once
#include "Hollow.h"
#include "Hollow/Components/Component.h"

class PrototypeComponent : public Hollow::Component
{
	REGISTERCOMPONENT(PrototypeComponent,"PrototypeComponent");
public:
	void Init();
	void Serialize(rapidjson::Value::Object data) {}
	void Clear();
	void DebugDisplay();

};