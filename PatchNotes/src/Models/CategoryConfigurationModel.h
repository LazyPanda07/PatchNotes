#pragma once

#include "BaseModel.h"

namespace models
{
	class CategoryConfigurationModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		CategoryConfigurationModel() = default;

		~CategoryConfigurationModel() = default;
	};
}
