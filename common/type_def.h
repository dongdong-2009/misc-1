/*
 * type_def.h
 *
 *  Created on: 2017年8月29日
 *      Author: houxd
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <stdint.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "time.h"
#include "../common/convert.h"
#define __gcc_packed __attribute__ ((packed))

template<int bytes>
struct __byte_x_t {
	uint8_t b[bytes];
	__byte_x_t<bytes>(){}
	__byte_x_t<bytes>(const char *s){
		operator =(s);
	}
	std::string toHexStr()const{
		char buf[bytes*2+1];
		hx_dumphex2str(this,bytes,buf);
		return std::string(buf);
	}
	void fromHexStr(const char *hexstr){
		hx_hexcode2bin(hexstr,bytes<<1,this);
	}
	void fromHexStr(std::string hexstr){
		char buf[bytes*2+1];
		memset(buf,0,bytes*2+1);
		snprintf(buf,bytes*2+1,"%s",hexstr.c_str());
		hx_hexcode2bin(buf,bytes<<1,this);
	}
	template<int newlen>
	__byte_x_t<newlen> convert(int fillchar=0){
		__byte_x_t<newlen> res;
		if(sizeof(*this)<newlen){
			memset(res.b,fillchar,newlen);
			memcpy(res.b,this,sizeof(*this));
		}else{
			memcpy(res.b,this,newlen);
		}
		return res;
	}
	template<int appendlen>
	__byte_x_t<bytes+appendlen> append(const char *appends){
		__byte_x_t<bytes+appendlen> res;
		memcpy(res.b,this,bytes);
		memcpy(&res.b[bytes],appends,bytes);
		return res;
	}
	bool operator==(const __byte_x_t<bytes>& v)const{
		return memcmp(this->b,v.b,bytes)==0;
	}
	void operator=(const char *s){
		memcpy(this->b,s,bytes);
	}
	void print(const char *prefix=0)const{
		if(prefix)
			::printf("%s%s\n",prefix,toHexStr().c_str());
		else
			::printf("val=%s\n",toHexStr().c_str());
	}
} __gcc_packed;

struct __byte_2_t {
	uint16_t toUint16Msb()const;
	uint16_t toUint16Lsb()const;
	void fromUint16Msb(uint16_t v);
	void fromUint16Lsb(uint16_t v);
} __gcc_packed;
struct __byte_3_t:__byte_2_t {
	uint32_t toUint24Msb()const;
	uint32_t toUint24Lsb()const;
	void fromUint24Msb(uint32_t v);
	void fromUint24Lsb(uint32_t v);
} __gcc_packed;
struct __byte_4_t:__byte_3_t{
	uint32_t toUint32Msb()const;
	uint32_t toUint32Lsb()const;
	void fromUint32Msb(uint32_t v);
	void fromUint32Lsb(uint32_t v);
} __gcc_packed;
struct __byte_8_t:__byte_4_t{
	uint64_t toUint64Msb()const;
	uint64_t toUint64Lsb()const;
	void fromUint64Msb(uint64_t v);
	void fromUint64Lsb(uint64_t v);
} __gcc_packed;

/*
 * all members as format HMS. like x10\x42\x00 -> 10:42:00
 */
struct __time_3_byte_t {
	void setToNow();
	uint getHour()const;
	uint getMunite()const;
	uint getSecond()const;
} __gcc_packed;
/*
 * all members as format YYMD. like \x20\x17\x09\x04 -> 2017.09.24
 */
struct __date_4_byte_t {
	void setToNow();
	uint getYear()const;
	uint getMouth()const;
	uint getDate()const;
	time_t toTimeAsBcdYYMD()const;
	double toTimeDiffNow()const;
	double toTimeNowDiff()const;
} __gcc_packed;
/*
 * all members as format YYMDHMS. like \x20\x17\x09\x04\x10\x42\x00
 * 										-> 2017.09.24 10:42:00
 */
