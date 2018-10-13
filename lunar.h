//
//  lunar.h
//  LunarCore
//
//  Created by Xiaoxuan Tang on 2/12/15.
//  Copyright (c) 2015 liwushuo. All rights reserved.

//  �����޸���Ҫ��std::string����ת����Platform::String�����Ա���UWP������ʹ�á�
//  The edition mainly changes the class std::string to Platform::String so that the lunar class can be used in the development of UWP.
//  Edited by Jingwei Tu on 2018/8/23.(2th Edition)

//	�������޸�Ϊ������Ҫ��ɾ������������Ĺ���,������һЩ���ա�-Ϳ��γ

//

#ifndef LunarCore_lunar_h
#define LunarCore_lunar_h

#include <iostream>
#include <stdio.h>

struct LunarObj {
	int32_t lunarYear, lunarMonth, lunarDay, solarYear, solarMonth, solarDay, weekNumber;
	std::string term;
	Platform::String^ animalString, ^lunarMonthChineseNameString, ^lunarDayChineseNameString, ^termString, ^weekChineseNameString, ^FestivalString;

	bool isToday, isLeap, isTerm, isFestival = 0;
};

class DateInfo {
public:
	int SolarYear;
	int SolarMonth;
	int SoloarDay;
	Platform::String^ LunarMonthString;
	Platform::String^ LunarDayString;
private:

};

class Lunar {

public:
	/**
	 *  ����ũ�� year ��һ�����������
	 *  @param year(1900~2100) ũ����
	 *  @return ������
	 */
	int32_t lYearDays(int32_t year);

	/**
	 *  ����ũ�� year ������ʱ�ĸ��£��� year ��û������ �򷵻�0
	 *  @param year(1900~2100) ũ����
	 *  @return 0-12
	 */
	int32_t leapMonth(int32_t year);

	/**
	 *  ����ũ�� year �� ���µ����� ������û�������򷵻� 0
	 *  @param year(1900~2100) ũ����
	 *  @return 0/29/30
	 */
	int32_t leapDays(int32_t year);

	/**
	 *  ����ũ�� year �� month �� (������) �������������� month Ϊ����ʱ��������ʹ�� leapDays ����
	 *  @param year(1900~2100)  ũ����
	 *  @param month(1~12) ũ����
	 *  @return -1/29/30
	 */
	int32_t monthDays(int32_t year, int32_t month);

	/**
	 *  ���ع����� year �� month �µ�����
	 *  @param year(1900~2100)  ������
	 *  @param month(1~12) ������
	 *  @return -1/28/29/30/31
	 */

	int32_t solarDays(int32_t year, int32_t month);

	/**
	 *  ���� offset ƫ���������ظ�֧
	 *  @param offset offset ��Լ��ӵ�ƫ����
	 *  @return �����ָ���
	 */
	std::string toGanZhi(int32_t offset);

	/**
	 *  ���빫����� year ��ø���� number �������Ĺ�������
	 *  @param year(1~24)   ������
	 *  @param number(1~24) ��ʮ�Ľ����еĵڼ������� ; �� number = 1 (С��) ����
	 *  @return һ�����֣���������
	 */
	int32_t getTerm(int32_t year, int32_t number);

	/**
	 *  ����ũ�������·ݷ��غ���ͨ�ױ�ʾ��
	 *  @param month(1~12) ũ����
	 *  @return �����ַ���
	 */
	std::string toChinaMonth(int32_t month);

	/**
	 *  ����ũ���������ַ��غ��ֱ�ʾ��
	 *  @param day(1~30) ũ����
	 *  @return �����ַ���
	 */
	std::string toChinaDay(int32_t day);

	/**
	 *  �����Фת����ע�����ת������Ф�ֽ���������
	 *  @param year(1900~2100) ũ����
	 *  @return �����ַ���
	 */
	std::string getAnimal(int32_t year);

	int32_t deltaDaysWith19000131(int32_t year, int32_t month, int32_t day);

	/**
	 *  ���빫�������ջ����ϸ�Ĺ���ũ����Ϣ����������1900.1.31~2100.12.31
	 *  @param year  ������
	 *  @param month ������
	 *  @param day   ������
	 *  @return obj
	 */
	LunarObj* solar2lunar(int32_t year, int32_t month, int32_t day);

};

#endif
