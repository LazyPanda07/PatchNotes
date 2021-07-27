#include "BaseController.h"

using namespace std;

namespace controllers
{
	void BaseController::sendDataToModel(const json::JSONParser& data) const
	{
		model->updateModel(data);
	}

	BaseController::BaseController(const shared_ptr<models::BaseModel>& model) noexcept :
		model(model)
	{

	}

	void BaseController::receiveData(gui_framework::BaseComposite* window)
	{
		json::JSONParser data(this->collectData(window).build());

		this->sendDataToModel(data);
	}

	shared_ptr<models::BaseModel>& BaseController::getModel()
	{
		return model;
	}
}
