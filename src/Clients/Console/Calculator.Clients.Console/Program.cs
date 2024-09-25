// Adam Dernis 2024

using Calculator.ExpressionTree.Nodes;
using Calculator.Operations;
using Calculator.Parser.Default;
using Calculator.Parser.Default.Status;
using Calculator.Printers.Default;
using SysCon = System.Console;

namespace Calculator.Clients.Console;

public class Program
{
    public static void Main(string[] args)
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

            DefaultParser parser = new();
            DefaultPrinter printer = new();
            ParserStatus status = parser.ParseString(str);
            if (status.Failed)
            {
                SysCon.WriteLine($"\nError: {status.ErrorType}\n");
            }
            else
            {
                ExpNode root = parser.Tree.Root;
                Simplifier simplifier = new();
                root = root.Execute(simplifier);

                if (root == null)
                {
                    SysCon.WriteLine($"\n{simplifier.Error.Message}\n");
                }
                else
                {
                    SysCon.WriteLine($"\n{root.Print(printer)}\n");
                }
            }
        }
    }
}
