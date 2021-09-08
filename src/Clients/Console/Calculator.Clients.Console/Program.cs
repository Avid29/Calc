using Calculator.ExpressionTree.Nodes;
using Calculator.Operations;
using Calculator.Parser.Default;
using Calculator.Parser.Default.Status;
using Calculator.Printers.Default;
using SysCon = System.Console;

namespace Calculator.Clients.Console
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                SysCon.Write("Enter an Equation (q to quit): ");
                string str = SysCon.ReadLine();

                if (str == "q")
                {
                    SysCon.Write("Done!");
                    return;
                }

                DefaultParser parser = new DefaultParser();
                DefaultPrinter printer = new DefaultPrinter();
                ParserStatus status = parser.ParseString(str);
                if (status.Failed)
                {
                    // TODO: Print error
                } else
                {
                    ExpNode root = parser.Tree.Root;
                    Simplifier simplifier = new Simplifier();
                    root = root.Execute(simplifier);
                    SysCon.WriteLine("\n" + root.Print(printer) + "\n");
                }
            }
        }
    }
}
