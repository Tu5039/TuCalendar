//
// MonthView.xaml.cpp
// MonthView 类的实现
//

#include "pch.h"
#include "MonthView.xaml.h"

using namespace TuCalendar;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

MonthView::MonthView()
{
	InitializeComponent();

	CalendarOnShow->Month = calendar->Month;

	SelectedYear->SelectedIndex = SelectedDate->Year - 1900;
	SelectedMonth->SelectedIndex = SelectedDate->Month - 1;
	SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	showday();
}
void TuCalendar::MonthView::showday()
{
	int n = 0;
	CalendarOnShow->Year = SelectedDate->Year;
	CalendarOnShow->Month = SelectedDate->Month;
	CalendarOnShow->Day = 1;



	obj = lunar.solar2lunar(CalendarOnShow->Year, CalendarOnShow->Month, CalendarOnShow->Day);

	x = GetDayOfWeek(CalendarOnShow);

	CalendarOnShow->Day = CalendarOnShow->LastDayInThisMonth;

	a = GetDayOfWeek(CalendarOnShow);
	//calendar->Day = 1;

	//补充前面
	{
		CalendarOnShow->AddMonths(-1);
		CalendarOnShow->Day = CalendarOnShow->LastDayInThisMonth;

		switch (x)
		{
		case 6:	FillprevBlank(Fri0, LunarFri0, CalendarOnShow);
		case 5:	FillprevBlank(Thur0, LunarThur0, CalendarOnShow);
		case 4:	FillprevBlank(Wed0, LunarWed0, CalendarOnShow);
		case 3:	FillprevBlank(Tue0, LunarTue0, CalendarOnShow);
		case 2:	FillprevBlank(Mon0, LunarMon0, CalendarOnShow);
		case 1:	FillprevBlank(Sun0, LunarSun0, CalendarOnShow);
		case 0:
		default:
			CalendarOnShow->AddMonths(1);
			CalendarOnShow->Day = CalendarOnShow->FirstDayInThisMonth;
			break;
		}
	}

	//本月
	while (n != 6)
	{
		n = (CalendarOnShow->Day + x - 1) / 7;
		if (CalendarOnShow->DayOfWeekAsString() == "星期日")Sunday(n);
		else if (CalendarOnShow->DayOfWeekAsString() == "星期一")Monday(n);
		else if (CalendarOnShow->DayOfWeekAsString() == "星期二")Tuesday(n);
		else if (CalendarOnShow->DayOfWeekAsString() == "星期三")Wednesday(n);
		else if (CalendarOnShow->DayOfWeekAsString() == "星期四")Thursday(n);
		else if (CalendarOnShow->DayOfWeekAsString() == "星期五")Friday(n);
		else if (CalendarOnShow->DayOfWeekAsString() == "星期六")Saturday(n);
		if (CalendarOnShow->Day == CalendarOnShow->LastDayInThisMonth)
			break;
		else
		{
			CalendarOnShow->AddDays(1);
			obj = lunar.solar2lunar(CalendarOnShow->Year, CalendarOnShow->Month, CalendarOnShow->Day);
		}
	}

	//补充后面
	{
		if (CalendarOnShow->DayOfWeekAsString() == "星期日")a = 0;
		else if (CalendarOnShow->DayOfWeekAsString() == "星期一")a = 1;
		else if (CalendarOnShow->DayOfWeekAsString() == "星期二")a = 2;
		else if (CalendarOnShow->DayOfWeekAsString() == "星期三")a = 3;
		else if (CalendarOnShow->DayOfWeekAsString() == "星期四")a = 4;
		else if (CalendarOnShow->DayOfWeekAsString() == "星期五")a = 5;
		else if (CalendarOnShow->DayOfWeekAsString() == "星期六")a = 6;
		if (CalendarOnShow->Month == 12)
		{
			CalendarOnShow->Year = CalendarOnShow->Year + 1;
			CalendarOnShow->Month = 1;
		}
		else CalendarOnShow->Month = CalendarOnShow->Month + 1;
		CalendarOnShow->Day = 1;
		if ((n == 3) && (a == 6))
		{
			FillnextBlank(Sun4, LunarSun4, CalendarOnShow);
			a = 0;
			++n;
		}
		if (((n == 4) && (a != 6)))
		{
			switch (a)
			{
			case 0:FillnextBlank(Mon4, LunarMon4, CalendarOnShow);
			case 1:FillnextBlank(Tue4, LunarTue4, CalendarOnShow);
			case 2:FillnextBlank(Wed4, LunarWed4, CalendarOnShow);
			case 3:FillnextBlank(Thur4, LunarThur4, CalendarOnShow);
			case 4:FillnextBlank(Fri4, LunarFri4, CalendarOnShow);
			case 5:FillnextBlank(Sat4, LunarSat4, CalendarOnShow);
			case 6:FillnextBlank(Sun5, LunarSun5, CalendarOnShow);
			default:++n; a = 0;
				break;
			}
		}
		if (((n == 4) && (a == 6)) || ((n == 5) && (a != 6)))
		{
			switch (a)
			{
			case 0:FillnextBlank(Mon5, LunarMon5, CalendarOnShow);
			case 1:FillnextBlank(Tue5, LunarTue5, CalendarOnShow);
			case 2:FillnextBlank(Wed5, LunarWed5, CalendarOnShow);
			case 3:FillnextBlank(Thur5, LunarThur5, CalendarOnShow);
			case 4:FillnextBlank(Fri5, LunarFri5, CalendarOnShow);
			case 5:FillnextBlank(Sat5, LunarSat5, CalendarOnShow);
			case 6:
			default:
				CalendarOnShow->AddMonths(-1);
				break;
			}
		}
	}
}

