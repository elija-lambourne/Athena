#pragma once
#include <iostream>

class pass_entry
{
public:
	int id;
	static int s_next_id;
	std::string source;
	std::string password;
	pass_entry(const std::string& password,const std::string& source);
};

