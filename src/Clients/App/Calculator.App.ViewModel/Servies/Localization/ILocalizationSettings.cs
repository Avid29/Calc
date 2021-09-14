// Adam Dernis © 2021

namespace Calculator.App.ViewModel.Servies.Localization
{
    public interface ILocalizationSettings
    {
        char GetDigitSymbolFromEnUsDigit(char digitSymbol);

        bool IsEnUsDigit(char digit);

        char GetDecimalSeparator();
    }
}
