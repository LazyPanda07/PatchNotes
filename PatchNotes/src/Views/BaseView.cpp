#include "BaseView.h"

using namespace std;

namespace views
{
	BaseView::BaseView(const shared_ptr<controllers::BaseController>& controller, gui_framework::BaseComposite* window, bool clean) noexcept :
		controller(controller),
		window(window),
		clean(clean)
	{

	}

	gui_framework::BaseComposite* BaseView::getWindow()
	{
		return window;
	}

	BaseView::~BaseView()
	{
		if (clean)
		{
			delete window;
		}
	}
}
