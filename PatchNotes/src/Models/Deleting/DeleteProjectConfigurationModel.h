#pragma once

#include "Models/BaseModel.h"

namespace models
{
	class DeleteProjectConfigurationModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		DeleteProjectConfigurationModel() = default;

		~DeleteProjectConfigurationModel() = default;
	};
}
