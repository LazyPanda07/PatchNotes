#pragma once

#include "JSONParser.h"

namespace views
{
	namespace interfaces
	{
		class IObserver
		{
		public:
			IObserver() = default;

			virtual void update(const json::JSONParser& data) = 0;

			virtual ~IObserver() = default;
		};
	}
}
