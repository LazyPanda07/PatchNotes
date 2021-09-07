#pragma once

#include "BaseModel.h"

#include "headers.h"

#include "BaseComposites/BaseComposite.h"

namespace models
{
	class GenerateHTMLModel : public BaseModel
	{
	private:
		gui_framework::BaseComposite* mainWindow;

	private:
		static void generateIndexHTML(const std::filesystem::path& outFolder, const std::string& projectName);

		static std::string generatePatchLink(const std::string& projectName);

		static std::string generateEmptyPatchLink();

	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

		void updateIndex(const std::filesystem::path& outFolder, const std::string& projectFileName);

	public:
		GenerateHTMLModel(gui_framework::BaseComposite* mainWindow);

		~GenerateHTMLModel() = default;
	};
}
