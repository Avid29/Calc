using System.Collections.Generic;
using Windows.UI.Xaml.Controls;

namespace Calculator.App.UWP.Pages
{
    public sealed partial class StandardPage : Page
    {
        CalculatorState state = new CalculatorState();

        public StandardPage()
        {
            for (char c = 'A'; c <= 'Z'; c++)
            {
                //Variables.Add(c.ToString()); Consider adding uppercase letters
                Variables.Add(((char)(c + 'a' - 'A')).ToString());
            }
            //Variables.Add("𝛼");
            //Variables.Add("𝛽");
            //Variables.Add("𝜃");
            //Variables.Add("𝜔");

            this.InitializeComponent();
        }

        List<string> Variables { get; } = new List<string>();

        List<string> Constants { get; } = new List<string>()
        {
            "𝜋",
            "𝑒",
            "𝜑",
        };

        private void InputKeyPressed(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            string tag = (sender as Button).Tag.ToString();
            foreach (char c in tag)
            {
                ParseChar(c);
            }
        }

        private void VariableSelected(object sender, ItemClickEventArgs e)
        {
            string tag = (string)e.ClickedItem;
            char c = tag[0];
            ParseChar(c);
        }

        private void Simplify(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            TextDisplay.Text = state.Simplify();
        }

        private void Clear(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            state.Clear();
            TextDisplay.Text = state.GetDisplay();
        }

        private void ParseChar(char c)
        {
            state.ParseNextChar(c);
            TextDisplay.Text = state.GetDisplay();
        }
    }
}
