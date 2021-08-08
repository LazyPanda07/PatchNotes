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
		json::JSONBuilder processData(const json::JSONParser& data) override;

		void updateIndex(const std::filesystem::path& outFolder, const std::string& projectFileName);

	public:
		GenerateHTMLModel(gui_framework::BaseComposite* mainWindow);

		~GenerateHTMLModel() = default;
	};
}
