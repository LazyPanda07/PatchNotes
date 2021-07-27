#include "BaseModel.h"

using namespace std;

namespace models
{
	void BaseModel::updateModel(const json::JSONParser& data)
	{
		json::JSONParser processedData(this->processData(data).build());

		this->notify(processedData);
	}
}
