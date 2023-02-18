#pragma once
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "PassEntry.h"

//! This is a singleton
class db_manager
{
public:
	static db_manager* get_instance(const std::string& db_path);
	
	db_manager(const std::string& db_path);
	bool store_entry(const pass_entry& entry) const;
	std::vector<pass_entry> search_by_src(const std::string& src) const;
	std::vector<pass_entry> get_all() const;
	bool start_con();
	bool terminate_con(); //! db_ will be changed
	~db_manager();
private:
	static db_manager* instance_ = nullptr;
	std::string db_path_;
	sqlite3* db_ = nullptr;
	bool create_table() const;
};
