// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.Parser.Default.Status;

namespace Calculator.Parser.Default.Functions
{
    /// <summary>
    /// A base class for objects used to parse functions in <see cref="DefaultParser"/>.
    /// </summary>
    public abstract class FunctionParser
    {
        /// <summary>
        /// How many child function parsers there are.
        /// </summary>
        protected int _depth = 0;

        /// <summary>
        /// Gets or sets the output of the <see cref="FunctionParser"/> once finished parsing.
        /// </summary>
        public BranchNode Output { get; protected set; }

        /// <summary>
        /// Makes a <see cref="FunctionParser"/> by function <see cref="char"/>.
        /// </summary>
        /// <param name="c">The function <see cref="char"/>.</param>
        /// <returns>The <see cref="FunctionParser"/> for the <see cref="char"/> <paramref name="c"/>.</returns>
        public static FunctionParser MakeFunctionParser(char c)
        {
            switch (c)
            {
                case '<':
                    return new VectorParser();
                default:
                    return null;
            }
        }

        /// <summary>
        /// Makes a <see cref="FunctionParser"/> by function name.
        /// </summary>
        /// <param name="functionName">The function name.</param>
        /// <returns>The <see cref="FunctionParser"/> for the name <paramref name="functionName"/>.</returns>
        public static FunctionParser MakeFunctionParser(string functionName)
        {
            switch (functionName)
            {
                case "sin":
                case "cos":
                case "tan":
                case "csc":
                case "sec":
                case "cot":
                    return new SinusoidalFuncParser(functionName);
                case "diff":
                    return new DiffFuncParser();
                case "int":
                    return new IntegralFuncParser();
                default:
                    return null;
            }
        }

        /// <summary>
        /// Parses the first character of the function.
        /// </summary>
        /// <param name="c">The first character of the function.</param>
        /// <returns>The resulting parser status.</returns>
        public abstract ParseError ParseFirstChar(char c);

        /// <summary>
        /// Parses the a character in the function.
        /// </summary>
        /// <param name="c">The character to parse.</param>
        /// <returns>The resulting parser status.</returns>
        public abstract ParseError ParseNextChar(char c);
    }
}
