#include "pch.h"
#include "lunar.h"

//
//  lunar.cpp
//  LunarCore
//
//  Created by Xiaoxuan Tang on 2/12/15.
//  Copyright (c) 2015 liwushuo. All rights reserved.

//  本次修改主要把std::string类型转换成Platform::String类型以便在UWP开发中使用。
//  The edition mainly changes the class std::string to Platform::String so that the lunar class can be used in the development of UWP.
//  Edited by Jingwei Tu on 2018/8/23.(2th Edition)

//	第三次修改为个人需要，删除不打算包含的功能。-涂经纬

//

#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <math.h>

#include "lunar.h"

/**
 *  农历1900-2100的润大小信息表
 */
static int32_t lunarInfo[] = { 0x04bd8,0x04ae0,0x0a570,0x054d5,0x0d260,0x0d950,0x16554,0x056a0,0x09ad0,0x055d2,//1900-1909
							  0x04ae0,0x0a5b6,0x0a4d0,0x0d250,0x1d255,0x0b540,0x0d6a0,0x0ada2,0x095b0,0x14977,//1910-1919
							  0x04970,0x0a4b0,0x0b4b5,0x06a50,0x06d40,0x1ab54,0x02b60,0x09570,0x052f2,0x04970,//1920-1929
							  0x06566,0x0d4a0,0x0ea50,0x06e95,0x05ad0,0x02b60,0x186e3,0x092e0,0x1c8d7,0x0c950,//1930-1939
							  0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557,//1940-1949
							  0x06ca0,0x0b550,0x15355,0x04da0,0x0a5b0,0x14573,0x052b0,0x0a9a8,0x0e950,0x06aa0,//1950-1959
							  0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0,//1960-1969
							  0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b6a0,0x195a6,//1970-1979
							  0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570,//1980-1989
							  0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0,//1990-1999
							  0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5,//2000-2009
							  0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930,//2010-2019
							  0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530,//2020-2029
							  0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45,//2030-2039
							  0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0,//2040-2049
							  /**Add By JJonline@JJonline.Cn**/
							  0x14b63,0x09370,0x049f8,0x04970,0x064b0,0x168a6,0x0ea50, 0x06b20,0x1a6c4,0x0aae0,//2050-2059
							  0x0a2e0,0x0d2e3,0x0c960,0x0d557,0x0d4a0,0x0da50,0x05d55,0x056a0,0x0a6d0,0x055d4,//2060-2069
							  0x052d0,0x0a9b8,0x0a950,0x0b4a0,0x0b6a6,0x0ad50,0x055a0,0x0aba4,0x0a5b0,0x052b0,//2070-2079
							  0x0b273,0x06930,0x07337,0x06aa0,0x0ad50,0x14b55,0x04b60,0x0a570,0x054e4,0x0d160,//2080-2089
							  0x0e968,0x0d520,0x0daa0,0x16aa6,0x056d0,0x04ae0,0x0a9d4,0x0a2d0,0x0d150,0x0f252,//2090-2099
							  0x0d520 };

/**
 *  公历每个月份的天数普通表
 */
static int32_t solarMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

/**
 *  天干地支之天干速查表
 */
static std::string Gan[] = { "\u7532","\u4e59","\u4e19","\u4e01","\u620a","\u5df1","\u5e9a","\u8f9b","\u58ec","\u7678" };

/**
 *  天干地支之地支速查表
 */
static std::string Zhi[] = { "\u5b50","\u4e11","\u5bc5","\u536f","\u8fb0","\u5df3","\u5348","\u672a","\u7533","\u9149","\u620c","\u4ea5" };

/**
 *  天干地支之地支速查表<=>生肖
 */
static std::string Animals[] = { "\u9f20","\u725b","\u864e","\u5154","\u9f99","\u86c7","\u9a6c","\u7f8a","\u7334","\u9e21","\u72d7","\u732a" };

/**
 *  24节气速查表
 */
