using Calculator.App.UWP.Pages;
using System;
using System.Collections.Generic;
using Windows.UI.Xaml.Controls;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Calculator.App.UWP
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
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
