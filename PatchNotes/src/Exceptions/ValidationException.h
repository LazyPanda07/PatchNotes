#pragma once

#include <stdexcept>

namespace exceptions
{
	class ValidationException : public std::runtime_error
	{
	public:
		ValidationException(const std::wstring& message);

		std::wstring getMessage() const;

		~ValidationException() = default;
	};
}
