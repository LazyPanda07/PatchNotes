#pragma once

#include "Models/BaseModel.h"

namespace models
{
	class EditProjectConfigurationModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		EditProjectConfigurationModel() = default;

		~EditProjectConfigurationModel() = default;
	};
}
