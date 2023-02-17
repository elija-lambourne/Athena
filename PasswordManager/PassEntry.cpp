#include "PassEntry.h"

//Public
 int pass_entry::s_next_id = 0;

pass_entry::pass_entry(const std::string& password, const std::string& source)
{
	this->password = password;
	this->source = source;
	this->id = s_next_id++;
}
