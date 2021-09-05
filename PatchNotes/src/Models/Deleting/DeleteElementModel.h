#pragma once

#include "Models/BaseModel.h"

namespace models
{
	class DeleteElementModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		DeleteElementModel() = default;

		~DeleteElementModel() = default;
	};
}
