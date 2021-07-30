#include "GenerateHTMLModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "HTMLAdapter.h"

using namespace std;

namespace models
{
	json::JSONBuilder GenerateHTMLModel::processData(const json::JSONParser& data)
	{
		json::JSONBuilder builder(utility::getCodepage());

		return builder;
	}
}
