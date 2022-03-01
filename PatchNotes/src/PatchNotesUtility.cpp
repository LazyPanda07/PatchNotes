#include "PatchNotesUtility.h"

#include <fstream>
#include <map>

#include <Windows.h>
#include <shellapi.h>
#include <tlhelp32.h>

#include "headers.h"
#include "CompositesHeader.h"
#include "Initializer.h"
#include "PatchNotesConstants.h"

using namespace std;

bool isRestartNeeded();

namespace utility
{
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
		using json::utility::jsonObject;

		json::JSONParser projectFile;

		ifstream(pathToProjectFile) >> projectFile;

		for (const auto& i : projectFile)
		{
			if (static_cast<variantTypeEnum>(i->second.index()) == variantTypeEnum::jJSONObject)
			{
				const jsonObject& object = get<jsonObject>(i->second);
				const string& type = get<string>(ranges::find_if(object.data, [](const pair<string, jsonObject::variantType>& value) { return value.first == "type"; })->second);

				if (type == "category")
				{
					jsonObject newObject;

					newObject.data.push_back({ "type"s, "category"s });

					for (const auto& j : object.data)
					{
						if (static_cast<variantTypeEnum>(j.second.index()) == variantTypeEnum::jJSONObject)
						{
							const jsonObject& item = get<jsonObject>(j.second);
							const vector<jsonObject>& notes = get<vector<jsonObject>>(
								ranges::find_if(item.data, [](const pair<string, jsonObject::variantType>& value) { return value.first == "notes"; })->second
								);
							jsonObject newItem;
							vector<jsonObject> newNotes;

							for (const auto& k : notes)
							{
								json::utility::appendArray(get<string>(k.data.back().second), newNotes);
							}

							newItem.data.push_back({ "type"s, "item"s });

							newItem.data.push_back({ "notes"s, move(newNotes) });

							newObject.data.push_back({ j.first, move(newItem) });
						}
					}

					outBuilder.append(i->first, move(newObject));
				}
			}
		}
	}

	vector<wstring> getAvailableProjectsFiles()
	{
		vector<wstring> result;
		multimap<filesystem::file_time_type, wstring, greater<filesystem::file_time_type>> lastTimeModifiedFiles;
		filesystem::directory_iterator it(globals::dataFolder);

		for (const auto& projectFile : it)
		{
			lastTimeModifiedFiles.insert(make_pair(filesystem::last_write_time(projectFile), projectFile.path().stem().wstring()));
		}

		result.reserve(lastTimeModifiedFiles.size());

		for (const auto& [key, value] : lastTimeModifiedFiles)
		{
			result.push_back(value);
		}

		return result;
	}

	vector<wstring> getAvailableCategories(const wstring& projectName)
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
				result.push_back(utility::to_wstring(i->first, CP_UTF8));
			}
		}

		return result;
	}

	vector<wstring> getAvailableElements(const wstring& projectName, const wstring& categoryName)
	{
		vector<wstring> result;
		json::JSONParser parser;
		filesystem::path pathToProject;
		string jsonCategoryName = gui_framework::utility::to_string(categoryName, CP_UTF8);

		pathToProject.append(globals::dataFolder).append(projectName) += (".json");

		ifstream(pathToProject) >> parser;

		for (const auto& i : parser)
		{
			if (i->second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONObject))
			{
				if (i->first == jsonCategoryName)
				{
					const json::utility::jsonObject& category = get<json::utility::jsonObject>(i->second);

					for (const auto& j : category.data)
					{
						if (j.second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONObject))
						{
							result.push_back(utility::to_wstring(j.first, CP_UTF8));
						}
					}

					break;
				}
			}
		}

		return result;
	}

	vector<wstring> getAvailableNotes(const wstring& projectName, const wstring& categoryName, const wstring& elementName)
	{
		vector<wstring> result;
		json::JSONParser parser;
		filesystem::path pathToProject;
		string jsonCategoryName = gui_framework::utility::to_string(categoryName, CP_UTF8);
		string jsonElementName = gui_framework::utility::to_string(elementName, CP_UTF8);

		pathToProject.append(globals::dataFolder).append(projectName) += (".json");

		ifstream(pathToProject) >> parser;

		for (const auto& i : parser)
		{
			if (i->second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONObject))
			{
				if (i->first == jsonCategoryName)
				{
					const json::utility::jsonObject& category = get<json::utility::jsonObject>(i->second);

					for (const auto& j : category.data)
					{
						if (j.second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONObject))
						{
							if (j.first == jsonElementName)
							{
								const json::utility::jsonObject& element = get<json::utility::jsonObject>(j.second);

								for (const auto& k : element.data)
								{
									if (k.second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONArray))
									{
										vector<string> notes = json::utility::JSONArrayWrapper(k.second).getAsStringArray();

										result.reserve(notes.size());

										ranges::for_each(notes, [&result](const string& note) { result.push_back(utility::to_wstring(note, CP_UTF8)); });

										return result;
									}
								}
							}
						}
					}
				}
			}
		}

		return result;
	}

	void initPathToPatchNotes(HINSTANCE hInstance)
	{
		wchar_t data[512] = {};
		DWORD size = GetModuleFileNameW(hInstance, data, 512);

		globals::pathToPatchNotes = data;

		globals::pathToPatchNotes.resize(size);
	}

	void restart()
	{
		while (!isRestartNeeded())
		{
			this_thread::sleep_for(0.5s);
		}

		ShellExecuteW(NULL, L"open", globals::pathToPatchNotes.data(), nullptr, nullptr, SW_SHOWDEFAULT);
	}
}

bool isRestartNeeded()
{
	PROCESSENTRY32W processInfo = {};
	size_t processes = 0;
	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (processesSnapshot == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	processInfo.dwSize = sizeof(processInfo);

	if (!Process32FirstW(processesSnapshot, &processInfo))
	{
		CloseHandle(processesSnapshot);

		return false;
	}

	do
	{
		processes += patch_notes_constants::projectName == processInfo.szExeFile;
	} while (Process32NextW(processesSnapshot, &processInfo));

	CloseHandle(processesSnapshot);

	return processes == 1;
}
