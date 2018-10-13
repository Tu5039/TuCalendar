//
// MonthView.xaml.h
// MonthView 类的声明
//

#pragma once

#include "MonthView.g.h"
#include "MonthView.xaml.h"
#include "lunar.h"

using namespace Windows::Globalization;
using namespace Windows::Foundation::Collections;

namespace TuCalendar
{
	/// <summary>
	/// 可用于自身或导航至 Frame 内部的空白页。
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MonthView sealed
	{
	public:
		MonthView();
		void showday();
		int GetDayOfWeek(Windows::Globalization::Calendar^ calendar);

		//int WeekNum(int *Calendar1);

		void Sunday(int n);
		void Monday(int n);
		void Tuesday(int n);
		void Wednesday(int n);
		void Thursday(int n);
		void Friday(int n);
		void Saturday(int n);

		//void GetLun(String^ date);
	private:
		Calendar^ calendar = ref new Calendar();
		Calendar^ SelectedDate = ref new Calendar();
		Calendar^ CalendarOnShow = ref new Calendar();
		Lunar lunar;
		LunarObj* obj;
		int x;//the firstday's weeknum;
		int a;//the lastday's weeknum;

		//void AheadLunar();
		void FillprevBlank(Windows::UI::Xaml::Controls::TextBlock ^textblock1, Windows::UI::Xaml::Controls::TextBlock ^textblock2, Windows::Globalization::Calendar^ calendar);
		void FillnextBlank(Windows::UI::Xaml::Controls::TextBlock ^textblock1, Windows::UI::Xaml::Controls::TextBlock ^textblock2, Windows::Globalization::Calendar^ calendar);
		void FillDay(Windows::UI::Xaml::Controls::TextBlock ^textblock1, Windows::UI::Xaml::Controls::TextBlock ^textblock2, Windows::Globalization::Calendar^ calendar);

		void SundayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void MondayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void TuesdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void WednesdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void ThursdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void FridayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void SaturdayList_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void SelectedYear_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);

		void SelectedMonth_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void SelectedDay_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
	};
}
