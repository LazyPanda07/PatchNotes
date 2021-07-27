#pragma once

#include <memory>

#include "Controllers/BaseController.h"
#include "Interfaces/IObserver.h"

namespace views
{
	class BaseView : public interfaces::IObserver
	{
	protected:
		std::shared_ptr<controllers::BaseController> controller;

	public:
		BaseView(const std::shared_ptr<controllers::BaseController>& controller) noexcept;

		virtual void update(const json::JSONParser& data) override = 0;

		virtual ~BaseView() = default;
	};
}
