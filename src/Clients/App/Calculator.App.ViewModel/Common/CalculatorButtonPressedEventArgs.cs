// Inspired by the Microsoft Calculator
// Code pulled from https://github.com/microsoft/calculator
// Adam Dernis © 2021

namespace Calculator.App.ViewModel.Common
{
    public sealed class CalculatorButtonPressedEventArgs
    {
        public CalculatorButtonPressedEventArgs(string feedback, NumbersAndOperatorsEnum operation)
        {
            Operation = operation;
            AuditoryFeedback = feedback;
        }

        public NumbersAndOperatorsEnum Operation { get; }

        public string AuditoryFeedback { get; }
    }
}
