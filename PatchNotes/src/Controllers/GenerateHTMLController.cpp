#include "GenerateHTMLController.h"

#include "Models/GenerateHTMLModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder GenerateHTMLController ::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(utility::getCodepage());



		return builder;
	}

	GenerateHTMLController::GenerateHTMLController() :
		BaseController(make_shared<models::GenerateHTMLModel>())
	{

	}
}
