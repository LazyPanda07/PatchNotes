#pragma once

#include "pch.h"

#include "BaseComposites/BaseComposite.h"

#include "Controllers/BaseController.h"
#include "Interfaces/IObserver.h"

namespace views
{
	class BaseView : public interfaces::IObserver
	{
	protected:
		std::shared_ptr<controllers::BaseController> controller;
		std::unique_ptr<gui_framework::BaseComposite> window;

	public:
		BaseView(const std::shared_ptr<controllers::BaseController>& controller, std::unique_ptr<gui_framework::BaseComposite>&& window) noexcept;

		virtual void update(const json::JSONParser& data) override = 0;

		virtual ~BaseView() = default;
	};
}
