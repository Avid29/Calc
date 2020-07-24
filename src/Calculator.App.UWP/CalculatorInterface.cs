namespace Calculator.App.UWP
{
    /// <summary>
    /// A static wrapper of a CalculatorState instance used for all operations.
    /// </summary>
    public static class CalculatorInterface
    {
        public static string Simplify(string expression)
        {
            foreach (char c in expression)
            {
                state.ParseNextChar(c);
            }

            string result = state.Simplify();
            state.Clear();
            return result;
        }

        public static bool ParseTo(string expression)
        {
            foreach (char c in expression)
            {
                if (!state.ParseNextChar(c))
                {
                    return false;
                }
            }
            state.Clear();
            return true;
        }

        private static CalculatorState state = new CalculatorState();
    }
}
