#include "EditNoteController.h"

#include "Models/Editing/EditNoteModel.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditNoteController::collectData(gui_framework::BaseComposite* window) const
	{
		return json::JSONBuilder(1251);
	}

	EditNoteController::EditNoteController() :
		BaseController(make_unique<models::EditNoteModel>())
	{

	}
}
