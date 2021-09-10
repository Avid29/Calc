// Adam Dernis © 2021

namespace Calculator.App.ViewModel.Servies
{
    /// <summary>
    /// An interface for a resource provider.
    /// </summary>
    public interface IAppResourceProvider
    {
        /// <summary>
        /// Gets a string from the resource loader.
        /// </summary>
        /// <param name="key">The key for the resource.</param>
        /// <returns>A string from the resource loader.</returns>
        string GetResourceString(string key);
    }
}
