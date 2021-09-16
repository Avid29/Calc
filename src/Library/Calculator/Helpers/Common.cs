namespace Calculator.Helpers
{
    /// <summary>
    /// General operations.
    /// </summary>
    public static class Common
    {
        /// <summary>
        /// Swaps two variables.
        /// </summary>
        /// <typeparam name="T">The type of the variables swapped.</typeparam>
        /// <param name="value1">The first value.</param>
        /// <param name="value2">The second value</param>
        public static void Swap<T>(ref T value1, ref T value2)
        {
            T swap = value1;
            value2 = value1;
            value1 = swap;
        }
    }
}
