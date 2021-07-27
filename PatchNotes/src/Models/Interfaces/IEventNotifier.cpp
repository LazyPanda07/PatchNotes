#include "IEventNotifier.h"

#include <algorithm>

using namespace std;

namespace models
{
	namespace interfaces
	{
		void IEventNotifier::addObserver(const shared_ptr<views::interfaces::IObserver>& observer)
		{
			observers.emplace_back(observer);
		}

		void IEventNotifier::removeObserver(const shared_ptr<views::interfaces::IObserver>& observer)
		{
			erase(observers, observer);
		}

		void IEventNotifier::notify(const json::JSONParser& data)
		{
			for_each(observers.begin(), observers.end(), [&data](shared_ptr<views::interfaces::IObserver>& observer) { observer->update(data); });
		}
	}
}
