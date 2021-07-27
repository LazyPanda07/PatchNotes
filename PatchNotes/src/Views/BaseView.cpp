#include "BaseView.h"

using namespace std;

namespace views
{
	BaseView::BaseView(const shared_ptr<controllers::BaseController>& controller) noexcept :
		controller(controller)
	{

	}
}