static std::string solarTerm[] = { "\u5c0f\u5bd2","\u5927\u5bd2","\u7acb\u6625","\u96e8\u6c34","\u60ca\u86f0","\u6625\u5206","\u6e05\u660e","\u8c37\u96e8","\u7acb\u590f","\u5c0f\u6ee1","\u8292\u79cd","\u590f\u81f3","\u5c0f\u6691","\u5927\u6691","\u7acb\u79cb","\u5904\u6691","\u767d\u9732","\u79cb\u5206","\u5bd2\u9732","\u971c\u964d","\u7acb\u51ac","\u5c0f\u96ea","\u5927\u96ea","\u51ac\u81f3" };

/**
 *  1900-2100各年的24节气日期速查表
 */
static std::string sTermInfo[] = { "9778397bd097c36b0b6fc9274c91aa","97b6b97bd19801ec9210c965cc920e","97bcf97c3598082c95f8c965cc920f",
				"97bd0b06bdb0722c965ce1cfcc920f","b027097bd097c36b0b6fc9274c91aa","97b6b97bd19801ec9210c965cc920e",
				"97bcf97c359801ec95f8c965cc920f","97bd0b06bdb0722c965ce1cfcc920f","b027097bd097c36b0b6fc9274c91aa",
				"97b6b97bd19801ec9210c965cc920e","97bcf97c359801ec95f8c965cc920f",	"97bd0b06bdb0722c965ce1cfcc920f",
				"b027097bd097c36b0b6fc9274c91aa","9778397bd19801ec9210c965cc920e","97b6b97bd19801ec95f8c965cc920f",
				"97bd09801d98082c95f8e1cfcc920f","97bd097bd097c36b0b6fc9210c8dc2","9778397bd197c36c9210c9274c91aa",
				"97b6b97bd19801ec95f8c965cc920e","97bd09801d98082c95f8e1cfcc920f",	"97bd097bd097c36b0b6fc9210c8dc2",
				"9778397bd097c36c9210c9274c91aa","97b6b97bd19801ec95f8c965cc920e","97bcf97c3598082c95f8e1cfcc920f",
				"97bd097bd097c36b0b6fc9210c8dc2","9778397bd097c36c9210c9274c91aa","97b6b97bd19801ec9210c965cc920e",
				"97bcf97c3598082c95f8c965cc920f","97bd097bd097c35b0b6fc920fb0722","9778397bd097c36b0b6fc9274c91aa",
				"97b6b97bd19801ec9210c965cc920e","97bcf97c3598082c95f8c965cc920f",	"97bd097bd097c35b0b6fc920fb0722",
				"9778397bd097c36b0b6fc9274c91aa","97b6b97bd19801ec9210c965cc920e","97bcf97c359801ec95f8c965cc920f",
				"97bd097bd097c35b0b6fc920fb0722","9778397bd097c36b0b6fc9274c91aa","97b6b97bd19801ec9210c965cc920e",
				"97bcf97c359801ec95f8c965cc920f","97bd097bd097c35b0b6fc920fb0722","9778397bd097c36b0b6fc9274c91aa",
				"97b6b97bd19801ec9210c965cc920e","97bcf97c359801ec95f8c965cc920f",	"97bd097bd07f595b0b6fc920fb0722",
				"9778397bd097c36b0b6fc9210c8dc2","9778397bd19801ec9210c9274c920e","97b6b97bd19801ec95f8c965cc920f",
				"97bd07f5307f595b0b0bc920fb0722","7f0e397bd097c36b0b6fc9210c8dc2","9778397bd097c36c9210c9274c920e",
				"97b6b97bd19801ec95f8c965cc920f","97bd07f5307f595b0b0bc920fb0722","7f0e397bd097c36b0b6fc9210c8dc2",
				"9778397bd097c36c9210c9274c91aa","97b6b97bd19801ec9210c965cc920e","97bd07f1487f595b0b0bc920fb0722",
				"7f0e397bd097c36b0b6fc9210c8dc2","9778397bd097c36b0b6fc9274c91aa","97b6b97bd19801ec9210c965cc920e",
				"97bcf7f1487f595b0b0bb0b6fb0722","7f0e397bd097c35b0b6fc920fb0722",	"9778397bd097c36b0b6fc9274c91aa",
				"97b6b97bd19801ec9210c965cc920e","97bcf7f1487f595b0b0bb0b6fb0722","7f0e397bd097c35b0b6fc920fb0722",
				"9778397bd097c36b0b6fc9274c91aa","97b6b97bd19801ec9210c965cc920e","97bcf7f1487f531b0b0bb0b6fb0722",
				"7f0e397bd097c35b0b6fc920fb0722","9778397bd097c36b0b6fc9274c91aa","97b6b97bd19801ec9210c965cc920e",
				"97bcf7f1487f531b0b0bb0b6fb0722","7f0e397bd07f595b0b6fc920fb0722",	"9778397bd097c36b0b6fc9274c91aa",
				"97b6b97bd19801ec9210c9274c920e","97bcf7f0e47f531b0b0bb0b6fb0722","7f0e397bd07f595b0b0bc920fb0722",
				"9778397bd097c36b0b6fc9210c91aa","97b6b97bd197c36c9210c9274c920e","97bcf7f0e47f531b0b0bb0b6fb0722",
				"7f0e397bd07f595b0b0bc920fb0722","9778397bd097c36b0b6fc9210c8dc2","9778397bd097c36c9210c9274c920e",
				"97b6b7f0e47f531b0723b0b6fb0722","7f0e37f5307f595b0b0bc920fb0722",	"7f0e397bd097c36b0b6fc9210c8dc2",
				"9778397bd097c36b0b70c9274c91aa","97b6b7f0e47f531b0723b0b6fb0721","7f0e37f1487f595b0b0bb0b6fb0722",
				"7f0e397bd097c35b0b6fc9210c8dc2","9778397bd097c36b0b6fc9274c91aa","97b6b7f0e47f531b0723b0b6fb0721",
				"7f0e27f1487f595b0b0bb0b6fb0722","7f0e397bd097c35b0b6fc920fb0722",	"9778397bd097c36b0b6fc9274c91aa",
				"97b6b7f0e47f531b0723b0b6fb0721","7f0e27f1487f531b0b0bb0b6fb0722","7f0e397bd097c35b0b6fc920fb0722",
				"9778397bd097c36b0b6fc9274c91aa","97b6b7f0e47f531b0723b0b6fb0721","7f0e27f1487f531b0b0bb0b6fb0722",
				"7f0e397bd097c35b0b6fc920fb0722","9778397bd097c36b0b6fc9274c91aa","97b6b7f0e47f531b0723b0b6fb0721",
				"7f0e27f1487f531b0b0bb0b6fb0722","7f0e397bd07f595b0b0bc920fb0722",	"9778397bd097c36b0b6fc9274c91aa",
				"97b6b7f0e47f531b0723b0787b0721","7f0e27f0e47f531b0b0bb0b6fb0722","7f0e397bd07f595b0b0bc920fb0722",
				"9778397bd097c36b0b6fc9210c91aa","97b6b7f0e47f149b0723b0787b0721","7f0e27f0e47f531b0723b0b6fb0722",
				"7f0e397bd07f595b0b0bc920fb0722","9778397bd097c36b0b6fc9210c8dc2","977837f0e37f149b0723b0787b0721",
				"7f07e7f0e47f531b0723b0b6fb0722","7f0e37f5307f595b0b0bc920fb0722","7f0e397bd097c35b0b6fc9210c8dc2",
				"977837f0e37f14998082b0787b0721","7f07e7f0e47f531b0723b0b6fb0721","7f0e37f1487f595b0b0bb0b6fb0722",
				"7f0e397bd097c35b0b6fc9210c8dc2","977837f0e37f14998082b0787b06bd","7f07e7f0e47f531b0723b0b6fb0721",
				"7f0e27f1487f531b0b0bb0b6fb0722","7f0e397bd097c35b0b6fc920fb0722","977837f0e37f14998082b0787b06bd",
				"7f07e7f0e47f531b0723b0b6fb0721","7f0e27f1487f531b0b0bb0b6fb0722","7f0e397bd097c35b0b6fc920fb0722",
				"977837f0e37f14998082b0787b06bd","7f07e7f0e47f531b0723b0b6fb0721","7f0e27f1487f531b0b0bb0b6fb0722",
				"7f0e397bd07f595b0b0bc920fb0722","977837f0e37f14998082b0787b06bd","7f07e7f0e47f531b0723b0b6fb0721",
				"7f0e27f1487f531b0b0bb0b6fb0722","7f0e397bd07f595b0b0bc920fb0722",	"977837f0e37f14998082b0787b06bd",
				"7f07e7f0e47f149b0723b0787b0721","7f0e27f0e47f531b0b0bb0b6fb0722","7f0e397bd07f595b0b0bc920fb0722",
				"977837f0e37f14998082b0723b06bd","7f07e7f0e37f149b0723b0787b0721","7f0e27f0e47f531b0723b0b6fb0722",
				"7f0e397bd07f595b0b0bc920fb0722","977837f0e37f14898082b0723b02d5","7ec967f0e37f14998082b0787b0721",
				"7f07e7f0e47f531b0723b0b6fb0722","7f0e37f1487f595b0b0bb0b6fb0722","7f0e37f0e37f14898082b0723b02d5",
				"7ec967f0e37f14998082b0787b0721","7f07e7f0e47f531b0723b0b6fb0722","7f0e37f1487f531b0b0bb0b6fb0722",
				"7f0e37f0e37f14898082b0723b02d5","7ec967f0e37f14998082b0787b06bd","7f07e7f0e47f531b0723b0b6fb0721",
				"7f0e37f1487f531b0b0bb0b6fb0722","7f0e37f0e37f14898082b072297c35","7ec967f0e37f14998082b0787b06bd",
				"7f07e7f0e47f531b0723b0b6fb0721","7f0e27f1487f531b0b0bb0b6fb0722","7f0e37f0e37f14898082b072297c35",
				"7ec967f0e37f14998082b0787b06bd","7f07e7f0e47f531b0723b0b6fb0721",	"7f0e27f1487f531b0b0bb0b6fb0722",
				"7f0e37f0e366aa89801eb072297c35","7ec967f0e37f14998082b0787b06bd","7f07e7f0e47f149b0723b0787b0721",
				"7f0e27f1487f531b0b0bb0b6fb0722","7f0e37f0e366aa89801eb072297c35","7ec967f0e37f14998082b0723b06bd",
				"7f07e7f0e47f149b0723b0787b0721","7f0e27f0e47f531b0723b0b6fb0722","7f0e37f0e366aa89801eb072297c35",
				"7ec967f0e37f14998082b0723b06bd","7f07e7f0e37f14998083b0787b0721","7f0e27f0e47f531b0723b0b6fb0722",
				"7f0e37f0e366aa89801eb072297c35","7ec967f0e37f14898082b0723b02d5","7f07e7f0e37f14998082b0787b0721",
				"7f07e7f0e47f531b0723b0b6fb0722","7f0e36665b66aa89801e9808297c35",	"665f67f0e37f14898082b0723b02d5",
				"7ec967f0e37f14998082b0787b0721","7f07e7f0e47f531b0723b0b6fb0722",	"7f0e36665b66a449801e9808297c35",
				"665f67f0e37f14898082b0723b02d5","7ec967f0e37f14998082b0787b06bd","7f07e7f0e47f531b0723b0b6fb0721",
				"7f0e36665b66a449801e9808297c35","665f67f0e37f14898082b072297c35",	"7ec967f0e37f14998082b0787b06bd",
				"7f07e7f0e47f531b0723b0b6fb0721","7f0e26665b66a449801e9808297c35",	"665f67f0e37f1489801eb072297c35",
				"7ec967f0e37f14998082b0787b06bd","7f07e7f0e47f531b0723b0b6fb0721",	"7f0e27f1487f531b0b0bb0b6fb0722" };

