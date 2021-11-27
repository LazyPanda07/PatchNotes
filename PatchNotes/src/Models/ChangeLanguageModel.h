#pragma once

#include "BaseModel.h"

#include "Utility/Holders/WindowHolder.h"

namespace models
{
	class ChangeLanguageModel : public BaseModel
	{
	private:
		std::unique_ptr<gui_framework::WindowHolder>& mainWindow;

	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

		void changeLanguage(const std::string& changeTo);

	public:
		ChangeLanguageModel(std::unique_ptr<gui_framework::WindowHolder>& mainWindow);

		~ChangeLanguageModel() = default;
	};
}
