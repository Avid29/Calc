using Calculator.App.UWP.Pages;
using System;
using System.Collections.Generic;
using Windows.UI.Xaml.Controls;

namespace Calculator.App.UWP
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            pages = new Dictionary<NavigationViewItemBase, Type>()
            {
                [StandardPage] = typeof(StandardPage),
                [GraphingPage] = typeof(GraphingPage),
            };
            NavigationView.SelectedItem = StandardPage;
        }

        private void NavigationView_SelectionChanged(NavigationView sender, NavigationViewSelectionChangedEventArgs args)
        {
            ContentFrame.Navigate(pages[args.SelectedItemContainer]);
        }

        private Dictionary<NavigationViewItemBase, Type> pages;
    }
}
