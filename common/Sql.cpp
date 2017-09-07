/*
 * Sql.cpp
 *
 *  Created on: 2017年8月19日
 *      Author: houxd
 */

#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "../sqlite-amalgamation-3190300/sqlite3.h"
#include "convert.h"
#include "utils.h"
#include "rec.h"
#include "Sql.h"

using namespace std;


Sql::Sql():pdb(NULL),stmt(NULL),lasterr(NULL),
		//callback(NULL),
		rowMax(0),pres(NULL),
		vecStepRow(0),mapStepRow()
{}
Sql::~Sql()
{
	if(lasterr) {
		sqlite3_free(lasterr);
		lasterr = NULL;
	}
}
bool Sql::connect(string fpath)
{
	int r = sqlite3_open(fpath.c_str(), &pdb);
	if (r != SQLITE_OK) {
		pdb = NULL;
		return false;
	}
	if(pdb==NULL)
		return false;
	return true;
}
bool Sql::disconnect()
{
	mtx.lock();
	int res = sqlite3_close(pdb);
	mtx.unlock();
	if(res!=SQLITE_OK)
		return true;
	return false;
}
bool Sql::synchronous(SynchronousLevel level)
{
	return exec("PRAGMA synchronous = %s;",
		level==SyncOn?"ON":level==SyncNormal?"NORMAL":"OFF"
	);
}
bool Sql::prepare(string cmd, ...)
{
	if(pdb==NULL)
		return false;
	if(lasterr) {
		sqlite3_free(lasterr);
		lasterr = NULL;
	}
	va_list va;
	va_start(va,cmd);
	char sqlbuf[SqlCmdBufsize];
	vsnprintf(sqlbuf,SqlCmdBufsize,cmd.c_str(),va);
	va_end(va);
	mtx.lock();
	int res = sqlite3_prepare_v2(pdb,sqlbuf,-1,&stmt,NULL);
	if(res == SQLITE_OK){
		return true;
	}
	stmt = NULL;
	mtx.unlock();
	return false;
}
bool Sql::bind_blob(int param_index, const void *value, int len)
{
	if(param_index<1 || param_index>SQLITE_LIMIT_VARIABLE_NUMBER)
		return false;
	int res = sqlite3_bind_blob(stmt, param_index, value, len, SQLITE_STATIC);
	return (res == SQLITE_OK);
}
bool Sql::bind_blob(string param_id, const void *value, int len)
{
	int index = sqlite3_bind_parameter_index(stmt, param_id.c_str());
    int res = sqlite3_bind_blob(stmt, index, value, len, SQLITE_STATIC);
 	return (res == SQLITE_OK);
}
bool Sql::step()
{
	vecStepRow.clear();
	if(pdb==NULL)
		return false;
	if(lasterr) {
		sqlite3_free(lasterr);
		lasterr = NULL;
	}
	int res = sqlite3_step(stmt);
	if(res==SQLITE_ROW){
		int count = sqlite3_column_count(stmt);
		if(count>0){
			vecStepRow.resize(count);
			for(int i=0;i<count;i++){
				sqlval val = sqlite3_column_value(stmt,i);
				vecStepRow[i] = val;
				string name = sqlite3_column_name(stmt,i);
				mapStepRow[name] =  val;
			}
			return true;
		}
	}
	return false;
}
bool Sql::step_exec_all()
{
	if(pdb==NULL)
		return false;
	if(lasterr) {
		sqlite3_free(lasterr);
		lasterr = NULL;
	}
	int res;
	do{
		res = sqlite3_step(stmt);
		//SQLITE_BUSY inpossable
		if(res==SQLITE_ERROR || res==SQLITE_MISUSE )
			return false;
	}while(res!=SQLITE_DONE);
	return true;
}
bool Sql::finalize()
{
	int res = SQLITE_OK;
	if(stmt)
		res = sqlite3_finalize(stmt);
	stmt = NULL;
	mtx.unlock();
	return (res == SQLITE_OK);
}
int Sql::column_count()
{
	return (int) vecStepRow.size();
}
Sql::sqlval Sql::value(string name)
{
	sqlval sv = NULL;
	try{
		sv = mapStepRow[name];
	}catch(...){};
	return sv;
}
Sql::sqlval Sql::value(int col)
{
	sqlval sv = NULL;
	try{
		sv = vecStepRow[col];
	}catch(...){};
	return sv;
}
int Sql::value_bytes(sqlval sv)
{
	return sqlite3_value_bytes(sv);
}
int Sql::value_bytes(string name)
{
	int rv = 0;
	try{
		sqlval sv = mapStepRow[name];
		rv = sqlite3_value_bytes(sv);
	}catch(...){};
	return rv;
}
int Sql::value_bytes(int col)
{
	int rv = 0;
	try{
		rv = sqlite3_value_bytes(vecStepRow[col]);
	}catch(...){};
	return rv;
}
const void *Sql::value_blob(sqlval sv)
{
	return sqlite3_value_blob(sv);
}
const void *Sql::value_blob(string name)
{
	const void * rv = NULL;
	try{
		rv = sqlite3_value_blob(mapStepRow[name]);
	}catch(...){};
	return rv;
}
const void *Sql::value_blob(int col)
{
	const void * rv = NULL;
	try{
		rv = sqlite3_value_blob(vecStepRow[col]);
	}catch(...){};
	return rv;
}
int Sql::value_int(sqlval sv)
{
	return sqlite3_value_int(sv);
}
int Sql::value_int(string name)
{
	int rv = 0;
	try{
		rv = sqlite3_value_int(mapStepRow[name]);
	}catch(...){};
	return rv;
}
int Sql::value_int(int col)
{
	int rv = 0;
	try{
		rv = sqlite3_value_int(vecStepRow[col]);
	}catch(...){};
	return rv;
}
int64_t Sql::value_int64(sqlval sv)
{
	return sqlite3_value_int64(sv);
}
int64_t Sql::value_int64(string name)
{
	int64_t rv = 0;
	try{
		rv = sqlite3_value_int64(mapStepRow[name]);
	}catch(...){};
	return rv;
}
int64_t Sql::value_int64(int col)
{
	int64_t rv = 0;
	try{
		rv = sqlite3_value_int64(vecStepRow[col]);
	}catch(...){};
	return rv;
}
const char* Sql::value_text(sqlval sv)
{
	return (const char*)sqlite3_value_text(sv);
}
const char * Sql::value_text(string name)
{
	const char * rv = 0;
	try{
		rv = (const char*)sqlite3_value_text(mapStepRow[name]);
	}catch(...){};
	return rv;
}
const char * Sql::value_text(int col)
{
	const char * rv = 0;
	try{
		rv = (const char*)sqlite3_value_text(vecStepRow[col]);
	}catch(...){};
	return rv;
}

