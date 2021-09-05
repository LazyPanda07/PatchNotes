#pragma once

#include "Views/BaseView.h"

namespace views
{
	class EditNoteView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createEditNoteDialog(const std::unique_ptr<controllers::BaseController>& controller);

	public:
		EditNoteView();

		void update(const json::JSONParser& data) override;

		~EditNoteView() = default;
	};
}
