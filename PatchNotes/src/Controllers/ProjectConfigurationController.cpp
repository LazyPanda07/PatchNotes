#include "ProjectConfigurationController.h"

#include "Models/ProjectConfigurationModel.h"

using namespace std;

namespace controllers
{
	ProjectConfigurationController::ProjectConfigurationController() :
		BaseController(shared_ptr<models::BaseModel>(new models::ProjectConfigurationModel()))
	{

	}
}
