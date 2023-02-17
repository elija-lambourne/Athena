#include "DbManager.h"
#include <string>

//public
db_manager::db_manager(const std::string& db_path)
{
	this->db_path_ = db_path;
}
db_manager::~db_manager()
{
	terminate_con();
}
//! MAJOR VULNERABILITIES DUE TO POSSIBLE SQL INJECTIONS
bool db_manager::store_entry(const pass_entry& entry) const
{
	if (db_ == nullptr || !create_table())
	{
		return false;
	}

	const std::string insert = "INSERT INTO PASSWORDS (id,password,source) VALUES(?,?,?);";
	sqlite3_stmt* statement = nullptr;
	if(sqlite3_prepare_v2(db_, insert.c_str(), -1, &statement, nullptr) != SQLITE_OK)
	{
		return false;
	}
	sqlite3_bind_int(statement, 1, entry.id);
	sqlite3_bind_text(statement, 2, entry.password.c_str(), static_cast<int>(entry.password.length()), SQLITE_TRANSIENT);
	sqlite3_bind_text(statement, 3, entry.source.c_str(), static_cast<int>(entry.source.length()), SQLITE_TRANSIENT);
	if(sqlite3_step(statement) != SQLITE_DONE)
	{
		return false;
	}
	sqlite3_finalize(statement);
	
	return true;
}

//! MAJOR VULNERABILITIES DUE TO POSSIBLE SQL INJECTIONS
std::vector<pass_entry> db_manager::search_by_src(const std::string& src) const
{
	std::vector<pass_entry> results;
	if (db_ == nullptr || !create_table())
	{
		return results;
	}
	
	
	const std::string get_all = "SELECT * FROM PASSWORDS WHERE source=?;";
	sqlite3_stmt* statement = nullptr;
	if(sqlite3_prepare_v2(db_, get_all.c_str(), -1, &statement, nullptr) != SQLITE_OK)
	{
		return results;
	}
	sqlite3_bind_text(statement, 1, src.c_str(), static_cast<int>(src.length()), SQLITE_TRANSIENT);
	while(sqlite3_step(statement) == SQLITE_ROW)
	{
		const std::string password = reinterpret_cast<const char*>(sqlite3_column_text(statement,1));
		const std::string source = reinterpret_cast<const char*>(sqlite3_column_text(statement,2));
		results.emplace_back(password, source);
	}
	sqlite3_finalize(statement);

	return results;
}

std::vector<pass_entry> db_manager::get_all() const
{
	std::vector<pass_entry> results;
	if (db_ == nullptr || !create_table())
	{
		return results;
	}
	
	
	const std::string get_all = "SELECT * FROM PASSWORDS";
	sqlite3_stmt* statement = nullptr;
	if(sqlite3_prepare_v2(db_, get_all.c_str(), -1, &statement, nullptr) != SQLITE_OK)
	{
		return results;
	}
	while(sqlite3_step(statement) == SQLITE_ROW)
	{
		const std::string password = reinterpret_cast<const char*>(sqlite3_column_text(statement,1));
		const std::string source = reinterpret_cast<const char*>(sqlite3_column_text(statement,2));
		results.emplace_back(password, source);
	}
	sqlite3_finalize(statement);

	return results;
}

bool db_manager::start_con() //https://www.sqlite.org/c3ref/open.html
{
	return sqlite3_open(db_path_.c_str(), &db_) == SQLITE_OK;
}

bool db_manager::terminate_con() //https://www.sqlite.org/c3ref/close.html
{//! db_ will be changed
	return sqlite3_close(db_) == SQLITE_OK;
}
bool db_manager::create_table() const //https://www.sqlite.org/c3ref/exec.html
{
	const auto create_if = "CREATE TABLE IF NOT EXISTS PASSWORDS (id INT,password TEXT, source TEXT);";
	return sqlite3_exec(db_, create_if, nullptr, nullptr, nullptr) == SQLITE_OK;
}
