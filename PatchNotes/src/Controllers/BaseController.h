#pragma once

#include "pch.h"

#include "JSONParser.h"
#include "BaseComposites/BaseComposite.h"

#include "Models/BaseModel.h"

namespace controllers
{
	class BaseController
	{
	protected:
		std::shared_ptr<models::BaseModel> model;

	protected:
		virtual json::JSONBuilder collectData(gui_framework::BaseComposite* window) const = 0;

		virtual void sendDataToModel(const json::JSONParser& data) const final;

	public:
		BaseController(const std::shared_ptr<models::BaseModel>& model) noexcept;

		virtual void receiveData(gui_framework::BaseComposite* window) final;

		virtual std::shared_ptr<models::BaseModel>& getModel() final;

		virtual ~BaseController() = default;
	};
}