int TuCalendar::MonthView::GetDayOfWeek(Windows::Globalization::Calendar ^ calendar)
{
	if (calendar->DayOfWeekAsString() == "星期日")return 0;
	else if (calendar->DayOfWeekAsString() == "星期一")return 1;
	else if (calendar->DayOfWeekAsString() == "星期二")return 2;
	else if (calendar->DayOfWeekAsString() == "星期三")return 3;
	else if (calendar->DayOfWeekAsString() == "星期四")return 4;
	else if (calendar->DayOfWeekAsString() == "星期五")return 5;
	else if (calendar->DayOfWeekAsString() == "星期六")return 6;
	return -1;
}


void TuCalendar::MonthView::Sunday(int n)
{
	switch (n)
	{
	case 0:FillDay(Sun0, LunarSun0, CalendarOnShow); break;
	case 1:FillDay(Sun1, LunarSun1, CalendarOnShow); break;
	case 2:FillDay(Sun2, LunarSun2, CalendarOnShow); break;
	case 3:FillDay(Sun3, LunarSun3, CalendarOnShow); break;
	case 4:FillDay(Sun4, LunarSun4, CalendarOnShow); break;
	case 5:FillDay(Sun5, LunarSun5, CalendarOnShow); break;
	}
	if (CalendarOnShow->Day == SelectedDate->Day&&CalendarOnShow->Month == SelectedDate->Month&&CalendarOnShow->Year == SelectedDate->Year)
		SundayList->SelectedIndex = n;
}
void TuCalendar::MonthView::Monday(int n)
{
	switch (n)
	{
	case 0:FillDay(Mon0, LunarMon0, CalendarOnShow);break;
	case 1:FillDay(Mon1, LunarMon1, CalendarOnShow); break;
	case 2:FillDay(Mon2, LunarMon2, CalendarOnShow); break;
	case 3:FillDay(Mon3, LunarMon3, CalendarOnShow); break;
	case 4:FillDay(Mon4, LunarMon4, CalendarOnShow); break;
	case 5:FillDay(Mon5, LunarMon5, CalendarOnShow); break;
	}
	if (CalendarOnShow->Day == SelectedDate->Day&&CalendarOnShow->Month == SelectedDate->Month&&CalendarOnShow->Year == SelectedDate->Year)
		MondayList->SelectedIndex = n;
}
void TuCalendar::MonthView::Tuesday(int n)
{
	switch (n)
	{
	case 0:FillDay(Tue0, LunarTue0, CalendarOnShow); break;
	case 1:FillDay(Tue1, LunarTue1, CalendarOnShow); break;
	case 2:FillDay(Tue2, LunarTue2, CalendarOnShow); break;
	case 3:FillDay(Tue3, LunarTue3, CalendarOnShow); break;
	case 4:FillDay(Tue4, LunarTue4, CalendarOnShow); break;
	case 5:FillDay(Tue5, LunarTue5, CalendarOnShow); break;
	}
	if (CalendarOnShow->Day == SelectedDate->Day&&CalendarOnShow->Month == SelectedDate->Month&&CalendarOnShow->Year == SelectedDate->Year)
		TuesdayList->SelectedIndex = n;
}
void TuCalendar::MonthView::Wednesday(int n)
{
	switch (n)
	{
	case 0:FillDay(Wed0, LunarWed0, CalendarOnShow); break;
	case 1:FillDay(Wed1, LunarWed1, CalendarOnShow); break;
	case 2:FillDay(Wed2, LunarWed2, CalendarOnShow); break;
	case 3:FillDay(Wed3, LunarWed3, CalendarOnShow); break;
	case 4:FillDay(Wed4, LunarWed4, CalendarOnShow); break;
	case 5:FillDay(Wed5, LunarWed5, CalendarOnShow); break;
	}
	if (CalendarOnShow->Day == SelectedDate->Day&&CalendarOnShow->Month == SelectedDate->Month&&CalendarOnShow->Year == SelectedDate->Year)
		WednesdayList->SelectedIndex = n;
}
void TuCalendar::MonthView::Thursday(int n)
{
	switch (n)
	{
	case 0:FillDay(Thur0, LunarThur0, CalendarOnShow); break;
	case 1:FillDay(Thur1, LunarThur1, CalendarOnShow); break;
	case 2:FillDay(Thur2, LunarThur2, CalendarOnShow); break;
	case 3:FillDay(Thur3, LunarThur3, CalendarOnShow); break;
	case 4:FillDay(Thur4, LunarThur4, CalendarOnShow); break;
	case 5:FillDay(Thur5, LunarThur5, CalendarOnShow); break;
	}
	if (CalendarOnShow->Day == SelectedDate->Day&&CalendarOnShow->Month == SelectedDate->Month&&CalendarOnShow->Year == SelectedDate->Year)
		ThursdayList->SelectedIndex = n;
}
void TuCalendar::MonthView::Friday(int n)
{
	switch (n)
	{
	case 0:FillDay(Fri0, LunarFri0, CalendarOnShow); break;
	case 1:FillDay(Fri1, LunarFri1, CalendarOnShow); break;
	case 2:FillDay(Fri2, LunarFri2, CalendarOnShow); break;
	case 3:FillDay(Fri3, LunarFri3, CalendarOnShow); break;
	case 4:FillDay(Fri4, LunarFri4, CalendarOnShow); break;
	case 5:FillDay(Fri5, LunarFri5, CalendarOnShow); break;
	}
	if (CalendarOnShow->Day == SelectedDate->Day&&CalendarOnShow->Month == SelectedDate->Month&&CalendarOnShow->Year == SelectedDate->Year)
		FridayList->SelectedIndex = n;
}
void TuCalendar::MonthView::Saturday(int n)
{
	switch (n)
	{
	case 0:FillDay(Sat0, LunarSat0, CalendarOnShow); break;
	case 1:FillDay(Sat1, LunarSat1, CalendarOnShow); break;
	case 2:FillDay(Sat2, LunarSat2, CalendarOnShow); break;
	case 3:FillDay(Sat3, LunarSat3, CalendarOnShow); break;
	case 4:FillDay(Sat4, LunarSat4, CalendarOnShow); break;
	case 5:FillDay(Sat5, LunarSat5, CalendarOnShow); break;
	}
	if (CalendarOnShow->Day == SelectedDate->Day&&CalendarOnShow->Month == SelectedDate->Month&&CalendarOnShow->Year == SelectedDate->Year)
		SaturdayList->SelectedIndex = n;
}

