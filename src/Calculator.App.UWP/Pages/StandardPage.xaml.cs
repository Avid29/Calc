using System.Collections.Generic;
using Windows.UI.Xaml.Controls;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace Calculator.App.UWP.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class StandardPage : Page
    {
        public StandardPage()
        {
            for (char c = 'A'; c <= 'Z'; c++)
            {
                //Variables.Add(c.ToString()); Consider adding uppercase letters
                Variables.Add(((char)(c + 'a' - 'A')).ToString());
            }
            Variables.Add("𝛼");
            Variables.Add("𝛽");
            Variables.Add("𝜃");
            Variables.Add("𝜔");

            this.InitializeComponent();
        }

        List<string> Variables { get; } = new List<string>();

        List<string> Constants { get; } = new List<string>()
        {
            "𝜋",
            "𝑒",
            "𝜑",
        };
    }
}
