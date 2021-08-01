#include "BaseView.h"

using namespace std;

namespace views
{
	BaseView::BaseView(unique_ptr<controllers::BaseController>&& controller, gui_framework::BaseComposite* window) noexcept :
		controller(move(controller)),
		window(window)
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

	void BaseView::remove()
	{
		dynamic_cast<gui_framework::BaseComposite*>(window->getParent())->removeChild(window);
	}
}
