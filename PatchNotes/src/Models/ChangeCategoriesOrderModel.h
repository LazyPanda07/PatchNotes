#pragma once

#include "BaseModel.h"

namespace models
{
	class ChangeCategoriesOrderModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		ChangeCategoriesOrderModel() = default;

		~ChangeCategoriesOrderModel() = default;
	};
}
