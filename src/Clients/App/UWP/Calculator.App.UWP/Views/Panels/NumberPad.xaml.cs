// Inspired by the Microsoft Calculator
// Code pulled from https://github.com/microsoft/calculator
// Adam Dernis © 2021

using Calculator.App.UWP.Services.Localization;
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

            var localizationSettings = LocalizationSettings.GetInstance();

            DecimalSeparatorButton.Content = localizationSettings.GetDecimalSeparator();
            Num0Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('0');
            Num1Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('1');
            Num2Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('2');
            Num3Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('3');
            Num4Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('4');
            Num5Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('5');
            Num6Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('6');
            Num7Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('7');
            Num8Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('8');
            Num9Button.Content = localizationSettings.GetDigitSymbolFromEnUsDigit('9');
        }

        public Style ButtonStyle
        {
            get { return (Style)GetValue(ButtonStyleProperty); }
            set { SetValue(ButtonStyleProperty, value); }
        }
    }
}