/**
 *  数字转中文速查表
 */
static std::string nStr1[] = { "\u65e5","\u4e00","\u4e8c","\u4e09","\u56db","\u4e94","\u516d","\u4e03","\u516b","\u4e5d","\u5341" };

/**
 *  日期转农历称呼速查表
 */
static std::string nStr2[] = { "\u521d","\u5341","\u5eff","\u5345" };

/**
 *  月份转农历称呼速查表
 */
static std::string nStr3[] = { "\u6b63","\u4e8c","\u4e09","\u56db","\u4e94","\u516d","\u4e03","\u516b","\u4e5d","\u5341","\u51ac","\u814a" };

int32_t Lunar::lYearDays(int32_t year)
{
	int32_t i, sum = 348;
	for (i = 0x8000; i > 0x8; i >>= 1)
	{
		sum += (lunarInfo[year - 1900] & i) ? 1 : 0;
	}
	return(sum + this->leapDays(year));
}

int32_t Lunar::leapMonth(int32_t year)
{
	return(lunarInfo[year - 1900] & 0xf);
}

int32_t Lunar::leapDays(int32_t year)
{
	if (this->leapMonth(year))
	{
		return(lunarInfo[year - 1900] & 0x10000) ? 30 : 29;
	}
	return 0;
}

int32_t Lunar::monthDays(int32_t year, int32_t month)
{
	if (month > 12 || month < 1)
	{
		return -1; //月份参数从1至12，参数错误返回-1
	}

	return (lunarInfo[year - 1900] & (0x10000 >> month)) ? 30 : 29;
}

