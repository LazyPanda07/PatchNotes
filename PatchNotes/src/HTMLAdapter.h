#pragma once

#include "JSONParser.h"

class HTMLAdapter
{
private:
	std::string html;

private:
	void addPageInformation(const std::string& projectName, const std::string& version);

	void addProjectNameAndVersion(const std::string& projectName, const std::string& version);

	void addCategory(const std::string& category);

	void addItem(const std::string& item, const std::vector<std::string>& notes);

	void addFooterInformation(const std::string& information = "");

public:
	HTMLAdapter(const json::JSONParser& jsonSchema);

	std::string& getHTML();

	~HTMLAdapter() = default;
};
