#pragma once

#include "Models/BaseModel.h"

namespace models
{
	class EditCategoryModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		EditCategoryModel() = default;

		~EditCategoryModel() = default;
	};
}
