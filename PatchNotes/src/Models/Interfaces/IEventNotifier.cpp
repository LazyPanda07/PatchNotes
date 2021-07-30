#include "IEventNotifier.h"

#include <algorithm>

using namespace std;

namespace models
{
	namespace interfaces
	{
		void IEventNotifier::addObserver(unique_ptr<views::interfaces::IObserver>&& observer)
		{
			observers.push_back(move(observer));
		}

		void IEventNotifier::removeObserver(views::interfaces::IObserver* observer)
		{
			erase_if(observers, [&observer](const unique_ptr<views::interfaces::IObserver>& ptr) { return observer == ptr.get(); });
		}

		void IEventNotifier::notify(const json::JSONParser& data)
		{
			for_each(observers.begin(), observers.end(), [&data](unique_ptr<views::interfaces::IObserver>& observer) { observer->update(data); });
		}

		vector<unique_ptr<views::interfaces::IObserver>>& IEventNotifier::getObservers()
		{
			return observers;
		}
	}
}
