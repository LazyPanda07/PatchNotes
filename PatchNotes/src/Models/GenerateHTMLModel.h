#pragma once

#include "BaseModel.h"

#include "pch.h"

#include "Components/ProgressBars/ProgressBar.h"

namespace models
{
	class GenerateHTMLModel : public BaseModel
	{
	private:
		gui_framework::ProgressBar* updateProgressBar;

	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;;

	public:
		GenerateHTMLModel(gui_framework::ProgressBar* updateProgressBar);

		~GenerateHTMLModel() = default;
	};
}
