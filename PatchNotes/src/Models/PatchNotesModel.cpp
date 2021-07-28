#include "PatchNotesModel.h"

#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	json::JSONBuilder PatchNotesModel::processData(const json::JSONParser& data)
	{
		json::JSONBuilder builder(utility::getCodepage());

		return builder;
	}
}
