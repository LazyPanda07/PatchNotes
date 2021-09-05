#pragma once

#include "Models/BaseModel.h"

namespace models
{
	class EditElementModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		EditElementModel() = default;

		~EditElementModel() = default;
	};
}
