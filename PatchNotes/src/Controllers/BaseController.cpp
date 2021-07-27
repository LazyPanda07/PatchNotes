#include "BaseController.h"

using namespace std;

namespace controllers
{
	BaseController::BaseController(const shared_ptr<models::BaseModel>& model) noexcept :
		model(model)
	{

	}

	void BaseController::sendDataToModel(const json::JSONParser& data) const
	{
		model->updateModel(data);
	}
}
