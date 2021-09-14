using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace Calculator.App.UWP.Views.Panels
{
    public sealed partial class NumberPad : UserControl
    {
        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="ButtonStyle"/> property.
        /// </summary>
        public static readonly DependencyProperty ButtonStyleProperty =
            DependencyProperty.Register(nameof(ButtonStyle), typeof(Style), typeof(NumberPad), new PropertyMetadata(default(Style)));

        public NumberPad()
        {
            this.InitializeComponent();
        }

        public Style ButtonStyle
        {
            get { return (Style)GetValue(ButtonStyleProperty); }
            set { SetValue(ButtonStyleProperty, value); }
        }
    }
}
