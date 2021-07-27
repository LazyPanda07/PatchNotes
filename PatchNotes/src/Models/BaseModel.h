#pragma once

#include <memory>

#include "JSONBuilder.h"

#include "Interfaces/IEventNotifier.h"

namespace models
{
	class BaseModel : public interfaces::IEventNotifier
	{
	protected:
		virtual json::JSONBuilder processData(const json::JSONParser& data) = 0;

	public:
		BaseModel() = default;

		virtual void updateModel(const json::JSONParser& data) final;

		virtual ~BaseModel() = default;
	};
}
