#include "BaseView.h"

using namespace std;

namespace views
{
	BaseView::BaseView(const shared_ptr<controllers::BaseController>& controller, unique_ptr<gui_framework::BaseComposite>&& window) noexcept :
		controller(controller),
		window(move(window))
	{

	}

	unique_ptr<gui_framework::BaseComposite>& BaseView::getWindow()
	{
		return window;
	}
}
