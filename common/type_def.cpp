/*
 * type_def.cpp
 *
 *  Created on: 2017年9月1日
 *      Author: houxd
 */

#include "type_def.h"
#include "../common/convert.h"
#include "time.h"
#include "string.h"


uint16_t __byte_2_t::toUint16Msb()const
{
	return HX_MSB_B2W(this);
}
uint16_t __byte_2_t::toUint16Lsb()const
{
	return HX_LSB_B2W(this);
}
void __byte_2_t::fromUint16Msb(uint16_t v)
{
	HX_MSB_W2B(v,this);
}
void __byte_2_t::fromUint16Lsb(uint16_t v)
{
	HX_LSB_W2B(v,this);
}
uint32_t __byte_3_t::toUint24Msb()const
{
	return HX_MSB_B2DW24(this);
}
uint32_t __byte_3_t::toUint24Lsb()const
{
	return HX_LSB_B2DW24(this);
}
void __byte_3_t::fromUint24Msb(uint32_t v)
{
	HX_MSB_DW24_2B(v,this);
}
void __byte_3_t::fromUint24Lsb(uint32_t v)
{
	HX_MSB_DW24_2B(v,this);
}
uint32_t __byte_4_t::toUint32Msb()const
{
	return HX_MSB_B2DW(this);
}
uint32_t __byte_4_t::toUint32Lsb()const
{
	return HX_LSB_B2DW(this);
}
void __byte_4_t::fromUint32Msb(uint32_t v)
{
	HX_MSB_DW2B(v,this);
}
void __byte_4_t::fromUint32Lsb(uint32_t v)
{
	HX_LSB_DW2B(v,this);
}
uint64_t __byte_8_t::toUint64Msb()const
{
	return HX_MSB_B2QW(this);
}
uint64_t __byte_8_t::toUint64Lsb()const
{
	return HX_LSB_B2QW(this);
}
void __byte_8_t::fromUint64Msb(uint64_t v)
{
	HX_MSB_QW2B(v,this);
}
void __byte_8_t::fromUint64Lsb(uint64_t v)
{
	HX_LSB_QW2B(v,this);
}
void __time_3_byte_t::setToNow()
{
	struct tm tm;
	time_t t = time(NULL);
	localtime_r(&t,&tm);
	((uint8_t*)this)[0] = int2bcd(tm.tm_hour);
	((uint8_t*)this)[1] = int2bcd(tm.tm_min);
	((uint8_t*)this)[2] = int2bcd(tm.tm_sec);
}
uint __time_3_byte_t::getHour()const
{
	return bcd2int(((uint8_t*)this)[0]);
}
uint __time_3_byte_t::getMunite()const
{
	return bcd2int(((uint8_t*)this)[1]);
}
uint __time_3_byte_t::getSecond()const
{
	return bcd2int(((uint8_t*)this)[2]);
}
void __date_4_byte_t::setToNow()
{
	struct tm tm;
	time_t t = time(NULL);
	localtime_r(&t,&tm);
	uint y = tm.tm_year;
	((uint8_t*)this)[0] = int2bcd(y/100);
	((uint8_t*)this)[1] = int2bcd(y%100);
	((uint8_t*)this)[2] = int2bcd(tm.tm_mon);
	((uint8_t*)this)[3] = int2bcd(tm.tm_mday);
}
uint __date_4_byte_t::getYear()const
{
	uint y = bcd2int(((uint8_t*)this)[0]);
	y = y*100 + bcd2int(((uint8_t*)this)[1]);
	return y;
}
uint __date_4_byte_t::getMouth()const
{
	return bcd2int(((uint8_t*)this)[2]);
}
uint __date_4_byte_t::getDate()const
{
	return bcd2int(((uint8_t*)this)[3]);
}
time_t __date_4_byte_t::toTimeAsBcdYYMD()const {
	uint y = getYear();
	uint m = getMouth();
	uint d = getDate();
	struct tm tm;
	time_t t = time(NULL);
	localtime_r(&t,&tm);
	tm.tm_year = y-1900;
	tm.tm_mon = (m-1)%12;
	tm.tm_mday = d;
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	if(tm.tm_mday<1 || tm.tm_mday>31)
		tm.tm_mday = 1;
	return mktime(&tm);
}
double __date_4_byte_t::toTimeDiffNow()const
{
	time_t t = toTimeAsBcdYYMD();
	time_t now = time(NULL);
	return difftime(t,now);
}
double __date_4_byte_t::toTimeNowDiff()const
{
	time_t t = toTimeAsBcdYYMD();
	time_t now = time(NULL);
	return difftime(now,t);
}

void __date_time_7_byte_t::setToNow()
{
	struct tm tm;
	time_t t = time(NULL);
	localtime_r(&t,&tm);
	uint y = tm.tm_year;
	((uint8_t*)this)[0] = int2bcd(y/100);
	((uint8_t*)this)[1] = int2bcd(y%100);
	((uint8_t*)this)[2] = int2bcd(tm.tm_mon);
	((uint8_t*)this)[3] = int2bcd(tm.tm_mday);
	((uint8_t*)this)[4] = int2bcd(tm.tm_hour);
	((uint8_t*)this)[5] = int2bcd(tm.tm_min);
	((uint8_t*)this)[6] = int2bcd(tm.tm_sec);
}
uint __date_time_7_byte_t::getYear()const
{
	uint y = bcd2int(((uint8_t*)this)[0]);
	y = y*100 + bcd2int(((uint8_t*)this)[1]);
	return y;
}
uint __date_time_7_byte_t::getMouth()const
{
	return bcd2int(((uint8_t*)this)[2]);
}
uint __date_time_7_byte_t::getDate()const
{
	return bcd2int(((uint8_t*)this)[3]);
}
uint __date_time_7_byte_t::getHour()const
{
	return bcd2int(((uint8_t*)this)[4]);
}
uint __date_time_7_byte_t::getMunite()const
{
	return bcd2int(((uint8_t*)this)[5]);
}
uint __date_time_7_byte_t::getSecond()const
{
	return bcd2int(((uint8_t*)this)[6]);
}
time_t __date_time_7_byte_t::toTimeAsBcdYYMDHMS()const
{
	uint y = getYear();
	uint m = getMouth();
	uint d = getDate();
	uint H = getHour();
	uint M = getMunite();
	uint S = getSecond();
	struct tm tm;
	time_t t = time(NULL);
	localtime_r(&t,&tm);
	tm.tm_year = y-1900;
	tm.tm_mon = (m-1)%12;
	tm.tm_mday = d;
	tm.tm_hour = H%24;
	tm.tm_min = M%60;
	tm.tm_sec = S%60;
	if(tm.tm_mday<1 || tm.tm_mday>31)
		tm.tm_mday = 1;
	return mktime(&tm);
}
double __date_time_7_byte_t::toTimeDiffNow()const
{
	time_t t = toTimeAsBcdYYMDHMS();
	time_t now = time(NULL);
	return difftime(t,now);
}
double __date_time_7_byte_t::toTimeNowDiff()const
{
	time_t t = toTimeAsBcdYYMDHMS();
	time_t now = time(NULL);
	return difftime(now,t);
}



