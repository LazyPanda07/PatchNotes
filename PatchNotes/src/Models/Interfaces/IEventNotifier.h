#pragma once

#include <vector>

#include "Views/Interfaces/IObserver.h"

namespace models
{
	namespace interfaces
	{
		class IEventNotifier
		{
		private:
			std::vector<std::shared_ptr<views::interfaces::IObserver>> observers;

		public:
			IEventNotifier() = default;

			virtual void addObserver(const std::shared_ptr<views::interfaces::IObserver>& observer) final;

			virtual void removeObserver(const std::shared_ptr<views::interfaces::IObserver>& observer) final;

			virtual void notify(const json::JSONParser& data) final;

			virtual ~IEventNotifier() = default;
		};
	}
}
