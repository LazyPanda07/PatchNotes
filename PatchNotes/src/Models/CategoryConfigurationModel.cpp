#include "CategoryConfigurationModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder CategoryConfigurationModel::processData(const json::JSONParser& data)
	{
		json::JSONBuilder builder(utility::getCodepage());
		const string& projectFile = data.get<string>("projectFile");
		const string& categoryName = data.get<string>("category");

		 

		return builder;
	}
}
