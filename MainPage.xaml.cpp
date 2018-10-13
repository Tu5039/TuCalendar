//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "MonthView.xaml.h"
#include "WeekView.xaml.h"
#include "WelcomePage.xaml.h"

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

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

MainPage::MainPage()
{
	InitializeComponent();
	this->main->Navigate(Windows::UI::Xaml::Interop::TypeName(WelcomePage::typeid));
}


void TuCalendar::MainPage::IconListbox_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (MonthViewTab->IsSelected)
	{
		this->main->Navigate(Windows::UI::Xaml::Interop::TypeName(MonthView::typeid));
	}
	else if (WeekViewTab->IsSelected)
	{
		this->main->Navigate(Windows::UI::Xaml::Interop::TypeName(WeekView::typeid));;
	}
	/*else if (DayViewTab->IsSelected)
	{
		this->main->Navigate(Windows::UI::Xaml::Interop::TypeName(DayView::typeid));;
	}
	else if (YearViewTab->IsSelected)
	{
		this->main->Navigate(Windows::UI::Xaml::Interop::TypeName(YearView::typeid));;
	}
	else if (DecadeViewTab->IsSelected)
	{
		this->main->Navigate(Windows::UI::Xaml::Interop::TypeName(DecadeView::typeid));;
	}*/
	else if (WelcomeTab->IsSelected)
	{
		this->main->Navigate(Windows::UI::Xaml::Interop::TypeName(WelcomePage::typeid));;
	}
}


void TuCalendar::MainPage::MyButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	MySplitView->IsPaneOpen = !MySplitView->IsPaneOpen;
}
