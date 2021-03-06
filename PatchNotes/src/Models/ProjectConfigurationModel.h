#pragma once

#include "BaseModel.h"

namespace models
{
	class ProjectConfigurationModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		ProjectConfigurationModel() = default;

		~ProjectConfigurationModel() = default;
	};
}
