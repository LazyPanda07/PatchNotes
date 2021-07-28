#pragma once

#include "BaseModel.h"

namespace models
{
	class PatchNotesModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		PatchNotesModel() = default;

		~PatchNotesModel() = default;
	};
}
