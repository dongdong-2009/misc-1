/*
 * HxConfig.cpp
 *
 *  Created on: 2017年8月23日
 *      Author: houxd
 */

#include <HxConfig.h>
#include <string>
#include <sstream>
#include <string.h>
#include <typeinfo>
#include <string.h>
#include "utils.h"
using namespace std;

#define hx_cfg_printf(...)	//printf(__VA_ARGS__)

//template<typename T>
//HxReflector::HxReflector(const char *t, const char *n,int ms,const T &defVal)
//	:_type(strdup(t?t:"")),_name(strdup(n?n:"")),_memberSize(ms),
//	 _defVal(new T(defVal))
//{
//}
HxReflector::~HxReflector(){
	if(_type)free(_type);
	if(_name)free(_name);
#define VALUE_CONVERT_SEGMENT(t) \
	if(strcmp(typeid(t).name(),_type)==0){\
		delete ((t*)_defVal);\
	}
	VALUE_CONVERT_SEGMENT(char)
	VALUE_CONVERT_SEGMENT(short)
	VALUE_CONVERT_SEGMENT(int)
	VALUE_CONVERT_SEGMENT(long)
	VALUE_CONVERT_SEGMENT(long long)
	VALUE_CONVERT_SEGMENT(unsigned char)
	VALUE_CONVERT_SEGMENT(unsigned short)
	VALUE_CONVERT_SEGMENT(unsigned int)
	VALUE_CONVERT_SEGMENT(unsigned long)
	VALUE_CONVERT_SEGMENT(unsigned long long)
	VALUE_CONVERT_SEGMENT(float)
	VALUE_CONVERT_SEGMENT(double)
	VALUE_CONVERT_SEGMENT(long double)
	VALUE_CONVERT_SEGMENT(bool)
	VALUE_CONVERT_SEGMENT(string)

#undef VALUE_CONVERT_SEGMENT

#define VALUE_CONVERT_SEGMENT(t) \
	if(strcmp(typeid(vector<t>).name(),_type)==0){\
		delete ((vector<t>*)_defVal);\
	}
	VALUE_CONVERT_SEGMENT(char)
	VALUE_CONVERT_SEGMENT(short)
	VALUE_CONVERT_SEGMENT(int)
	VALUE_CONVERT_SEGMENT(long)
	VALUE_CONVERT_SEGMENT(long long)
	VALUE_CONVERT_SEGMENT(unsigned char)
	VALUE_CONVERT_SEGMENT(unsigned short)
	VALUE_CONVERT_SEGMENT(unsigned int)
	VALUE_CONVERT_SEGMENT(unsigned long)
	VALUE_CONVERT_SEGMENT(unsigned long long)
	VALUE_CONVERT_SEGMENT(float)
	VALUE_CONVERT_SEGMENT(double)
	VALUE_CONVERT_SEGMENT(long double)
	VALUE_CONVERT_SEGMENT(bool)
	VALUE_CONVERT_SEGMENT(string)

#undef VALUE_CONVERT_SEGMENT
}
void *HxReflector::valueAddr()const {
	return (void*)(this+1);
}
HxReflector *HxReflector::next()const {
	if(_memberSize==0)
		return NULL;
	HxReflector *res = (HxReflector*)(_memberSize + (char*)(this+1));
	if(res->_type[0]==0 || res->_name[0]==0 || res->_memberSize==0)
		return NULL;
	return res;
}
void HxReflector::setValue(string val){
#define VALUE_CONVERT_SEGMENT(t) \
	if(strcmp(typeid(t).name(),_type)==0){\
		hx_cfg_printf("setVal: type is %s\n",_type.c_str());\
		stringstream ss(val);\
		ss>>*((t*)valueAddr());\
	}
	VALUE_CONVERT_SEGMENT(char)
	VALUE_CONVERT_SEGMENT(short)
	VALUE_CONVERT_SEGMENT(int)
	VALUE_CONVERT_SEGMENT(long)
	VALUE_CONVERT_SEGMENT(long long)
	VALUE_CONVERT_SEGMENT(unsigned char)
	VALUE_CONVERT_SEGMENT(unsigned short)
	VALUE_CONVERT_SEGMENT(unsigned int)
	VALUE_CONVERT_SEGMENT(unsigned long)
	VALUE_CONVERT_SEGMENT(unsigned long long)
	VALUE_CONVERT_SEGMENT(float)
	VALUE_CONVERT_SEGMENT(double)
	VALUE_CONVERT_SEGMENT(long double)
	VALUE_CONVERT_SEGMENT(bool)
	VALUE_CONVERT_SEGMENT(string)
#undef VALUE_CONVERT_SEGMENT

#define VALUE_CONVERT_SEGMENT(t)\
	if(strcmp(typeid(vector<t>).name(),_type)==0){\
		hx_cfg_printf("setVal: type is %s\n",_type.c_str());\
		vector<t> &v = *(vector<t>*)valueAddr();\
		v.clear();\
		stringstream ss(val);\
		for(;;){\
			t vo;\
			ss>>vo;\
			if(ss.fail())\
				break;\
			v.push_back(vo);\
		}\
	}
	VALUE_CONVERT_SEGMENT(char)
	VALUE_CONVERT_SEGMENT(short)
	VALUE_CONVERT_SEGMENT(int)
	VALUE_CONVERT_SEGMENT(long)
	VALUE_CONVERT_SEGMENT(long long)
	VALUE_CONVERT_SEGMENT(unsigned char)
	VALUE_CONVERT_SEGMENT(unsigned short)
	VALUE_CONVERT_SEGMENT(unsigned int)
	VALUE_CONVERT_SEGMENT(unsigned long)
	VALUE_CONVERT_SEGMENT(unsigned long long)
	VALUE_CONVERT_SEGMENT(float)
	VALUE_CONVERT_SEGMENT(double)
	VALUE_CONVERT_SEGMENT(long double)
	VALUE_CONVERT_SEGMENT(bool)
	VALUE_CONVERT_SEGMENT(string)
#undef VALUE_CONVERT_SEGMENT

	hx_cfg_printf("setVal: type is %s  ***NC\n",type.c_str());
}
string HxReflector::getValue()const{
#define VALUE_CONVERT_SEGMENT(t) \
	if(strcmp(typeid(t).name(),_type)==0){\
		stringstream ss;\
		ss<<*((t*)valueAddr());\
		hx_cfg_printf("setval: type is %s\n",type.c_str());\
		return ss.str();\
	}
	VALUE_CONVERT_SEGMENT(char)
	VALUE_CONVERT_SEGMENT(short)
	VALUE_CONVERT_SEGMENT(int)
	VALUE_CONVERT_SEGMENT(long)
	VALUE_CONVERT_SEGMENT(long long)
	VALUE_CONVERT_SEGMENT(unsigned char)
	VALUE_CONVERT_SEGMENT(unsigned short)
	VALUE_CONVERT_SEGMENT(unsigned int)
	VALUE_CONVERT_SEGMENT(unsigned long)
	VALUE_CONVERT_SEGMENT(unsigned long long)
	VALUE_CONVERT_SEGMENT(float)
	VALUE_CONVERT_SEGMENT(double)
	VALUE_CONVERT_SEGMENT(long double)
	VALUE_CONVERT_SEGMENT(bool)
	VALUE_CONVERT_SEGMENT(string)
#undef VALUE_CONVERT_SEGMENT

#define VALUE_CONVERT_SEGMENT(t)\
	if(strcmp(typeid(vector<t>).name(),_type)==0){\
		vector<t> &v = *(vector<t>*)valueAddr();\
		stringstream ss;\
		for(uint i=0;i<v.size();i++){\
			ss<<v[i]<<" ";\
		}\
		hx_cfg_printf("setval: type is %s\n",type.c_str());\
		return ss.str();\
	}
	VALUE_CONVERT_SEGMENT(char)
	VALUE_CONVERT_SEGMENT(short)
	VALUE_CONVERT_SEGMENT(int)
	VALUE_CONVERT_SEGMENT(long)
	VALUE_CONVERT_SEGMENT(long long)
	VALUE_CONVERT_SEGMENT(unsigned char)
	VALUE_CONVERT_SEGMENT(unsigned short)
	VALUE_CONVERT_SEGMENT(unsigned int)
	VALUE_CONVERT_SEGMENT(unsigned long)
	VALUE_CONVERT_SEGMENT(unsigned long long)
	VALUE_CONVERT_SEGMENT(float)
	VALUE_CONVERT_SEGMENT(double)
	VALUE_CONVERT_SEGMENT(long double)
	VALUE_CONVERT_SEGMENT(bool)
	VALUE_CONVERT_SEGMENT(string)
#undef VALUE_CONVERT_SEGMENT

	hx_cfg_printf("setval: type is %s  ***NC\n",type.c_str());
	return "";
}
string HxReflector::getDefVal()const{
#define VALUE_CONVERT_SEGMENT(t) \
	if(strcmp(typeid(t).name(),_type)==0){\
		stringstream ss;\
		ss<<*((t*)_defVal);\
		hx_cfg_printf("setval: type is %s\n",type.c_str());\
		return ss.str();\
	}
	VALUE_CONVERT_SEGMENT(char)
	VALUE_CONVERT_SEGMENT(short)
	VALUE_CONVERT_SEGMENT(int)
	VALUE_CONVERT_SEGMENT(long)
	VALUE_CONVERT_SEGMENT(long long)
	VALUE_CONVERT_SEGMENT(unsigned char)
	VALUE_CONVERT_SEGMENT(unsigned short)
	VALUE_CONVERT_SEGMENT(unsigned int)
	VALUE_CONVERT_SEGMENT(unsigned long)
	VALUE_CONVERT_SEGMENT(unsigned long long)
	VALUE_CONVERT_SEGMENT(float)
	VALUE_CONVERT_SEGMENT(double)
	VALUE_CONVERT_SEGMENT(long double)
	VALUE_CONVERT_SEGMENT(bool)
	VALUE_CONVERT_SEGMENT(string)
#undef VALUE_CONVERT_SEGMENT

#define VALUE_CONVERT_SEGMENT(t)\
	if(strcmp(typeid(vector<t>).name(),_type)==0){\
		vector<t> &v = *(vector<t>*)_defVal;\
		stringstream ss;\
		for(uint i=0;i<v.size();i++){\
			ss<<v[i]<<" ";\
		}\
		hx_cfg_printf("setval: type is %s\n",type.c_str());\
		return ss.str();\
	}
	VALUE_CONVERT_SEGMENT(char)
	VALUE_CONVERT_SEGMENT(short)
	VALUE_CONVERT_SEGMENT(int)
	VALUE_CONVERT_SEGMENT(long)
	VALUE_CONVERT_SEGMENT(long long)
	VALUE_CONVERT_SEGMENT(unsigned char)
	VALUE_CONVERT_SEGMENT(unsigned short)
	VALUE_CONVERT_SEGMENT(unsigned int)
	VALUE_CONVERT_SEGMENT(unsigned long)
	VALUE_CONVERT_SEGMENT(unsigned long long)
	VALUE_CONVERT_SEGMENT(float)
	VALUE_CONVERT_SEGMENT(double)
	VALUE_CONVERT_SEGMENT(long double)
	VALUE_CONVERT_SEGMENT(bool)
	VALUE_CONVERT_SEGMENT(string)
#undef VALUE_CONVERT_SEGMENT

	hx_cfg_printf("setval: type is %s  ***NC\n",type.c_str());
	return "";
}
bool HxConfig::Load(const char *filePath)
{
	if(filePath==NULL)
		return false;
	INIFILE_T ini = inifile_open(filePath,"r");
	int inic = ini?inifile_entry_count(ini):0;
	HxReflector* p = (HxReflector*)this;
	if(p->valueAddr()==NULL){
		hx_cfg_printf("nothing!\n");
		return false;
	}
	do{
		char *s,*k,*v;
		hx_cfg_printf("key:%s val:%s\n",p->name.c_str(),p->setVal().c_str());
		int i;
		for(i=0;i<inic;i++){
			inifile_get_entry(ini,i,&s,&k,&v);
			if(strcmp(k,p->_name)==0){
				p->setValue(v);
				break;
			}
		}
		if(i==inic)
			p->setValue(p->getDefVal());
		p = p->next();
	}while(p);
	inifile_close(ini);
	return 0;
}
bool HxConfig::Save(const char *filePath)
{
	if(filePath==NULL)
		return false;
	INIFILE_T ini = inifile_open(filePath,"w+");
	if(ini==NULL)
		return false;
	HxReflector* p = (HxReflector*)this;
	if(p->valueAddr()==NULL){
		hx_cfg_printf("nothing!\n");
		return false;
	}
	do{
		hx_cfg_printf("key:%s val:%s\n",p->name.c_str(),p->setVal().c_str());
		inifile_setstr(ini,p->_name,p->getValue().c_str());
		p = p->next();
	}while(p);
	inifile_close(ini);
	return 0;
}

struct Conf:HxConfig {
	Hx_KeyDef(string,book,"fuck")
	Hx_KeyDef(int,book_count,71)
	Hx_KeyDef(char,book_c,'x')
	Hx_KeyDef(vector<int>,vv,{78,1,9,3})
	Hx_KeyDef(bool,save,false)
	Hx_KeyDef(string,good,"9988")

	Hx_KeyEnd()

} __gcc_packed;
Conf cf;
int main2(){
	vector<int> x = vector<int>({1,1});
	printf("%d\n",sizeof(cf));
	cf.Load("/opt/a.ini");
	cf.Save("/opt/a.ini");

	printf("book=%s\n",cf.book.c_str());
	printf("book_count=%d\n",cf.book_count);
	printf("book_c=%c\n",cf.book_c);
	printf("vv=%d\n",cf.vv[0]);
	printf("vv=%d\n",cf.vv[1]);
	printf("vv=%d\n",cf.vv[2]);
	printf("vv=%d\n",cf.vv[3]);
	printf("save=%d\n",cf.save);
	printf("good=%s\n",cf.good.c_str());

//	printf("val=%d\n",conf.book_count);
//	printf("val=%c\n",conf.good);


}


