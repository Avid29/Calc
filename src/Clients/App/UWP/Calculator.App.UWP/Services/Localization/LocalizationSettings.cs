using Calculator.App.ViewModel.Servies.Localization;
using Microsoft.Toolkit.Diagnostics;
using Windows.Globalization.NumberFormatting;

namespace Calculator.App.UWP.Services.Localization
{
    public class LocalizationSettings : ILocalizationSettings
    {
        private char _decimalSeparator;
        private char _numberGroupSeparator;
        private char[] _digitSymbols;

        private LocalizationSettings()
        {
            //Initialize(LocalizationService.GetInstance().GetRegionalSettingsAwareDecimalFormatter());
            Initialize(null);
        }

        public char GetDecimalSeparator()
        {
            return _decimalSeparator;
        }

        public char GetNumberGroupSeperator()
        {
            return _numberGroupSeparator;
        }

        public char GetDigitSymbolFromEnUsDigit(char digitSymbol)
        {
            Guard.IsBetweenOrEqualTo((int)digitSymbol, (int)'0', (int)'9', nameof(digitSymbol));
            int digit = digitSymbol - '0';
            return _digitSymbols[digit];
        }

        public static LocalizationSettings GetInstance()
        {
            return new LocalizationSettings();
        }

        public bool IsEnUsDigit(char digit)
        {
            return digit >= '0' && digit <= '9';
        }

        private void Initialize(DecimalFormatter formatter)
        {
            // TODO: Initialize properly.
            _decimalSeparator = '.';
            _numberGroupSeparator = ',';
            _digitSymbols = new char[] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        }
    }
}
