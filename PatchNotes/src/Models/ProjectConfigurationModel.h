#pragma once

#include "BaseModel.h"

namespace models
{
	class ProjectConfigurationModel : public BaseModel
	{
	public:
		ProjectConfigurationModel(const std::shared_ptr<views::interfaces::IObserver>& projectConfigurationView);

		json::JSONBuilder processData(const json::JSONParser& data) override;

		~ProjectConfigurationModel() = default;
	};
}
