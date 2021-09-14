// Inspired by the Microsoft Calculator
// Code pulled from https://github.com/microsoft/calculator
// Adam Dernis © 2021

using Calculator.App.ViewModel.Common;
using Windows.System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;

namespace Calculator.App.UWP.Controls
{
    public sealed class CalculatorButton : Button
    {
        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="ButtonId"/> property.
        /// </summary>
        public static readonly DependencyProperty ButtonIdProperty =
            DependencyProperty.Register(nameof(ButtonId), typeof(NumbersAndOperatorsEnum), typeof(CalculatorButton), new PropertyMetadata(default(NumbersAndOperatorsEnum), new PropertyChangedCallback((sender, args) =>
            {
                var self = (CalculatorButton)sender;
                self.OnButtonIdPropertyChanged((NumbersAndOperatorsEnum)args.OldValue, (NumbersAndOperatorsEnum)args.NewValue);
            })));

        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="AuditoryFeedback"/> property.
        /// </summary>
        public static readonly DependencyProperty AuditoryFeedbackProperty =
            DependencyProperty.Register(nameof(AuditoryFeedback), typeof(string), typeof(CalculatorButton), new PropertyMetadata(string.Empty, new PropertyChangedCallback((sender, args) =>
            {
                var self = (CalculatorButton)sender;
                self.OnAuditoryFeedbackPropertyChanged((string)args.OldValue, (string)args.NewValue);
            })));

        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="HoverBackground"/> property.
        /// </summary>
        public static readonly DependencyProperty HoverBackgroundProperty =
                DependencyProperty.Register(nameof(HoverBackground), typeof(Brush), typeof(CalculatorButton), new PropertyMetadata(default(Brush)));

        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="HoverForeground"/> property.
        /// </summary>
        public static readonly DependencyProperty HoverForegroundProperty =
                DependencyProperty.Register(nameof(HoverForeground), typeof(Brush), typeof(CalculatorButton), new PropertyMetadata(default(Brush)));

        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="PressBackground"/> property.
        /// </summary>
        public static readonly DependencyProperty PressBackgroundProperty =
            DependencyProperty.Register(nameof(PressBackground), typeof(Brush), typeof(CalculatorButton), new PropertyMetadata(default(Brush)));

        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="PressForeground"/> property.
        /// </summary>
        public static readonly DependencyProperty PressForegroundProperty =
            DependencyProperty.Register(nameof(PressForeground), typeof(Brush), typeof(CalculatorButton), new PropertyMetadata(default(Brush)));

        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="DisabledBackground"/> property.
        /// </summary>
        public static readonly DependencyProperty DisabledBackgroundProperty =
            DependencyProperty.Register(nameof(DisabledBackground), typeof(Brush), typeof(CalculatorButton), new PropertyMetadata(default(Brush)));

        /// <summary>
        /// <see cref="DependencyProperty"/> for the <see cref="DisabledForeground"/> property.
        /// </summary>
        public static readonly DependencyProperty DisabledForegroundProperty =
            DependencyProperty.Register(nameof(DisabledForeground), typeof(Brush), typeof(CalculatorButton), new PropertyMetadata(default(Brush)));

        /// <summary>
        /// Initializes a new instance of the <see cref="CalculatorButton"/> class.
        /// </summary>
        public CalculatorButton()
        {
            // Set the default bindings for this button, these can be overwritten by Xaml if needed
            // These are a replacement for binding in styles
            Binding commandBinding = new Binding();
            commandBinding.Path = new PropertyPath("ButtonPressed");
            this.SetBinding(CommandProperty, commandBinding);
        }

        /// <summary>
        /// Gets or sets the input associated to the button.
        /// </summary>
        public NumbersAndOperatorsEnum ButtonId
        {
            get => (NumbersAndOperatorsEnum)GetValue(ButtonIdProperty);
            set => SetValue(ButtonIdProperty, value);
        }

        /// <summary>
        /// Gets or sets a string representing the auditory feedback to a keypress for the button.
        /// </summary>
        public string AuditoryFeedback
        {
            get => (string)GetValue(AuditoryFeedbackProperty);
            set => SetValue(AuditoryFeedbackProperty, value);
        }

        public Brush HoverBackground
        {
            get { return (Brush)GetValue(HoverBackgroundProperty); }
            set { SetValue(HoverBackgroundProperty, value); }
        }

        public Brush HoverForeground
        {
            get { return (Brush)GetValue(HoverForegroundProperty); }
            set { SetValue(HoverForegroundProperty, value); }
        }

        public Brush PressBackground
        {
            get { return (Brush)GetValue(PressBackgroundProperty); }
            set { SetValue(PressBackgroundProperty, value); }
        }

        public Brush PressForeground
        {
            get { return (Brush)GetValue(PressForegroundProperty); }
            set { SetValue(PressForegroundProperty, value); }
        }

        public Brush DisabledBackground
        {
            get { return (Brush)GetValue(DisabledBackgroundProperty); }
            set { SetValue(DisabledBackgroundProperty, value); }
        }

        public Brush DisabledForeground
        {
            get { return (Brush)GetValue(DisabledForegroundProperty); }
            set { SetValue(DisabledForegroundProperty, value); }
        }

        protected override void OnKeyDown(KeyRoutedEventArgs e)
        {
            // Ignore the Enter key
            if (e.Key == VirtualKey.Enter)
            {
                return;
            }

            base.OnKeyDown(e);
        }

        protected override void OnKeyUp(KeyRoutedEventArgs e)
        {
            // Ignore the Enter key
            if (e.Key == VirtualKey.Enter)
            {
                return;
            }

            base.OnKeyUp(e);
        }

        private void OnButtonIdPropertyChanged(NumbersAndOperatorsEnum oldValue, NumbersAndOperatorsEnum newValue)
        {
            this.CommandParameter = new CalculatorButtonPressedEventArgs(AuditoryFeedback, newValue);
        }

        private void OnAuditoryFeedbackPropertyChanged(string oldValue, string newValue)
        {
            this.CommandParameter = new CalculatorButtonPressedEventArgs(newValue, ButtonId);
        }
    }
}
