#include "EditElementView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Editing/EditElementController.h"
#include "PatchNotesUtility.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(editElement)

namespace views
{
	gui_framework::BaseComposite* EditElementView::createEditElementDialog(const std::unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"EditElement", L"Редактирование конфигурации", x, y, "editElement");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> configurationToEdit(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newElementName(L"Новое название конфигурации(это поле может быть пустым)");
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newElementVersion(L"Новая версия конфигурации(это поле может быть пустым)");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(L"Изменить", []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"ProjectsToEdit", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, configurationToEdit).
			addComponent<gui_framework::EditControl>(L"NewElementName", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, newElementName).
			addComponent<gui_framework::EditControl>(L"NewElementVersion", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, newElementVersion).
			addComponent<gui_framework::Button>(L"ConfirmEditElement", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmEditElement"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"ProjectsToEdit"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				controller->receiveData(result);
			});

		result->show();

		return result;
	}

	EditElementView::EditElementView() :
		BaseView(make_unique<controllers::EditElementController>(), EditElementView::createEditElementDialog(controller))
	{

	}

	void EditElementView::update(const json::JSONParser& data)
	{

	}
}
