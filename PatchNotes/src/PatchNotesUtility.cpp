#include "PatchNotesUtility.h"

#include <fstream>

#include "GUIFramework.h"

#include "PatchNotesConstants.h"

using namespace std;

namespace utility
{
	uint32_t getCodepage()
	{
		return static_cast<uint32_t>(gui_framework::GUIFramework::get().getJSONSettings().getUnsignedInt("codepage"));
	}

	pair<int, int> getScreenCenter(uint16_t width, uint16_t height)
	{
		uint16_t screenWidth = static_cast<uint16_t>(GetSystemMetrics(SM_CXSCREEN));
		uint16_t screenHeight = static_cast<uint16_t>(GetSystemMetrics(SM_CYSCREEN));

		return { (screenWidth - width) / 2, (screenHeight - height) / 2 };
	}

	wstring to_wstring(const string& stringToConvert, uint32_t codepage)
	{
		wstring result;

		int size = MultiByteToWideChar
		(
			codepage,
			NULL,
			stringToConvert.data(),
			-1,
			nullptr,
			NULL
		);

		if (!size)
		{
			throw json::exceptions::WrongEncodingException();
		}

		result.resize(static_cast<size_t>(size) - 1);

		if (!MultiByteToWideChar
		(
			codepage,
			NULL,
			stringToConvert.data(),
			-1,
			result.data(),
			size
		))
		{
			throw json::exceptions::WrongEncodingException();
		}

		return result;
	}
	
	void copyJSON(const filesystem::path& pathToProjectFile, json::JSONBuilder& outBuilder)
	{
		using json::utility::variantTypeEnum;
		using json::utility::objectSmartPointer;
		using json::utility::jsonObject;

		json::JSONParser projectFile;

		ifstream(pathToProjectFile) >> projectFile;

		for (const auto& i : projectFile)
		{
			if (static_cast<variantTypeEnum>(i->second.index()) == variantTypeEnum::jJSONObject)
			{
				const objectSmartPointer<jsonObject>& object = get<objectSmartPointer<jsonObject>>(i->second);
				const string& type = get<string>(find_if(object->data.begin(), object->data.end(), [](const pair<string, jsonObject::variantType>& value) { return value.first == "type"; })->second);

				if (type == "category")
				{
					objectSmartPointer<jsonObject> newObject = json::utility::make_object<jsonObject>();

					newObject->data.push_back({ "type"s, "category"s });

					for (const auto& j : object->data)
					{
						if (static_cast<variantTypeEnum>(j.second.index()) == variantTypeEnum::jJSONObject)
						{
							const objectSmartPointer<jsonObject>& item = get<objectSmartPointer<jsonObject>>(j.second);
							const vector<objectSmartPointer<jsonObject>>& notes = get<vector<objectSmartPointer<jsonObject>>>(
								find_if(item->data.begin(), item->data.end(), [](const pair<string, jsonObject::variantType>& value) { return value.first == "notes"; })->second
								);
							objectSmartPointer<jsonObject> newItem = json::utility::make_object<jsonObject>();
							vector<objectSmartPointer<jsonObject>> newNotes;

							for (const auto& k : notes)
							{
								json::utility::appendArray(get<string>(k->data.back().second), newNotes);
							}

							newItem->data.push_back({ "type"s, "item"s });

							newItem->data.push_back({ "notes"s, move(newNotes) });

							newObject->data.push_back({ j.first, move(newItem) });
						}
					}

					outBuilder.append(i->first, move(newObject));
				}
			}
		}
	}

	vector<wstring> getProjectCategories(const wstring& projectName)
	{
		vector<wstring> result;
		json::JSONParser parser;
		filesystem::path pathToProject;

		pathToProject.append(globals::dataFolder).append(projectName) += (".json");

		ifstream(pathToProject) >> parser;

		for (const auto& i : parser)
		{
			if (i->second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONObject))
			{
				const json::utility::objectSmartPointer<json::utility::jsonObject>& object = get<json::utility::objectSmartPointer<json::utility::jsonObject>>(i->second);
				const string& type = get<string>(
					find_if(object->data.begin(), object->data.end(), [](const pair<string, json::utility::jsonObject::variantType>& value) { return value.first == "type"; })->second
					);

				if (type == "category")
				{
					result.push_back(utility::to_wstring(i->first, CP_UTF8));
				}
			}
		}

		return result;
	}

	vector<wstring> getAvailableProjectsFiles()
	{
		vector<wstring> result;
		map<filesystem::file_time_type, wstring> lastTimeModifiedFiles;

		filesystem::directory_iterator it(globals::dataFolder);

		for (const auto& projectFile : it)
		{
			lastTimeModifiedFiles[filesystem::last_write_time(projectFile)] = projectFile.path().stem().wstring();
		}

		result.reserve(lastTimeModifiedFiles.size());

		for_each(lastTimeModifiedFiles.rbegin(), lastTimeModifiedFiles.rend(), [&result](const pair<filesystem::file_time_type, wstring>& value) { result.push_back(value.second); });

		return result;
	}
}