bool Sql::_exec(string cmd, sqlite3_callback callback)
{
	if(pdb==NULL)
		return false;
	if(lasterr) sqlite3_free(lasterr);
	mtx.lock();
	int res = sqlite3_exec(pdb, cmd.c_str(), callback, this, &lasterr);
	mtx.unlock();
	return (res == SQLITE_OK);
}

bool Sql::exec(string cmd, ...)
{
	pres = NULL;
	rowMax = 0;
	//callback = 0;
	va_list va;
	va_start(va,cmd);
	char sqlbuf[SqlCmdBufsize];
	vsnprintf(sqlbuf,SqlCmdBufsize,cmd.c_str(),va);
	va_end(va);
	return _exec(sqlbuf);
}
int Sql::exec_callback(void* pthis, int cols, char* vals[], char* names[])
{
	Sql *p = (Sql*)pthis;
	if(p->rowMax>0){
		p->rowMax--;
		vector<string> row(cols);
		for(int i=0;i<cols;i++){
			row[i] = vals[i];
		}
		p->pres->push_back(row);
	}
	return SQLITE_OK;
}
bool Sql::exec(vector<vector<string>> &res, uint rowmax, string cmd, ...)
{
	res.clear();
	pres = &res;
	rowMax = rowmax;
	//callback = exec_callback;
	va_list va;
	va_start(va,cmd);
	char sqlbuf[SqlCmdBufsize];
	vsnprintf(sqlbuf,SqlCmdBufsize,cmd.c_str(),va);
	va_end(va);
	return _exec(sqlbuf,exec_callback);
}
uint Sql::tables(vector<string> &res)
{
	res.clear();
	vector<vector<string>> rt;
	if(exec(rt,32,"SELECT name FROM sqlite_master WHERE type='table' ORDER BY name")){
		if(rt.size()>0){
			res.resize(rt.size());
			for(uint i=0;i<rt.size();i++){
				res[i] = rt[i][0];
			}
		}
	}
	return res.size();
}


