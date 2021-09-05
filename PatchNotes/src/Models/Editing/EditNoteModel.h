#pragma once

#include "Models/BaseModel.h"

namespace models
{
	class EditNoteModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		EditNoteModel() = default;

		~EditNoteModel() = default;
	};
}
