#pragma once

#include "BaseModel.h"

namespace models
{
	class CategoryModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		CategoryModel() = default;

		~CategoryModel() = default;
	};
}
