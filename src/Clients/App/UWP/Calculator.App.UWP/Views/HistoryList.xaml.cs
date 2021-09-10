// Adam Dernis © 2021

using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace Calculator.App.UWP.Views
{
    /// <summary>
    /// The control for listing the history of inputs in the calculator.
    /// </summary>
    public sealed partial class HistoryList : UserControl
    {
        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="RowHeight"/> property.
        /// </summary>
        public static readonly DependencyProperty RowHeightProperty =
            DependencyProperty.Register(
                nameof(RowHeight),
                typeof(GridLength),
                typeof(HistoryList),
                new PropertyMetadata(default(GridLength)));

        /// <summary>
        /// Initializes a new instance of the <see cref="HistoryList"/> class.
        /// </summary>
        public HistoryList()
        {
            this.InitializeComponent();
        }

        public GridLength RowHeight
        {
            get { return (GridLength)GetValue(RowHeightProperty); }
            set { SetValue(RowHeightProperty, value); }
        }
    }
}