void TuCalendar::MonthView::FillprevBlank(Windows::UI::Xaml::Controls::TextBlock ^ textblock1, Windows::UI::Xaml::Controls::TextBlock ^ textblock2, Windows::Globalization::Calendar ^ calendar)
{
	obj = lunar.solar2lunar(calendar->Year, calendar->Month, calendar->Day);
	textblock1->Text = calendar->DayAsPaddedString(1);
	if (obj->lunarDayChineseNameString == "初一")textblock2->Text = obj->lunarMonthChineseNameString;
	else textblock2->Text = obj->lunarDayChineseNameString;
	if (obj->isTerm)textblock2->Text += "\n" + obj->termString;
	if (obj->isFestival)textblock2->Text += obj->FestivalString;
	calendar->AddDays(-1);
}
void TuCalendar::MonthView::FillnextBlank(Windows::UI::Xaml::Controls::TextBlock ^ textblock1, Windows::UI::Xaml::Controls::TextBlock ^ textblock2, Windows::Globalization::Calendar ^ calendar)
{
	obj = lunar.solar2lunar(calendar->Year, calendar->Month, calendar->Day);
	textblock1->Text = calendar->DayAsPaddedString(1);
	if (obj->lunarDayChineseNameString == "初一")textblock2->Text = obj->lunarMonthChineseNameString;
	else textblock2->Text = obj->lunarDayChineseNameString;
	if (obj->isTerm)textblock2->Text += "\n" + obj->termString;
	if (obj->isFestival)textblock2->Text += obj->FestivalString;
	calendar->AddDays(1);
}
void TuCalendar::MonthView::FillDay(Windows::UI::Xaml::Controls::TextBlock ^ textblock1, Windows::UI::Xaml::Controls::TextBlock ^ textblock2, Windows::Globalization::Calendar ^ calendar)
{
	textblock1->Text = CalendarOnShow->DayAsPaddedString(1);
	if (obj->lunarDayChineseNameString == "初一")textblock2->Text = obj->lunarMonthChineseNameString;
	else textblock2->Text = obj->lunarDayChineseNameString;
	if (obj->isTerm)textblock2->Text += "\n" + obj->termString;
	if (obj->isFestival)textblock2->Text += obj->FestivalString;
}

