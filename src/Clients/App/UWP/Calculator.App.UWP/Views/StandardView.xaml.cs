// Inspired by the Microsoft Calculator
// Code pulled from https://github.com/microsoft/calculator
// Adam Dernis © 2021

using Calculator.App.UWP.Services;
using Calculator.App.ViewModel;
using Calculator.App.ViewModel.ViewModels;
using Microsoft.Toolkit.Mvvm.Input;
using System.Windows.Input;
using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Automation;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Input;

namespace Calculator.App.UWP.Views
{
    /// <summary>
    /// A <see langword="delegate"/> for when the a fullscreen flyout is closed.
    /// </summary>
    public delegate void FullscreenFlyoutClosedEventHandler();

    /// <summary>
    /// The <see cref="UserControl"/> for the Calculator standard UI layout.
    /// </summary>
    public sealed partial class StandardView : UserControl
    {
        private bool _doAnimate;
        private bool _resultAnimate;
        private bool _isHistoryFlyoutOpen;
        private bool _isMemoryFlyoutOpen;
        private bool _isLastAnimatedInScientific;
        private bool _isLastAnimatedInProgrammer;
        private bool _isLastFlyoutMemory = false;
        private bool _isLastFlyoutHistory = false;

        private string _openMemoryFlyoutAutomationName;
        private string _closeMemoryFlyoutAutomationName;
        private string _openHistoryFlyoutAutomationName;
        private string _closeHistoryFlyoutAutomationName;
        private string _dockPanelHistoryMemoryLists;
        private string _dockPanelMemoryList;

        private HistoryList _historyList;

        /// <summary>
        /// Initializes a new instance of the <see cref="StandardView"/> class.
        /// </summary>
        public StandardView()
        {
            _doAnimate = false;
            _isLastAnimatedInScientific = false;
            _isLastAnimatedInProgrammer = false;
            _resultAnimate = false;

            InitializeComponent();
            LoadResourceStrings();

            HistoryButtonPressedCommand = new RelayCommand(ToggleHistoryFlyout);
        }

        /// <summary>
        /// Invoked when a fullscreen flyout is closed.
        /// </summary>
        public event FullscreenFlyoutClosedEventHandler FullscreenFlyoutClosed;

        /// <summary>
        /// Gets the command to invoke when the history button is pressed.
        /// </summary>
        public ICommand HistoryButtonPressedCommand { get; }

        /// <summary>
        /// Gets the <see cref="StandardCalculatorViewModel"/> model for the standard view element.
        /// </summary>
        public StandardCalculatorViewModel Model
        {
            get => (StandardCalculatorViewModel)this.DataContext;
        }

        /// <summary>
        /// Initializes the history view if it's not already initialized.
        /// </summary>
        /// <param name="historyViewModel">The <see cref="HistoryViewModel"/> to bind to the view.</param>
        public void InitializeHistoryView(HistoryViewModel historyViewModel)
        {
            if (_historyList == null)
            {
                _historyList = new HistoryList();
                _historyList.DataContext = historyViewModel;
                //historyVM.HideHistoryClicked += OnHideHistoryClicked;
                //historyVM.HistoryItemClicked += OnHistoryItemClicked;
            }
        }

        /// <summary>
        /// Closes the history flyout if it is open.
        /// </summary>
        public void CloseHistoryFlyout()
        {
            if (_isHistoryFlyoutOpen)
            {
                HistoryFlyout.Hide();
            }
        }

        /// <summary>
        /// Closes the memory flyout if it is open.
        /// </summary>
        public void CloseMemoryFlyout()
        {
            if (_isMemoryFlyoutOpen)
            {
                MemoryFlyout.Hide();
            }
        }

        private void OnLoaded(object sender, RoutedEventArgs e)
        {
            InitializeHistoryView(null);
        }

        private void LoadResourceStrings()
        {
            var resProvider = AppResourceProvider.GetInstance();
            _openMemoryFlyoutAutomationName = resProvider.GetResourceString("MemoryButton_Open");
            _closeMemoryFlyoutAutomationName = resProvider.GetResourceString("MemoryButton_Close");
            _openHistoryFlyoutAutomationName = resProvider.GetResourceString("HistoryButton_Open");
            _closeHistoryFlyoutAutomationName = resProvider.GetResourceString("HistoryButton_Close");
            _dockPanelHistoryMemoryLists = resProvider.GetResourceString("DockPanel_HistoryMemoryLists");
            _dockPanelMemoryList = resProvider.GetResourceString("DockPanel_MemoryList");
            //AutomationProperties.SetName(MemoryButton, m_openMemoryFlyoutAutomationName);
            //AutomationProperties.SetName(HistoryButton, m_openHistoryFlyoutAutomationName);
            //AutomationProperties.SetName(DockPanel, m_dockPanelHistoryMemoryLists);
        }

        private void EnableControls(bool enable)
        {
            OpsPanel.IsEnabled = enable;
            EnableMemoryControls(enable);
        }

        private void EnableMemoryControls(bool enable)
        {
            //MemButton.IsEnabled = enable;
            //MemMinus.IsEnabled = enable;
            //MemPlus.IsEnabled = enable;
            //if (!Model.IsMemoryEmpty)
            //{
            //    MemRecall.IsEnabled = enable;
            //    ClearMemoryButton.IsEnabled = enable;
            //}
        }

        private void HistoryFlyout_Opened(object sender, object args)
        {
            _isHistoryFlyoutOpen = true;
            _isLastFlyoutMemory = false;
            _isLastFlyoutHistory = true;
            EnableControls(false);
            AutomationProperties.SetName(HistoryButton, _closeHistoryFlyoutAutomationName);
        }

        private void HistoryFlyout_Closed(object sender, object args)
        {
            // Ideally, this would be renamed in the Closing event because the Closed event is too late.
            // Closing is not available until RS1+ so we set the name again here for TH2 support.
            AutomationProperties.SetName(HistoryButton, _openHistoryFlyoutAutomationName);
            _isHistoryFlyoutOpen = false;
            EnableControls(true);
            if (HistoryButton.IsEnabled && HistoryButton.Visibility == Visibility.Visible)
            {
                HistoryButton.Focus(FocusState.Programmatic);
            }

            FullscreenFlyoutClosed?.Invoke();
        }

        private void ToggleHistoryFlyout()
        {
            //if (Model.IsProgrammer || DockPanel.Visibility == Visibility.Visible)
            //{
            //    return;
            //}

            if (_isHistoryFlyoutOpen)
            {
                HistoryFlyout.Hide();
            }
            else
            {
                HistoryFlyout.Content = _historyList;
                _historyList.RowHeight = new GridLength(NumpadPanel.ActualHeight);
                FlyoutBase.ShowAttachedFlyout(HistoryButton);
            }
        }

        private void OnMemoryFlyOutTapped(object sender, TappedRoutedEventArgs e)
        {
            Grid grid = (Grid)sender;
            Point point = e.GetPosition(null);

            if (point.Y < (grid.ActualHeight - NumpadPanel.ActualHeight))
            {
                MemoryFlyout.Hide();
            }
        }

        private void OnHistoryFlyOutTapped(object sender, TappedRoutedEventArgs e)
        {
            Grid grid = (Grid)sender;
            Point point = e.GetPosition(null);

            if (point.Y < (grid.ActualHeight - NumpadPanel.ActualHeight))
            {
                HistoryFlyout.Hide();
            }
        }
    }
}
