#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")


using std::string;
using std::wstring;
using std::vector;
using std::getline;

#define TIMEFRONT_MIN	5
#define TIMEFRONT_MAX	60
#define TIMEBACK_MIN	5
#define TIMEBACK_MAX	300
#define FONTSIZE_MIN	100
#define FONTSIZE_MAX	200
#define HSIZE_MIN		0
#define HSIZE_MAX		8

enum class DIF { COMMON, BASIC, ADVANCED, ALL };
enum class DIFG { I, II, III, IV, V, VI, VII, ALL };

class Database
{
public:
	Database(void* param);
	~Database();

	Database& load_settings();
	Database& save_settings();
	Database& load_database();
	Database& init_indexes();
	Database& next_index();
	Database& previous_index();

	string get_str_type();
	string get_front();
	string get_back();
	void play_sound();
	int get_index();
private:
	void clear();
	int check(int input, int min, int max);
	DIF convert_str_dif(string dif);
	DIFG convert_str_group(string group);
public:
	DIF dif;
	DIFG group;
private:
	void* param;
	int index;
	int* indexes;
	vector<string> front;
	vector<string> back;
};