void TuCalendar::MonthView::SundayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Month = CalendarOnShow->Month;
	if (SundayList->SelectedIndex != -1)
	{
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;

		int tmp = SundayList->SelectedIndex * 7 + 1 - x + 0;
		if (tmp <= SelectedDate->LastDayInThisMonth&&tmp >= 1)
			SelectedDate->Day = tmp;
		else if (tmp <= 0)
		{

			if (CalendarOnShow->Month == 1)
			{
				CalendarOnShow->Year--;
				CalendarOnShow->Month = 12;
				SelectedDate->Year = CalendarOnShow->Year;
				SelectedDate->Month = CalendarOnShow->Month;
			}
			else SelectedDate->Month = CalendarOnShow->Month - 1;
			SelectedDate->Day = tmp + SelectedDate->LastDayInThisMonth;
		}
		else if (tmp > SelectedDate->LastDayInThisMonth)
		{
			SelectedDate->Day = tmp - SelectedDate->LastDayInThisMonth;

			if (SelectedDate->Month == 12) { SelectedDate->Year++; SelectedDate->Month = 1; }
			else SelectedDate->Month++;
			CalendarOnShow->Day = CalendarOnShow->FirstDayInThisMonth;
		}
		SelectedYear->SelectedIndex = SelectedDate->Year - 1900;
		SelectedMonth->SelectedIndex = SelectedDate->Month - 1;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}

}
void TuCalendar::MonthView::MondayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Month = CalendarOnShow->Month;
	if (MondayList->SelectedIndex != -1)
	{
		SundayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = MondayList->SelectedIndex * 7 + 1 - x + 1;
		if (tmp <= SelectedDate->LastDayInThisMonth&&tmp >= 1)
			SelectedDate->Day = tmp;
		else if (tmp <= 0)
		{
			if (CalendarOnShow->Month == 1)
			{
				CalendarOnShow->Year--;
				CalendarOnShow->Month = 12;
				SelectedDate->Year = CalendarOnShow->Year;
				SelectedDate->Month = CalendarOnShow->Month;
			}
			else SelectedDate->Month = CalendarOnShow->Month - 1;
			SelectedDate->Day = tmp + SelectedDate->LastDayInThisMonth;
		}
		else if (tmp > SelectedDate->LastDayInThisMonth)
		{
			SelectedDate->Day = tmp - SelectedDate->LastDayInThisMonth;
			if (SelectedDate->Month == 12) { SelectedDate->Year++; SelectedDate->Month = 1; }
			else SelectedDate->Month++;;
		}
		SelectedYear->SelectedIndex = SelectedDate->Year - 1900;
		SelectedMonth->SelectedIndex = SelectedDate->Month - 1;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}

}
void TuCalendar::MonthView::TuesdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Month = CalendarOnShow->Month;
	if (TuesdayList->SelectedIndex != -1)
	{
		SundayList->SelectedIndex = -1;
		MondayList->SelectedIndex = -1;

		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = TuesdayList->SelectedIndex * 7 + 1 - x + 2;
		if (tmp <= SelectedDate->LastDayInThisMonth&&tmp >= 1)
			SelectedDate->Day = tmp;
		else if (tmp <= 0)
		{
			if (CalendarOnShow->Month == 1)
			{
				CalendarOnShow->Year--;
				CalendarOnShow->Month = 12;
				SelectedDate->Year = CalendarOnShow->Year;
				SelectedDate->Month = CalendarOnShow->Month;
			}
			else SelectedDate->Month = CalendarOnShow->Month - 1;
			SelectedDate->Day = tmp + SelectedDate->LastDayInThisMonth;
		}
		else if (tmp > SelectedDate->LastDayInThisMonth)
		{
			SelectedDate->Day = tmp - SelectedDate->LastDayInThisMonth;
			if (SelectedDate->Month == 12) { SelectedDate->Year++; SelectedDate->Month = 1; }
			else SelectedDate->Month++;;
		}
		SelectedYear->SelectedIndex = SelectedDate->Year - 1900;
		SelectedMonth->SelectedIndex = SelectedDate->Month - 1;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}

}
void TuCalendar::MonthView::WednesdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Month = CalendarOnShow->Month;
	if (WednesdayList->SelectedIndex != -1)
	{
		SundayList->SelectedIndex = -1;
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;

		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = WednesdayList->SelectedIndex * 7 + 1 - x + 3;
		if (tmp <= SelectedDate->LastDayInThisMonth&&tmp >= 1)
			SelectedDate->Day = tmp;
		else if (tmp <= 0)
		{
			if (CalendarOnShow->Month == 1)
			{
				CalendarOnShow->Year--;
				CalendarOnShow->Month = 12;
				SelectedDate->Year = CalendarOnShow->Year;
				SelectedDate->Month = CalendarOnShow->Month;
			}
			else SelectedDate->Month = CalendarOnShow->Month - 1;
			SelectedDate->Day = tmp + SelectedDate->LastDayInThisMonth;
		}
		else if (tmp > SelectedDate->LastDayInThisMonth)
		{
			SelectedDate->Day = tmp - SelectedDate->LastDayInThisMonth;
			if (SelectedDate->Month == 12) { SelectedDate->Year++; SelectedDate->Month = 1; }
			else SelectedDate->Month++;;
		}
		SelectedYear->SelectedIndex = SelectedDate->Year - 1900;
		SelectedMonth->SelectedIndex = SelectedDate->Month - 1;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}

}
void TuCalendar::MonthView::ThursdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Month = CalendarOnShow->Month;
	if (ThursdayList->SelectedIndex != -1)
	{
		SundayList->SelectedIndex = -1;
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;

		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = ThursdayList->SelectedIndex * 7 + 1 - x + 4;
		if (tmp <= SelectedDate->LastDayInThisMonth&&tmp >= 1)
			SelectedDate->Day = tmp;
		else if (tmp <= 0)
		{
			if (CalendarOnShow->Month == 1)
			{
				CalendarOnShow->Year--;
				CalendarOnShow->Month = 12;
				SelectedDate->Year = CalendarOnShow->Year;
				SelectedDate->Month = CalendarOnShow->Month;
			}
			else SelectedDate->Month = CalendarOnShow->Month - 1;
			SelectedDate->Day = tmp + SelectedDate->LastDayInThisMonth;
		}
		else if (tmp > SelectedDate->LastDayInThisMonth)
		{
			SelectedDate->Day = tmp - SelectedDate->LastDayInThisMonth;
			if (SelectedDate->Month == 12) { SelectedDate->Year++; SelectedDate->Month = 1; }
			else SelectedDate->Month++;;
		}
		SelectedYear->SelectedIndex = SelectedDate->Year - 1900;
		SelectedMonth->SelectedIndex = SelectedDate->Month - 1;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}

}
void TuCalendar::MonthView::FridayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Month = CalendarOnShow->Month;
	if (FridayList->SelectedIndex != -1)
	{
		SundayList->SelectedIndex = -1;
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;

		SaturdayList->SelectedIndex = -1;
		int tmp = FridayList->SelectedIndex * 7 + 1 - x + 5;
		if (tmp <= SelectedDate->LastDayInThisMonth&&tmp >= 1)
			SelectedDate->Day = tmp;
		else if (tmp <= 0)
		{
			if (CalendarOnShow->Month == 1)
			{
				CalendarOnShow->Year--;
				CalendarOnShow->Month = 12;
				SelectedDate->Year = CalendarOnShow->Year;
				SelectedDate->Month = CalendarOnShow->Month;
			}
			else SelectedDate->Month = CalendarOnShow->Month - 1;
			SelectedDate->Day = tmp + SelectedDate->LastDayInThisMonth;
		}
		else if (tmp > SelectedDate->LastDayInThisMonth)
		{
			SelectedDate->Day = tmp - SelectedDate->LastDayInThisMonth;
			if (SelectedDate->Month == 12) { SelectedDate->Year++; SelectedDate->Month = 1; }
			else SelectedDate->Month++;;
		}
		SelectedYear->SelectedIndex = SelectedDate->Year - 1900;
		SelectedMonth->SelectedIndex = SelectedDate->Month - 1;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}

}
void TuCalendar::MonthView::SaturdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Month = CalendarOnShow->Month;
	if (SaturdayList->SelectedIndex != -1)
	{
		SundayList->SelectedIndex = -1;
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		int tmp = SaturdayList->SelectedIndex * 7 + 1 - x + 6;
		if (tmp <= SelectedDate->LastDayInThisMonth&&tmp >= 1)
			SelectedDate->Day = tmp;
		else if (tmp <= 0)
		{
			if (CalendarOnShow->Month == 1)
			{
				CalendarOnShow->Year--;
				CalendarOnShow->Month = 12;
				SelectedDate->Year = CalendarOnShow->Year;
				SelectedDate->Month = CalendarOnShow->Month;
			}
			else SelectedDate->Month = CalendarOnShow->Month - 1;
			SelectedDate->Day = tmp + SelectedDate->LastDayInThisMonth;
		}
		else if (tmp > SelectedDate->LastDayInThisMonth)
		{
			SelectedDate->Day = tmp - SelectedDate->LastDayInThisMonth;
			if (SelectedDate->Month == 12) { SelectedDate->Year++; SelectedDate->Month = 1; }
			else SelectedDate->Month++;;
		}
		SelectedYear->SelectedIndex = SelectedDate->Year - 1900;
		SelectedMonth->SelectedIndex = SelectedDate->Month - 1;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}

}



