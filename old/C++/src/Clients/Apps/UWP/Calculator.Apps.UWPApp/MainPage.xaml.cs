using CalculatorInterface;
using Windows.UI.Xaml.Controls;

namespace Calculator.Apps.UWPApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            Expression expression = new Expression();
            foreach (char c in "2+2")
            {
                expression.ParseChar(c);
            }
            string result = expression.FinalizeSimplifyPrint();
        }
    }
}
