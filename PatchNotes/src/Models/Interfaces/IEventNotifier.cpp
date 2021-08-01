#include "IEventNotifier.h"

#include <algorithm>

using namespace std;

namespace models
{
	namespace interfaces
	{
		void IEventNotifier::addObserver(views::interfaces::IObserver* observer)
		{
			observers.push_back(observer);
		}

		void IEventNotifier::removeObserver(views::interfaces::IObserver* observer)
		{
			erase_if(observers, [&observer](views::interfaces::IObserver* ptr) { return observer == ptr; });
		}

		void IEventNotifier::notify(const json::JSONParser& data)
		{
			for_each(observers.begin(), observers.end(), [&data](views::interfaces::IObserver* observer) { observer->update(data); });
		}

		vector<views::interfaces::IObserver*>& IEventNotifier::getObservers()
		{
			return observers;
		}
	}
}
