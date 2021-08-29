#pragma once

#include "BaseModel.h"

namespace models
{
	class DeleteProjectConfigurationModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		DeleteProjectConfigurationModel();

		~DeleteProjectConfigurationModel() = default;
	};
}
