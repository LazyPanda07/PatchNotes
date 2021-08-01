#include "BaseView.h"

using namespace std;

namespace views
{
	BaseView::BaseView(unique_ptr<controllers::BaseController>&& controller, gui_framework::BaseComposite* window, bool clean) noexcept :
		controller(move(controller)),
		window(window),
		clean(clean)
	{
		this->controller->getModel()->addObserver(this);
	}

	gui_framework::BaseComposite* BaseView::getWindow()
	{
		return window;
	}

	unique_ptr<controllers::BaseController>& BaseView::getController()
	{
		return controller;
	}

	BaseView::~BaseView()
	{
		if (clean)
		{
			delete window;
		}
	}
}
