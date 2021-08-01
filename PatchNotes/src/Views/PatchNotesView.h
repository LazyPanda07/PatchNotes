#pragma once

#include "BaseView.h"
#include "Controllers/BaseController.h"

namespace views
{
	class PatchNotesView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createPatchNotesWindow(const std::unique_ptr<controllers::BaseController>& controller, gui_framework::BaseComponent* parent);

	private:
		static std::vector<std::wstring> getAvailableProjectsFiles();

		static std::vector<std::wstring> getProjectCategories(const std::wstring& projectName);

	public:
		PatchNotesView(gui_framework::BaseComponent* parent);

		void update(const json::JSONParser& data) override;

		PatchNotesView() = default;
	};
}
