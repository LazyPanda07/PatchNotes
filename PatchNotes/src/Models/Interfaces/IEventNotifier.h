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
			std::vector<std::unique_ptr<views::interfaces::IObserver>> observers;

		public:
			IEventNotifier() = default;

			virtual void addObserver(std::unique_ptr<views::interfaces::IObserver>&& observer) final;

			virtual void removeObserver(views::interfaces::IObserver* observer) final;

			virtual void notify(const json::JSONParser& data) final;

			virtual std::vector<std::unique_ptr<views::interfaces::IObserver>>& getObservers() final;

			virtual ~IEventNotifier() = default;
		};
	}
}
