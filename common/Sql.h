/*
 * Sql.h
 *
 *  Created on: 2017年8月19日
 *      Author: houxd
 */

#ifndef SQL_H_
#define SQL_H_

#include <string>
#include <sstream>
#include <mutex>
#include <vector>
#include <map>
#include <stdint.h>
#include <stdlib.h>
#include "../sqlite-amalgamation-3190300/sqlite3.h"

class Sql {
public:
	typedef sqlite3* sqldb;
	typedef sqlite3_value* sqlval;
	typedef sqlite3_stmt* sqlstmt;
	typedef sqlite3_callback sqlcall;
private:
	static const uint SqlCmdBufsize = 4096;
	sqldb pdb;
	sqlstmt stmt;
	std::mutex mtx;
	char *lasterr;
	uint rowMax;
	std::vector<std::vector<std::string>> *pres;
	std::vector<sqlval> vecStepRow;
	std::map<std::string,sqlval> mapStepRow;
public:
	Sql();
	~Sql();
	bool connect(std::string fpath);
	bool disconnect();
	/*
	 * off:fast on:slow normal:
	 */
	enum SynchronousLevel {
		SyncOn,SyncNormal,SyncOff,
	};
	bool synchronous(SynchronousLevel level);
public:
	bool prepare(std::string cmd, ...);
	bool bind_blob(int param_index, const void *value, int len);
	bool bind_blob(std::string param_id, const void *value, int len);
	bool step();
	bool step_exec_all();
	bool finalize();
	int column_count();
	sqlval value(std::string mane);
	sqlval value(int col);
	int value_bytes(sqlval sv);
	int value_bytes(std::string name);
	int value_bytes(int col);
	const void *value_blob(sqlval v);
	const void *value_blob(std::string name);
	const void *value_blob(int col);
	int value_int(sqlval v);
	int value_int(std::string name);
	int value_int(int col);
	int64_t value_int64(sqlval v);
	int64_t value_int64(std::string name);
	int64_t value_int64(int col);
	const char * value_text(sqlval v);
	const char * value_text(std::string name);
	const char * value_text(int col);
	bool _exec(std::string cmd, sqlcall callback=NULL);
	bool exec(std::string cmd, ...);
private:
	static int exec_callback(void* pthis, int cols, char* vals[], char* names[]);
public:
	bool exec(std::vector<std::vector<std::string>> &res, uint rowmax, std::string cmd, ...);
	uint tables(std::vector<std::string> &res);
};



#endif /* SQL_H_ */
