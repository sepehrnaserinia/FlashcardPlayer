#include "pch.h"
#include "Database.h"
#include "GREDoc.h"


Database::Database(void* param)
{
	srand(time(NULL));
	this->param = param;
	dif = DIF::ALL;
	group = DIFG::ALL;
	load_settings();
	load_database();
}
Database::~Database()
{
	save_settings();
}

Database& Database::load_settings()
{
	std::ifstream file;
	file.open("Database/Database.txt");
	if (!file.is_open())
		return *this;

	GREDoc* pDoc = (GREDoc*)param;
	string str;
	getline(file, str, ':');
	getline(file, str);
	if (str.find('-') != -1)
	{
		dif = convert_str_dif(str.substr(0, str.find('-')).c_str());
		group = convert_str_group(str.substr(str.find('-') + 1).c_str());
	}
	getline(file, str); pDoc->audio = str.substr(str.find(':') + 1) == "true";
	getline(file, str); pDoc->shuffle = str.substr(str.find(':') + 1) == "true";
	getline(file, str); pDoc->always_on_top = str.substr(str.find(':') + 1) == "true";
	getline(file, str); pDoc->time_front = check(atoi(str.substr(str.find(':') + 1).c_str()), TIMEFRONT_MIN, TIMEFRONT_MAX);
	getline(file, str); pDoc->time_back = check(atoi(str.substr(str.find(':') + 1).c_str()), TIMEBACK_MIN, TIMEBACK_MAX);
	getline(file, str); pDoc->font_size = check(atoi(str.substr(str.find(':') + 1).c_str()), FONTSIZE_MIN, FONTSIZE_MAX);
	getline(file, str); pDoc->horizontal_size = check(atoi(str.substr(str.find(':') + 1).c_str()), HSIZE_MIN, HSIZE_MAX);
	file.close();
	return *this;
}
Database& Database::save_settings()
{
	GREDoc* pDoc = (GREDoc*)param;
	std::ofstream file;
	file.open("Database/Database.txt");
	file << "Database:" << get_str_type() << std::endl;
	file << "Audio:" << (pDoc->audio ? "true": "false") << std::endl;
	file << "Shuffle:" << (pDoc->shuffle ? "true" : "false") << std::endl;
	file << "AlwaysOnTop:" << (pDoc->always_on_top ? "true": "false") << std::endl;
	file << "SpeedFront:" << pDoc->time_front << std::endl;
	file << "SpeedBack:" << pDoc->time_back << std::endl;
	file << "FontSize:" << pDoc->font_size << std::endl;
	file << "HorizontalSize:" << pDoc->horizontal_size << std::endl;
	file.close();
	return *this;
}
Database& Database::load_database()
{
	clear();
	string strF, strB;
	std::ifstream file;
	file.open("Database/" + get_str_type() + ".txt");
	if (!file.is_open())
		return *this;

	while (!file.eof())
	{
		getline(file, strF, '#');
		getline(file, strB);
		for (int i = 0; i < strB.size(); i++)
			if (strB[i] == '@')
				strB[i] = '\n';
		front.push_back(strF);
		back.push_back(strB);
	}
	if (front.size() == 0)
		return *this;

	indexes = new int[front.size()];
	init_indexes();
	return *this;
}
Database& Database::init_indexes()
{
	for (int i = 0; i < front.size(); i++)
		indexes[i] = i;
	GREDoc* pDoc = (GREDoc*)param;
	if (pDoc->shuffle)
		for (int i = 0; i < front.size(); i++)
		{
			int j = rand() % front.size();
			int temp = indexes[i];
			indexes[i] = indexes[j];
			indexes[j] = temp;
		}
	return *this;
}
Database& Database::next_index()
{
	index += 1;
	if (index >= front.size())
		index = 0;
	return *this;
}
Database& Database::previous_index()
{
	index -= 1;
	if (index <= -1)
		index = front.size() - 1;
	return *this;
}

std::string Database::get_str_type()
{
	if (dif == DIF::ALL)
		return "All";
	std::string type1, type2;
	switch (dif)
	{
	case DIF::COMMON:
		type1 = "Common";
		break;
	case DIF::BASIC:
		type1 = "Basic";
		break;
	case DIF::ADVANCED:
		type1 = "Advanced";
		break;
	}
	switch (group)
	{
	case DIFG::I:
		type2 = "I";
		break;
	case DIFG::II:
		type2 = "II";
		break;
	case DIFG::III:
		type2 = "III";
		break;
	case DIFG::IV:
		type2 = "IV";
		break;
	case DIFG::V:
		type2 = "V";
		break;
	case DIFG::VI:
		type2 = "VI";
		break;
	case DIFG::VII:
		type2 = "VII";
		break;
	case DIFG::ALL:
		type2 = "All";
		break;
	}
	return type1 + "-" + type2;
}
string Database::get_front()
{
	if (front.size() == 0)
		return "";
	return front.at(indexes[index]);
}
string Database::get_back()
{
	if (front.size() == 0)
		return "";
	return back.at(indexes[index]);
}
void Database::play_sound()
{
	if (front.size() == 0)
		return;
	string str = front.at(indexes[index]);
	wstring sound(L"Audio/");
	sound.append(wstring(str.begin(), str.end()));
	sound.append(L".mp3");
	PlaySound(sound.c_str(), NULL, SND_FILENAME);
}
int Database::get_index()
{
	return index;
}

void Database::clear()
{
	this->index = 0;
	this->front.clear();
	this->back.clear();
	if (this->indexes != nullptr)
		delete[] indexes;
	this->indexes = nullptr;
}
int Database::check(int input, int min, int max)
{
	if (input >= min && input <= max)
		return input;
	return min;
}
DIF Database::convert_str_dif(std::string dif)
{
	if (dif == "Common")
		return DIF::COMMON;
	if (dif == "Basic")
		return DIF::BASIC;
	if (dif == "Advanced")
		return DIF::ADVANCED;
	return DIF::COMMON;
}
DIFG Database::convert_str_group(std::string group)
{
	if (group == "I")
		return DIFG::I;
	if (group == "II")
		return DIFG::II;
	if (group == "III")
		return DIFG::III;
	if (group == "IV")
		return DIFG::IV;
	if (group == "V")
		return DIFG::V;
	if (group == "VI")
		return DIFG::VI;
	if (group == "VII")
		return DIFG::VII;
	if (group == "All")
		return DIFG::ALL;
	return DIFG::I;
}
