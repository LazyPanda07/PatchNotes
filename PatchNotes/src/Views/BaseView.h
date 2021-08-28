#pragma once

#include "headers.h"

#include "BaseComposites/BaseComposite.h"

#include "Controllers/BaseController.h"
#include "Interfaces/IObserver.h"

namespace views
{
	class BaseView : public interfaces::IObserver
	{
	protected:
		std::unique_ptr<controllers::BaseController> controller;
		gui_framework::BaseComposite* window;

	public:
		BaseView(std::unique_ptr<controllers::BaseController>&& controller, gui_framework::BaseComposite* window) noexcept;

		virtual void update(const json::JSONParser& data) override = 0;

		virtual gui_framework::BaseComposite* getWindow() final;

		virtual std::unique_ptr<controllers::BaseController>& getController() final;

		virtual void remove() final;

		virtual ~BaseView() = default;
	};
}
