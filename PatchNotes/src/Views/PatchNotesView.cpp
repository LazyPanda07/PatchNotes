#include "PatchNotesView.h"

#include "Composites/ChildWindow.h"
#include "Components/ComboBoxes/DropDownListComboBox.h"
#include "Components/EditControl.h"
#include "Components/RichEdit.h"
#include "Components/Buttons/Button.h"
#include "Composites/DialogBox.h"
#include "Components/ProgressBars/ProgressBar.h"

#include "Initializer.h"
#include "Controllers/PatchNotesController.h"
#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

#include "Exceptions/ValidationException.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotesUI)

namespace views
{
	gui_framework::BaseComposite* PatchNotesView::createPatchNotesWindow(const unique_ptr<controllers::BaseController>& controller, gui_framework::BaseComponent* parent)
	{
		using namespace gui_framework;

		uint16_t width = parent->getDesiredWidth();
		uint16_t height = parent->getDesiredHeight();

		gui_framework::utility::ComponentSettings settings(0, 0, width - 17, height - 60);
		ChildWindow* patchNotesWindow = new ChildWindow(L"PatchNotesUI", L"PatchNotesUI", settings, parent, "patchNotesUI");

		patchNotesWindow->setAutoResize(true);

		DropDownListComboBox* currentProject = new DropDownListComboBox(L"ProjectNameAndVersion", gui_framework::utility::ComponentSettings(width / 4, 0, width / 2, 20), patchNotesWindow);
		vector<wstring> projects = ::utility::getAvailableProjectsFiles();

		currentProject->setAutoResize(true);

		for (const auto& i : projects)
		{
			currentProject->addValue(i);
		}

		if (projects.size())
		{
			currentProject->setCurrentSelection(0);
		}

		DropDownListComboBox* currentCategory = new DropDownListComboBox(L"ProjectCategory", gui_framework::utility::ComponentSettings(width / 4, 25, width / 2, 20), patchNotesWindow);

		currentCategory->setAutoResize(true);

		if (currentProject->getCurrentSelectionIndex() != -1)
		{
			vector<wstring> categories = ::utility::getAvailableCategories(currentProject->getValue(currentProject->getCurrentSelectionIndex()));

			for (const auto& i : categories)
			{
				currentCategory->addValue(i);
			}

			if (categories.size())
			{
				currentCategory->setCurrentSelection(0);
			}
		}

		EditControl* element = new EditControl(L"Item", width / 4, 50, patchNotesWindow, width / 2);

		element->setAutoResize(true);

		element->setPlaceholder(L"Элемент");

		RichEdit* notes = new RichEdit(L"Notes", gui_framework::utility::ComponentSettings(0, 70, width - 20, height - 170), patchNotesWindow, true);

		notes->setAutoResize(true);

		Button* add = new Button(L"AddNotes", L"Добавить", 0, height - 100, patchNotesWindow, [&controller, patchNotesWindow]()
			{
				try
				{
					controller->receiveData(patchNotesWindow);
				}
				catch (const exceptions::ValidationException& e)
				{
					BaseDialogBox::createMessageBox(e.getMessage(), L"Ошибка", BaseDialogBox::messageBoxType::ok, patchNotesWindow);
				}
			}, 200, 40);

		add->setAutoResize(true);

		ProgressBar* generateHTML = new ProgressBar(L"GenerateHTMLProgressBar", gui_framework::utility::ComponentSettings(200, height - 100, 824, 40), patchNotesWindow);

		generateHTML->setAutoResize(true);

		currentProject->setOnSelectionChange([currentCategory](gui_framework::BaseComboBox& comboBox)
			{
				if (comboBox.getCurrentSelectionIndex() != -1)
				{
					currentCategory->clear();

					vector<wstring> categories = ::utility::getAvailableCategories(comboBox.getValue(comboBox.getCurrentSelectionIndex()));

					for (const auto& i : categories)
					{
						currentCategory->addValue(i);
					}

					if (categories.size())
					{
						currentCategory->setCurrentSelection(0);
					}
				}
			});

		return patchNotesWindow;
	}

	PatchNotesView::PatchNotesView(gui_framework::BaseComponent* parent) :
		BaseView(make_unique<controllers::PatchNotesController>(), PatchNotesView::createPatchNotesWindow(controller, parent))
	{

	}

	void PatchNotesView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.getBool("success");
		string message = data.getString("message");

		if (success)
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