int32_t Lunar::solarDays(int32_t year, int32_t month)
{
	if (month > 12 || month < 1) { return -1; } //若参数错误 返回-1

	int32_t ms = month - 1;
	if (ms == 1)
	{ //2月份的闰平规律测算后确认返回28或29
		return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) ? 29 : 28;
	}
	else
	{
		return(solarMonth[ms]);
	}
}

std::string Lunar::toGanZhi(int32_t offset)
{
	return(Gan[offset % 10] + Zhi[offset % 12]);
}

int32_t Lunar::getTerm(int32_t year, int32_t number)
{
	if (year < 1900 || year > 2100) { return -1; }
	if (number < 1 || number > 24) { return -1; }

	std::string _table = sTermInfo[year - 1900];
	std::vector< std::string > _info = std::vector< std::string >();

	for (int32_t i = 0; i < 6; i++) {
		std::string tmp = _table.substr(i * 5, 5);
		tmp = "0x" + tmp;
		int32_t number = (int32_t)strtol(tmp.c_str(), NULL, 16);
		_info.push_back(std::to_string(number));
	}

	std::vector< int32_t > _calday = std::vector< int32_t >();

	for (int32_t i = 0; i < 6; i++) {
		_calday.push_back(std::stoi(_info[i].substr(0, 1)));
		_calday.push_back(std::stoi(_info[i].substr(1, 2)));
		_calday.push_back(std::stoi(_info[i].substr(3, 1)));
		_calday.push_back(std::stoi(_info[i].substr(4, 2)));
	}

	return _calday[number - 1];
}