struct __date_time_7_byte_t {
	void setToNow();
	time_t toTimeAsBcdYYMDHMS()const;
	uint getYear()const;
	uint getMouth()const;
	uint getDate()const;
	uint getHour()const;
	uint getMunite()const;
	uint getSecond()const;
	double toTimeDiffNow()const;
	double toTimeNowDiff()const;
} __gcc_packed;




typedef uint8_t byte1_t;
struct byte2_t:	__byte_x_t<2>, 	__byte_2_t {using __byte_x_t<2>::__byte_x_t;using __byte_x_t<2>::operator=;}__gcc_packed;
struct byte3_t: __time_3_byte_t, __byte_x_t<3>, __byte_3_t {using __byte_x_t<3>::__byte_x_t;using __byte_x_t<3>::operator=;}__gcc_packed;
struct byte4_t: __date_4_byte_t, __byte_x_t<4>, __byte_4_t {using __byte_x_t<4>::__byte_x_t;using __byte_x_t<4>::operator=;}__gcc_packed;
struct byte5_t: __byte_x_t<5>, 	__byte_4_t {using __byte_x_t<5>::__byte_x_t;using __byte_x_t<5>::operator=;}__gcc_packed;
struct byte6_t: __byte_x_t<6>, 	__byte_4_t {using __byte_x_t<6>::__byte_x_t;using __byte_x_t<6>::operator=;}__gcc_packed;
struct byte7_t: __date_time_7_byte_t,__byte_x_t<7>, __byte_4_t {using __byte_x_t<7>::__byte_x_t;using __byte_x_t<7>::operator=;}__gcc_packed;
struct byte8_t: __byte_x_t<8>, 	__byte_8_t {using __byte_x_t<8>::__byte_x_t;using __byte_x_t<8>::operator=;}__gcc_packed;
struct byte9_t: __byte_x_t<9>, 	__byte_8_t {using __byte_x_t<9>::__byte_x_t;using __byte_x_t<9>::operator=;}__gcc_packed;
struct byte10_t:__byte_x_t<10>, __byte_8_t {using __byte_x_t<10>::__byte_x_t;using __byte_x_t<10>::operator=;}__gcc_packed;
struct byte11_t:__byte_x_t<11>, __byte_8_t {using __byte_x_t<11>::__byte_x_t;using __byte_x_t<11>::operator=;}__gcc_packed;
struct byte12_t:__byte_x_t<12>, __byte_8_t {using __byte_x_t<12>::__byte_x_t;using __byte_x_t<12>::operator=;}__gcc_packed;
struct byte13_t:__byte_x_t<13>, __byte_8_t {using __byte_x_t<13>::__byte_x_t;using __byte_x_t<13>::operator=;}__gcc_packed;
struct byte14_t:__byte_x_t<14>, __byte_8_t {using __byte_x_t<14>::__byte_x_t;using __byte_x_t<14>::operator=;}__gcc_packed;
struct byte15_t:__byte_x_t<15>, __byte_8_t {using __byte_x_t<15>::__byte_x_t;using __byte_x_t<15>::operator=;}__gcc_packed;
struct byte16_t:__byte_x_t<16>, __byte_8_t {using __byte_x_t<16>::__byte_x_t;using __byte_x_t<16>::operator=;}__gcc_packed;

/*
 * for card msb 4 byte money define
 * dont use this for struct inner defines.
 */
