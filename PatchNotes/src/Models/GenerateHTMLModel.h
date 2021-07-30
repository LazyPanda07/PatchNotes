#pragma once

#include "BaseModel.h"

namespace models
{
	class GenerateHTMLModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;;

	public:
		GenerateHTMLModel() = default;

		~GenerateHTMLModel() = default;
	};
}