std::string Lunar::toChinaMonth(int32_t month)
{
	if (month > 12 || month < 1) { return ""; } //若参数错误 返回""
	std::string s = nStr3[month - 1];
	s += "\u6708";//加上月字
	return s;
}

std::string Lunar::toChinaDay(int32_t day)
{
	std::string s;

	switch (day) {
	case 10:
		s = "\u521d\u5341"; break;
	case 20:
		s = "\u4e8c\u5341"; break;
		break;
	case 30:
		s = "\u4e09\u5341"; break;
		break;
	default:

		s = nStr2[(int32_t)floor(day / 10)];
		s += nStr1[day % 10];
	}

	return(s);
}

std::string Lunar::getAnimal(int32_t year)
{
	return Animals[(year - 4) % 12];
}

int32_t Lunar::deltaDaysWith19000131(int32_t year, int32_t month, int32_t day)
{
	if (year == 1900)
	{
		int32_t s = 0;
		for (int32_t m = 2; m < month; m++) {
			s += this->solarDays(year, m);
		}

		if (month != 1)
			s += day;

		return s;
	}
	else
	{
		int32_t s = 365 - 31;
		for (int32_t i = 1901; i < year; i++)
		{
			s += ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) ? 366 : 365;
		}

		if (month != 1)
		{
			for (int32_t i = 1; i < month; i++) {
				s += this->solarDays(year, i);
			}
		}

		s += day;

		return s;
	}
}

