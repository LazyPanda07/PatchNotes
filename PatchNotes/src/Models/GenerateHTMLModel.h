#pragma once

#include "BaseModel.h"

#include "pch.h"

#include "BaseComposites/BaseComposite.h"

namespace models
{
	class GenerateHTMLModel : public BaseModel
	{
	private:
		gui_framework::BaseComposite* mainWindow;

	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;;

	public:
		GenerateHTMLModel(gui_framework::BaseComposite* mainWindow);

		~GenerateHTMLModel() = default;
	};
}
