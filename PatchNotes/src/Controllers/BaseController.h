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
		std::unique_ptr<models::BaseModel> model;

	protected:
		virtual json::JSONBuilder collectData(gui_framework::BaseComposite* window) const = 0;

		virtual void sendDataToModel(const json::JSONParser& data) const final;

	public:
		BaseController(std::unique_ptr<models::BaseModel>&& model) noexcept;

		virtual void receiveData(gui_framework::BaseComposite* window) final;

		virtual std::unique_ptr<models::BaseModel>& getModel() final;

		virtual ~BaseController() = default;
	};
}
