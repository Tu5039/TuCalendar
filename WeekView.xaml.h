//
// WeekView.xaml.h
// WeekView 类的声明
//

#pragma once

#include "WeekView.g.h"
#include "lunar.h"
#include "App.xaml.h"
using namespace Platform::Collections;
using namespace Windows::Globalization;
using namespace Windows::Foundation::Collections;

namespace TuCalendar
{
	/// <summary>
	/// 可用于自身或导航至 Frame 内部的空白页。
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class WeekView sealed
	{
	public:
		WeekView();
		int GetDayOfWeek(Windows::Globalization::Calendar^ calendar);
		void DayShow1(Windows::UI::Xaml::Controls::TextBlock ^textblock1, Windows::UI::Xaml::Controls::TextBlock  ^textblock2, Windows::Globalization::Calendar^ calendar);

		void WeekShow1();

	private:
		Calendar ^WeekCalendarOnShow = ref new Calendar();
		Calendar ^WeekSelectedDate = ref new Calendar();
		Lunar lunar;
		LunarObj* obj;

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