void TuCalendar::MonthView::SelectedYear_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Year = SelectedYear->SelectedIndex + 1900;
	if (SelectedDate->Day > SelectedDate->LastDayInThisMonth)
	{
		SelectedDate->Day = SelectedDate->LastDayInThisMonth;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}
	CalendarOnShow->Year = SelectedDate->Year;
	showday();
}

void TuCalendar::MonthView::SelectedMonth_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	SelectedDate->Month = SelectedMonth->SelectedIndex + 1;
	if (SelectedDate->Day > SelectedDate->LastDayInThisMonth)
	{
		SelectedDate->Day = SelectedDate->LastDayInThisMonth;
		SelectedDay->SelectedIndex = SelectedDate->Day - 1;
	}
	CalendarOnShow->Month = SelectedDate->Month;

	showday();
}

void TuCalendar::MonthView::SelectedDay_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (SelectedDate->Day <= SelectedDate->LastDayInThisMonth)
	{
		SelectedDate->Day = SelectedDay->SelectedIndex + 1;
	}
	else
	{
		SelectedDate->Day = SelectedDate->LastDayInThisMonth;
		SelectedDay->SelectedIndex = SelectedDate->LastDayInThisMonth - 1;
	}

	CalendarOnShow->Day = SelectedDate->Day;
	showday();
}
