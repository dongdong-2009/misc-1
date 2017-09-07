/*
 * HxConfig.h
 *
 *  Created on: 2017年8月23日
 *      Author: houxd
 *  ==========================================================
 *  Demo Usage:
 *
	struct Config : HxConfig {
		Hx_KeyDef(std::string,book,"houxd")
		Hx_KeyDef(int,book_count,3)
		Hx_KeyDef(vector<int>,array,{78,1,9,3})
		Hx_KeyEnd()    // !!! must define Hx_KeyEnd() !!!
	} __gcc_packed;		// !!! must packed !!!
	Config config;
	const char *fpath = "/opt/a.ini";
	config.Load(fpath);
	printf("book is %s\n",config.book.c_str());
	printf("book_count is %d\n",config.book_count);
	config.book_count.val--;
	config.Save(fpath);

 *
 *  Supported Types:
 *	char,short,int,long,long long,unsigned char,
 *	unsigned short,unsigned int,unsigned long,unsigned long long,
 *	float,double,long double,bool,string,
 *	vector<T> surpported, hehe.
 *	And self defined simple type can be supported yet.
 *  =========================================================
 */

#ifndef HXCONFIG_H_
#define HXCONFIG_H_
#include <string>
#include <vector>
#include <typeinfo>
#include <string.h>

using std::string;
using std::vector;

#ifndef __gcc_packed
#define __gcc_packed __attribute__ ((packed))
#endif

struct HxReflector {
	char *_type;
	char *_name;
	int _memberSize;
	void *_defVal;
	/*
	 * t
	 */
	template<typename T>
	HxReflector(const char *t, const char *n,int ms,const T &defVal)
		:_type(strdup(t?t:"")),_name(strdup(n?n:"")),_memberSize(ms),_defVal(new T(defVal)){}
	~HxReflector();
	void *valueAddr()const ;
	HxReflector *next()const ;
	void setValue(std::string val);
	std::string getValue()const;
	std::string getDefVal()const;
} __gcc_packed;

#pragma pack(push,1)
struct HxConfig {
	bool Load(const char *filePath);
	bool Save(const char *filePath);
} __gcc_packed;

#define Hx_KeyDef(Type,Name,Default...) \
	struct z_##Name##reflect_info_class : HxReflector { \
		z_##Name##reflect_info_class():HxReflector(typeid(Type).name(),#Name,sizeof(Type),Type(Default)){} \
	} __gcc_packed Name##reflect_info; \
	Type Name ;

#define Hx_KeyEnd() \
	struct z_##Name##reflect_info_class : HxReflector { \
		z_##Name##reflect_info_class():HxReflector(typeid(int).name(),NULL,0,int(0)){} \
	} __gcc_packed Name##reflect_info; \

#endif /* HXCONFIG_H_ */
