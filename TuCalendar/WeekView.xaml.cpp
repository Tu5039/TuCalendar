//
// WeekView.xaml.cpp
// WeekView 类的实现
//

#include "pch.h"
#include "WeekView.xaml.h"

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

WeekView::WeekView()
{
	InitializeComponent();
	SelectedDay->SelectedIndex = WeekSelectedDate->Day - 1;
	SelectedMonth->SelectedIndex = WeekSelectedDate->Month - 1;
	SelectedYear->SelectedIndex = WeekSelectedDate->Year - 1900;


	WeekShow1();
}

int TuCalendar::WeekView::GetDayOfWeek(Windows::Globalization::Calendar ^ calendar)
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

void TuCalendar::WeekView::DayShow1(Windows::UI::Xaml::Controls::TextBlock ^ textblock1, Windows::UI::Xaml::Controls::TextBlock ^textblock2, Windows::Globalization::Calendar^ calendar)
{
	textblock1->Text = calendar->DayAsPaddedString(1);
	obj = lunar.solar2lunar(calendar->Year, calendar->Month, calendar->Day);
	textblock2->Text = obj->lunarDayChineseNameString;
	if (obj->isTerm)textblock2->Text += "\n" + obj->termString;
	if (obj->isFestival)textblock2->Text += "\n" + obj->FestivalString;
}


void TuCalendar::WeekView::WeekShow1()
{

	WeekCalendarOnShow->AddDays(-GetDayOfWeek(WeekCalendarOnShow));


	DayShow1(Sunday, SundayLunar, WeekCalendarOnShow);

	WeekCalendarOnShow->AddDays(1);
	DayShow1(Monday, MondayLunar, WeekCalendarOnShow);

	WeekCalendarOnShow->AddDays(1);
	DayShow1(Tuesday, TuesdayLunar, WeekCalendarOnShow);

	WeekCalendarOnShow->AddDays(1);
	DayShow1(Wednesday, WednesdayLunar, WeekCalendarOnShow);

	WeekCalendarOnShow->AddDays(1);
	DayShow1(Thursday, ThursdayLunar, WeekCalendarOnShow);

	WeekCalendarOnShow->AddDays(1);
	DayShow1(Friday, FridayLunar, WeekCalendarOnShow);

	WeekCalendarOnShow->AddDays(1);
	DayShow1(Saturday, SaturdayLunar, WeekCalendarOnShow);

	switch (GetDayOfWeek(WeekSelectedDate))
	{
	case 0:SundayList->SelectedIndex = 0; break;
	case 1:MondayList->SelectedIndex = 0; break;
	case 2:TuesdayList->SelectedIndex = 0; break;
	case 3:WednesdayList->SelectedIndex = 0; break;
	case 4:ThursdayList->SelectedIndex = 0; break;
	case 5:FridayList->SelectedIndex = 0; break;
	case 6:SaturdayList->SelectedIndex = 0; break;
	}
}



void TuCalendar::WeekView::SundayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

	if (SundayList->SelectedIndex != -1)
	{
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = GetDayOfWeek(WeekSelectedDate);
		WeekSelectedDate->AddDays(0 - tmp);
		SelectedDay->SelectedIndex = WeekSelectedDate->Day - 1;
		SelectedMonth->SelectedIndex = WeekSelectedDate->Month - 1;
		SelectedYear->SelectedIndex = WeekSelectedDate->Year - 1900;
	}
}


void TuCalendar::WeekView::MondayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

	if (MondayList->SelectedIndex != -1)
	{
		SundayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = GetDayOfWeek(WeekSelectedDate);
		WeekSelectedDate->AddDays(1 - tmp);
		SelectedDay->SelectedIndex = WeekSelectedDate->Day - 1;
		SelectedMonth->SelectedIndex = WeekSelectedDate->Month - 1;
		SelectedYear->SelectedIndex = WeekSelectedDate->Year - 1900;
	}
}


void TuCalendar::WeekView::TuesdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

	if (TuesdayList->SelectedIndex != -1)
	{
		MondayList->SelectedIndex = -1;
		SundayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = GetDayOfWeek(WeekSelectedDate);
		WeekSelectedDate->AddDays(2 - tmp);
		SelectedDay->SelectedIndex = WeekSelectedDate->Day - 1;
		SelectedMonth->SelectedIndex = WeekSelectedDate->Month - 1;
		SelectedYear->SelectedIndex = WeekSelectedDate->Year - 1900;
	}

}


void TuCalendar::WeekView::WednesdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

	if (WednesdayList->SelectedIndex != -1)
	{
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		SundayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = GetDayOfWeek(WeekSelectedDate);
		WeekSelectedDate->AddDays(3 - tmp);
		SelectedDay->SelectedIndex = WeekSelectedDate->Day - 1;
		SelectedMonth->SelectedIndex = WeekSelectedDate->Month - 1;
		SelectedYear->SelectedIndex = WeekSelectedDate->Year - 1900;
	}
}


void TuCalendar::WeekView::ThursdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

	if (ThursdayList->SelectedIndex != -1)
	{
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		SundayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		int tmp = GetDayOfWeek(WeekSelectedDate);
		WeekSelectedDate->AddDays(4 - tmp);
		SelectedDay->SelectedIndex = WeekSelectedDate->Day - 1;
		SelectedMonth->SelectedIndex = WeekSelectedDate->Month - 1;
		SelectedYear->SelectedIndex = WeekSelectedDate->Year - 1900;
	}
}


void TuCalendar::WeekView::FridayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

	if (FridayList->SelectedIndex != -1)
	{
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		SaturdayList->SelectedIndex = -1;
		SundayList->SelectedIndex = -1;
		int tmp = GetDayOfWeek(WeekSelectedDate);
		WeekSelectedDate->AddDays(5 - tmp);
		SelectedDay->SelectedIndex = WeekSelectedDate->Day - 1;
		SelectedMonth->SelectedIndex = WeekSelectedDate->Month - 1;
		SelectedYear->SelectedIndex = WeekSelectedDate->Year - 1900;
	}
}


void TuCalendar::WeekView::SaturdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

	if (SaturdayList->SelectedIndex != -1)
	{
		MondayList->SelectedIndex = -1;
		TuesdayList->SelectedIndex = -1;
		WednesdayList->SelectedIndex = -1;
		ThursdayList->SelectedIndex = -1;
		FridayList->SelectedIndex = -1;
		SundayList->SelectedIndex = -1;
		int tmp = GetDayOfWeek(WeekSelectedDate);
		WeekSelectedDate->AddDays(6 - tmp);
		SelectedDay->SelectedIndex = WeekSelectedDate->Day - 1;
		SelectedMonth->SelectedIndex = WeekSelectedDate->Month - 1;
		SelectedYear->SelectedIndex = WeekSelectedDate->Year - 1900;
	}
}


void TuCalendar::WeekView::SelectedYear_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	WeekSelectedDate->Year = SelectedYear->SelectedIndex + 1900;
	WeekCalendarOnShow->Year = WeekSelectedDate->Year;
	WeekShow1();
}


void TuCalendar::WeekView::SelectedMonth_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	WeekSelectedDate->Month = SelectedMonth->SelectedIndex + 1;

	WeekCalendarOnShow->Month = WeekSelectedDate->Month;
	WeekShow1();
}


void TuCalendar::WeekView::SelectedDay_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	WeekSelectedDate->Day = SelectedDay->SelectedIndex + 1;

	WeekCalendarOnShow->Day = WeekSelectedDate->Day;
	WeekShow1();
}