struct money_msb_t : byte4_t {
	money_msb_t()	{byte4_t::fromUint32Msb(0);}
	money_msb_t(uint32_t v)	{byte4_t::fromUint32Msb(v);}
	money_msb_t(byte4_t v)	{memcpy(this->b,v.b,4);}
	void operator=(uint32_t v)	{byte4_t::fromUint32Msb(v);}
	void operator=(byte4_t v)	{memcpy(this->b,v.b,4);}
	uint32_t val()const	{return byte4_t::toUint32Msb();}
	bool operator>	(const money_msb_t& v)const	{return this->toUint32Msb()> 	(v.toUint32Msb());}
	bool operator>=	(const money_msb_t& v)const	{return this->toUint32Msb()>= 	(v.toUint32Msb());}
	bool operator<	(const money_msb_t& v)const	{return this->toUint32Msb()< 	(v.toUint32Msb());}
	bool operator<=	(const money_msb_t& v)const	{return this->toUint32Msb()<= 	(v.toUint32Msb());}
	bool operator==	(const money_msb_t& v)const	{return this->toUint32Msb()== 	(v.toUint32Msb());}
	uint32_t operator+	(const money_msb_t& v)const {return this->toUint32Msb()+	(v.toUint32Msb());}
	uint32_t operator-	(const money_msb_t& v)const {return this->toUint32Msb()-	(v.toUint32Msb());}
	uint32_t operator*	(const money_msb_t& v)const {return this->toUint32Msb()*	(v.toUint32Msb());}
	uint32_t operator/	(const money_msb_t& v)const {return this->toUint32Msb()/	(v.toUint32Msb());}
	uint32_t operator+=	(const money_msb_t& v) {*this = this->toUint32Msb()+	(v.toUint32Msb());	return this->val();}
	uint32_t operator-=	(const money_msb_t& v) {*this = this->toUint32Msb()-	(v.toUint32Msb());	return this->val();}
	uint32_t operator*=	(const money_msb_t& v) {*this = this->toUint32Msb()*	(v.toUint32Msb());	return this->val();}
	uint32_t operator/=	(const money_msb_t& v) {*this = this->toUint32Msb()/	(v.toUint32Msb());	return this->val();}
}__gcc_packed;

struct money_lsb_t : byte4_t {
	money_lsb_t()	{byte4_t::fromUint32Lsb(0);}
	money_lsb_t(uint32_t v)	{byte4_t::fromUint32Lsb(v);}
	money_lsb_t(byte4_t v)	{memcpy(this->b,v.b,4);}
	void operator=(uint32_t v)	{byte4_t::fromUint32Lsb(v);}
	void operator=(byte4_t v)	{memcpy(this->b,v.b,4);}
	uint32_t val()const	{return byte4_t::toUint32Lsb();}
	bool operator>(const money_lsb_t& v)const	{return this->toUint32Lsb()> 	(v.toUint32Lsb());}
	bool operator>=(const money_lsb_t& v)const	{return this->toUint32Lsb()>= 	(v.toUint32Lsb());}
	bool operator<(const money_lsb_t& v)const	{return this->toUint32Lsb()< 	(v.toUint32Lsb());}
	bool operator<=(const money_lsb_t& v)const	{return this->toUint32Lsb()<= 	(v.toUint32Lsb());}
	bool operator==(const money_lsb_t& v)const	{return this->toUint32Lsb()== 	(v.toUint32Lsb());}
	uint32_t operator+	(const money_lsb_t& v)const {return this->toUint32Lsb()+	(v.toUint32Lsb());}
	uint32_t operator-	(const money_lsb_t& v)const {return this->toUint32Lsb()-	(v.toUint32Lsb());}
	uint32_t operator*	(const money_lsb_t& v)const {return this->toUint32Lsb()*	(v.toUint32Lsb());}
	uint32_t operator/	(const money_lsb_t& v)const {return this->toUint32Lsb()/	(v.toUint32Lsb());}
	uint32_t operator+=	(const money_lsb_t& v) {*this = this->toUint32Lsb()+	(v.toUint32Lsb());	return this->val();}
	uint32_t operator-=	(const money_lsb_t& v) {*this = this->toUint32Lsb()-	(v.toUint32Lsb());	return this->val();}
	uint32_t operator*=	(const money_lsb_t& v) {*this = this->toUint32Lsb()*	(v.toUint32Lsb());	return this->val();}
	uint32_t operator/=	(const money_lsb_t& v) {*this = this->toUint32Lsb()/	(v.toUint32Lsb());	return this->val();}
}__gcc_packed;

typedef byte3_t bcd_time_t;
typedef byte4_t bcd_date_t;
typedef byte7_t bcd_datetime_t;


#endif /* TYPEDEFS_H_ */
