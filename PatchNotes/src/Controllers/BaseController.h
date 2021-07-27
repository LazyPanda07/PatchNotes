#pragma once

#include <memory>

#include "JSONParser.h"

#include "Models/BaseModel.h"

namespace controllers
{
	class BaseController
	{
	protected:
		std::shared_ptr<models::BaseModel> model;

	public:
		BaseController(const std::shared_ptr<models::BaseModel>& model) noexcept;

		virtual void sendDataToModel(const json::JSONParser& data) const final;

		virtual ~BaseController() = default;
	};
}
