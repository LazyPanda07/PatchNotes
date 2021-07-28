#include "PatchNotesController.h"

#include "Models/PatchNotesModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder PatchNotesController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(utility::getCodepage());



		return builder;
	}

	PatchNotesController::PatchNotesController() :
		BaseController(make_shared<models::PatchNotesModel>())
	{

	}
}
