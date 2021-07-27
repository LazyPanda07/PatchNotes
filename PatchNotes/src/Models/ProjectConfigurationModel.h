#pragma once

#include "BaseModel.h"

namespace models
{
	class ProjectConfigurationModel : public BaseModel
	{
	public:
		ProjectConfigurationModel() = default;

		json::JSONBuilder processData(const json::JSONParser& data) override;

		~ProjectConfigurationModel() = default;
	};
}
