// Inspired by the Microsoft Calculator
// Code pulled from https://github.com/microsoft/calculator
// Adam Dernis © 2021

using Calculator.App.ViewModel.Servies.Localization;
using Windows.ApplicationModel.Resources;

namespace Calculator.App.UWP.Services.Localization
{
    /// <summary>
    /// A resource provider that loads localized string.
    /// </summary>
    public class AppResourceProvider : IAppResourceProvider
    {
        private readonly ResourceLoader _resourceLoader;

        /// <summary>
        /// Initializes a new instance of the <see cref="AppResourceProvider"/> class.
        /// </summary>
        public AppResourceProvider()
        {
            _resourceLoader = ResourceLoader.GetForViewIndependentUse();
        }

        /// <summary>
        /// Gets an instance of the <see cref="AppResourceProvider"/>.
        /// </summary>
        /// <returns>An instance of the <see cref="AppResourceProvider"/>.</returns>
        public static AppResourceProvider GetInstance()
        {
            return new AppResourceProvider();
        }

        /// <inheritdoc/>
        public string GetResourceString(string key) => _resourceLoader.GetString(key);
    }
}