LunarObj* Lunar::solar2lunar(int32_t year, int32_t month, int32_t day)
{
	if (year < 1900 || year > 2100) return NULL;
	if (year == 1900 && month == 1 && day < 31) return NULL;

	int32_t i = 0, temp = 0, leap = 0;

	int32_t offset = this->deltaDaysWith19000131(year, month, day);

	for (i = 1900; i < 2101 && offset > 0; i++)
	{
		temp = lYearDays(i);
		offset -= temp;
	}

	if (offset < 0) {
		offset += temp;
		i--;
	}



	int32_t lunarYear = i;
	leap = this->leapMonth(i);

	bool isLeap = false;

	for (i = 1; i < 13 && offset > 0; i++)
	{
		if (leap > 0 && i == (leap + 1) && isLeap == false)
		{
			--i;
			isLeap = true;
			temp = this->leapDays(lunarYear);
		}
		else
		{
			temp = this->monthDays(lunarYear, i);
		}

		if (isLeap == true && i == (leap + 1))
		{
			isLeap = false;
		}

		offset -= temp;
	}

	if (offset == 0 && leap > 0 && i == leap + 1)
	{
		if (isLeap) {
			isLeap = false;
		}
		else
		{
			isLeap = true;
			--i;
		}
	}

	if (offset < 0)
	{
		offset += temp;
		--i;
	}

	int32_t lunarMonth = i;
	int32_t lunarDay = (int32_t)offset + 1;

	int32_t sm = month - 1;
	int32_t term3 = this->getTerm(lunarYear, 3);



	int32_t firstNode = this->getTerm(year, month * 2 - 1);
	int32_t secondNode = this->getTerm(year, month * 2);


	bool isTerm = false;
	std::string Term = "";

	if (firstNode == day)
	{
		isTerm = true;
		Term = solarTerm[month * 2 - 2];
	}

	if (secondNode == day)
	{
		isTerm = true;
		Term = solarTerm[month * 2 - 1];
	}

	int32_t dayCyclical = (int32_t)(deltaDaysWith19000131(year, sm + 1, 1) + 30) + 10;


	LunarObj* obj = new LunarObj;

	obj->lunarYear = lunarYear;
	obj->lunarMonth = lunarMonth;
	obj->lunarDay = lunarDay;



	//转成Platform::String；有bug 

	//可放在类外（mainpage）生成生肖
	switch (obj->solarYear % 12)
	{
	case 0:obj->animalString = "猴"; break;
	case 1:obj->animalString = "鸡"; break;
	case 2:obj->animalString = "狗"; break;
	case 3:obj->animalString = "猪"; break;
	case 4:obj->animalString = "鼠"; break;
	case 5:obj->animalString = "牛"; break;
	case 6:obj->animalString = "虎"; break;
	case 7:obj->animalString = "兔"; break;
	case 8:obj->animalString = "龙"; break;
	case 9:obj->animalString = "蛇"; break;
	case 10:obj->animalString = "马"; break;
	case 11:obj->animalString = "羊"; break;

	default:
		break;
	}

	switch (obj->lunarMonth)
	{
	case 1:obj->lunarMonthChineseNameString = "一月"; break;
	case 2:obj->lunarMonthChineseNameString = "二月"; break;
	case 3:obj->lunarMonthChineseNameString = "三月"; break;
	case 4:obj->lunarMonthChineseNameString = "四月"; break;
	case 5:obj->lunarMonthChineseNameString = "五月"; break;
	case 6:obj->lunarMonthChineseNameString = "六月"; break;
	case 7:obj->lunarMonthChineseNameString = "七月"; break;
	case 8:obj->lunarMonthChineseNameString = "八月"; break;
	case 9:obj->lunarMonthChineseNameString = "九月"; break;
	case 10:obj->lunarMonthChineseNameString = "十月"; break;
	case 11:obj->lunarMonthChineseNameString = "十一月"; break;
	case 12:obj->lunarMonthChineseNameString = "十二月"; break;
	default:
		break;
	}

	switch (obj->lunarDay)
	{
	case 1:obj->lunarDayChineseNameString = "初一"; break;
	case 2:obj->lunarDayChineseNameString = "初二"; break;
	case 3:obj->lunarDayChineseNameString = "初三"; break;
	case 4:obj->lunarDayChineseNameString = "初四"; break;
	case 5:obj->lunarDayChineseNameString = "初五"; break;
	case 6:obj->lunarDayChineseNameString = "初六"; break;
	case 7:obj->lunarDayChineseNameString = "初七"; break;
	case 8:obj->lunarDayChineseNameString = "初八"; break;
	case 9:obj->lunarDayChineseNameString = "初九"; break;
	case 10:obj->lunarDayChineseNameString = "初十"; break;
	case 11:obj->lunarDayChineseNameString = "十一"; break;
	case 12:obj->lunarDayChineseNameString = "十二"; break;
	case 13:obj->lunarDayChineseNameString = "十三"; break;
	case 14:obj->lunarDayChineseNameString = "十四"; break;
	case 15:obj->lunarDayChineseNameString = "十五"; break;
	case 16:obj->lunarDayChineseNameString = "十六"; break;
	case 17:obj->lunarDayChineseNameString = "十七"; break;
	case 18:obj->lunarDayChineseNameString = "十八"; break;
	case 19:obj->lunarDayChineseNameString = "十九"; break;
	case 20:obj->lunarDayChineseNameString = "二十"; break;
	case 21:obj->lunarDayChineseNameString = "廿一"; break;
	case 22:obj->lunarDayChineseNameString = "廿二"; break;
	case 23:obj->lunarDayChineseNameString = "廿三"; break;
	case 24:obj->lunarDayChineseNameString = "廿四"; break;
	case 25:obj->lunarDayChineseNameString = "廿五"; break;
	case 26:obj->lunarDayChineseNameString = "廿六"; break;
	case 27:obj->lunarDayChineseNameString = "廿七"; break;
	case 28:obj->lunarDayChineseNameString = "廿八"; break;
	case 29:obj->lunarDayChineseNameString = "廿九"; break;
	case 30:obj->lunarDayChineseNameString = "三十"; break;

	default:
		break;
	}

	obj->solarYear = year;
	obj->solarMonth = month;
	obj->solarDay = day;

	obj->isLeap = isLeap;
	obj->term = Term;
	if (Term == "立春")obj->termString = "立春";
	else if (Term == "雨水")obj->termString = "雨水";
	else if (Term == "惊蛰")obj->termString = "惊蛰";
	else if (Term == "春分")obj->termString = "春分";
	else if (Term == "清明")obj->termString = "清明";
	else if (Term == "谷雨")obj->termString = "谷雨";
	else if (Term == "立夏")obj->termString = "立夏";
	else if (Term == "小满")obj->termString = "小满";
	else if (Term == "芒种")obj->termString = "芒种";
	else if (Term == "夏至")obj->termString = "夏至";
	else if (Term == "小暑")obj->termString = "小暑";
	else if (Term == "大暑")obj->termString = "大暑";
	else if (Term == "立秋")obj->termString = "立秋";
	else if (Term == "处暑")obj->termString = "处暑";
	else if (Term == "白露")obj->termString = "白露";
	else if (Term == "秋分")obj->termString = "秋分";
	else if (Term == "寒露")obj->termString = "寒露";
	else if (Term == "霜降")obj->termString = "霜降";
	else if (Term == "立冬")obj->termString = "立冬";
	else if (Term == "小雪")obj->termString = "小雪";
	else if (Term == "大雪")obj->termString = "大雪";
	else if (Term == "冬至")obj->termString = "冬至";
	else if (Term == "小寒")obj->termString = "小寒";
	else if (Term == "大寒")obj->termString = "大寒";


	obj->isTerm = isTerm;


	//节日有
	//农历：腊八、除夕、春节、元宵节、清明节、端午节、七夕、中秋节、重阳节
	//公历：元旦、情人节、植树节、劳动节、青年节、母亲节、儿童节、建党节、建军节、教师节、国庆节、圣诞节
	//星期：母亲节、父亲节、

	//农历
	{
		if (obj->lunarMonth == 12)
			switch (obj->lunarDay)
			{
			case 8:obj->isFestival = 1; obj->FestivalString += "\n腊八"; break;
			case 30:obj->isFestival = 1; obj->FestivalString += "\n除夕"; break;
			}
		else if (obj->lunarMonth == 1)
			switch (obj->lunarDay)
			{
			case 1:obj->isFestival = 1; obj->FestivalString += "\n春节"; break;
			case 15:obj->isFestival = 1; obj->FestivalString += "\n元宵节"; break;
			}
		else if (obj->lunarMonth == 5 && obj->lunarDay == 5) { obj->isFestival = 1; obj->FestivalString += "\n端午节"; }
		else if (obj->lunarMonth == 7 && obj->lunarDay == 7) { obj->isFestival = 1; obj->FestivalString += "\n七夕"; }
		else if (obj->lunarMonth == 8 && obj->lunarDay == 15) { obj->isFestival = 1; obj->FestivalString += "\n中秋节"; }
		else if (obj->lunarMonth == 9 && obj->lunarDay == 9) { obj->isFestival = 1; obj->FestivalString += "\n重阳节"; }
	}
	//公历
	{
		if (obj->solarMonth == 1 && obj->solarDay == 1) { obj->isFestival = 1; obj->FestivalString += "\n元旦"; }
		else if (obj->solarMonth == 2 && obj->solarDay == 14) { obj->isFestival = 1; obj->FestivalString += "\n情人节"; }
		else if (obj->solarMonth == 3 && obj->solarDay == 12) { obj->isFestival = 1; obj->FestivalString += "\n植树节"; }
		else if (obj->solarMonth == 5)
			switch (obj->lunarDay)
			{ 
			case 1:obj->isFestival = 1; obj->FestivalString += "\n劳动节"; break;
			case 12:obj->isFestival = 1; obj->FestivalString += "\n青年节"; break;
			}
		else if (obj->solarMonth == 6 && obj->solarDay == 1) { obj->isFestival = 1; obj->FestivalString += "\n儿童节"; }
		else if (obj->solarMonth == 7 && obj->solarDay == 1) { obj->isFestival = 1; obj->FestivalString += "\n建党节"; }
		else if (obj->solarMonth == 8 && obj->solarDay == 1) { obj->isFestival = 1; obj->FestivalString += "\n建军节"; }
		else if (obj->solarMonth == 9 && obj->solarDay == 10) { obj->isFestival = 1; obj->FestivalString += "\n教师节"; }
		else if (obj->solarMonth == 10 && obj->solarDay == 1) { obj->isFestival = 1; obj->FestivalString += "\n国庆节"; }
		else if (obj->solarMonth == 12 && obj->solarDay == 25) { obj->isFestival = 1; obj->FestivalString += "\n圣诞节"; }
	}
	/*//母亲节、父亲节
	if (obj->solarMonth == 5 && obj->weekNumber) { obj->isFestival = 1; obj->FestivalString += "\n建党节"; }*/
	return obj;
}
