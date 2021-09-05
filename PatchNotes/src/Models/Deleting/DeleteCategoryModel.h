#pragma once

#include "Models/BaseModel.h"

namespace models
{
	class DeleteCategoryModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		DeleteCategoryModel() = default;

		~DeleteCategoryModel() = default;
	};
}
