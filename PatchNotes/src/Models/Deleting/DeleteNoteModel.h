#pragma once

#include "Models/BaseModel.h"

namespace models
{
	class DeleteNoteModel : public BaseModel
	{
	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		DeleteNoteModel() = default;

		~DeleteNoteModel() = default;
	};
}
