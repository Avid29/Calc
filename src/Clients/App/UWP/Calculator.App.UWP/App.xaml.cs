// Inspired by the Microsoft Calculator
// Code pulled from https://github.com/microsoft/calculator
// Adam Dernis © 2021

using Calculator.App.UWP.Views;
using System;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.ApplicationModel.Core;
using Windows.Foundation;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace Calculator.App.UWP
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    public sealed partial class App : Application
    {
        //private readonly ReaderWriterLockSlim _windowsMapLock = new ReaderWriterLockSlim();
        private bool _preLaunched;
        private int _mainViewId;

        /// <summary>
        /// Initializes a new instance of the <see cref="App"/> class, a singleton application object. 
        /// This is the first line of authored code executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            InitializeComponent();
            Suspending += OnSuspending;
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="args">Details about the launch request and process.</param>
        protected override void OnLaunched(LaunchActivatedEventArgs args)
        {
            if (args.PrelaunchActivated)
            {
                // If the app got pre-launch activated, then save that state in a flag
                _preLaunched = true;
            }
            //NavCategory.InitializeCategoryManifest(args.User);
            OnAppLaunch(args, args.Arguments);
        }

        /// <summary>
        /// Invoked when Navigation to a certain page fails.
        /// </summary>
        /// <param name="sender">The Frame which failed navigation.</param>
        /// <param name="e">Details about the navigation failure.</param>
        private void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }

        private void OnAppLaunch(IActivatedEventArgs args, string argument)
        {
            // Uncomment the following lines to display frame-rate and per-frame CPU usage info.
            //#if _DEBUG
            //    if (IsDebuggerPresent())
            //    {
            //        DebugSettings->EnableFrameRateCounter = true;
            //    }
            //#endif

            //args.SplashScreen.Dismissed += DismissedEventHandler;

            var rootFrame = Window.Current.Content as Frame;
            WeakReference weak = new WeakReference(this);

            float minWindowWidth = (float)(double)Resources["AppMinWindowWidth"];
            float minWindowHeight = (float)(double)Resources["AppMinWindowHeight"];
            Size minWindowSize = SizeHelper.FromDimensions(minWindowWidth, minWindowHeight);

            ApplicationView appView = ApplicationView.GetForCurrentView();
            ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
            // For very first launch, set the size of the calc as size of the default standard mode
            if (!localSettings.Values.ContainsKey("VeryFirstLaunch"))
            {
                localSettings.Values["VeryFirstLaunch"] = false;
                appView.SetPreferredMinSize(minWindowSize);
                appView.TryResizeView(minWindowSize);
            }
            else
            {
                ApplicationView.PreferredLaunchWindowingMode = ApplicationViewWindowingMode.Auto;
            }

            // Do not repeat app initialization when the Window already has content,
            // just ensure that the window is active
            if (rootFrame == null)
            {
                if (!Windows.Foundation.Metadata.ApiInformation.IsTypePresent("Windows.Phone.UI.Input.HardwareButtons")) // PC Family
                {
                    // Disable the system view activation policy during the first launch of the app
                    // only for PC family devices and not for phone family devices
                    try
                    {
                        ApplicationViewSwitcher.DisableSystemViewActivationPolicy();
                    }
                    catch (Exception)
                    {
                        // Log that DisableSystemViewActionPolicy didn't work
                    }
                }

                // Create a Frame to act as the navigation context
                rootFrame = App.CreateFrame();

                // When the navigation stack isn't restored navigate to the first page,
                // configuring the new page by passing required information as a navigation
                // parameter
                if (!rootFrame.Navigate(typeof(MainPage), argument))
                {
                    // We couldn't navigate to the main page, kill the app so we have a good
                    // stack to debug
                    throw new SystemException();
                }

                SetMinWindowSizeAndActivate(rootFrame, minWindowSize);
                _mainViewId = ApplicationView.GetForCurrentView().Id;
                //AddWindowToMap(WindowFrameService.CreateNewWindowFrameService(rootFrame, false, weak));
            }
            else
            {
                // For first launch, LaunchStart is logged in constructor, this is for subsequent launches.

                // !Phone check is required because even in continuum mode user interaction mode is Mouse not Touch
                if ((UIViewSettings.GetForCurrentView().UserInteractionMode == UserInteractionMode.Mouse)
                    && (!Windows.Foundation.Metadata.ApiInformation.IsTypePresent("Windows.Phone.UI.Input.HardwareButtons")))
                {
                    // If the pre-launch hasn't happened then allow for the new window/view creation
                    if (!_preLaunched)
                    {
                        var newCoreAppView = CoreApplication.CreateNewView();
                        _ = newCoreAppView.Dispatcher.RunAsync(
                            CoreDispatcherPriority.Normal, async () =>
                            {
                                var that = weak.Target as App;
                                if (that != null)
                                {
                                    var newRootFrame = App.CreateFrame();

                                    SetMinWindowSizeAndActivate(newRootFrame, minWindowSize);

                                    if (!newRootFrame.Navigate(typeof(MainPage), argument))
                                    {
                                        // We couldn't navigate to the main page, kill the app so we have a good
                                        // stack to debug
                                        throw new SystemException();
                                    }

                                    //var frameService = WindowFrameService.CreateNewWindowFrameService(newRootFrame, true, weak);
                                    //that.AddWindowToMap(frameService);

                                    var dispatcher = CoreWindow.GetForCurrentThread().Dispatcher;

                                    // CSHARP_MIGRATION_ANNOTATION:
                                    // class SafeFrameWindowCreation is being interpreted into a IDisposable class
                                    // in order to enhance its RAII capability that was written in C++/CX
                                    /* using (var safeFrameServiceCreation = new SafeFrameWindowCreation(frameService, that))
                                    {
                                        int newWindowId = ApplicationView.GetApplicationViewIdForWindow(CoreWindow.GetForCurrentThread());

                                        ActivationViewSwitcher activationViewSwitcher = null;
                                        var activateEventArgs = args as IViewSwitcherProvider;
                                        if (activateEventArgs != null)
                                        {
                                            activationViewSwitcher = activateEventArgs.ViewSwitcher;
                                        }

                                        if (activationViewSwitcher != null)
                                        {
                                            _ = activationViewSwitcher.ShowAsStandaloneAsync(newWindowId, ViewSizePreference.Default);
                                            safeFrameServiceCreation.SetOperationSuccess(true);
                                        }
                                        else
                                        {
                                            var activatedEventArgs = (args as IApplicationViewActivatedEventArgs);
                                            if ((activatedEventArgs != null) && (activatedEventArgs.CurrentlyShownApplicationViewId != 0))
                                            {
                                                // CSHARP_MIGRATION_ANNOTATION:
                                                // here we don't use ContinueWith() to interpret origin code because we would like to 
                                                // pursue the design of class SafeFrameWindowCreate whichi was using RAII to ensure
                                                // some states get handled properly when its instance is being destructed.
                                                //
                                                // To achieve that, SafeFrameWindowCreate has been reinterpreted using IDisposable
                                                // pattern, which forces we use below way to keep async works being controlled within
                                                // a same code block.
                                                var viewShown = await ApplicationViewSwitcher.TryShowAsStandaloneAsync(
                                                                frameService.GetViewId(),
                                                                ViewSizePreference.Default,
                                                                activatedEventArgs.CurrentlyShownApplicationViewId,
                                                                ViewSizePreference.Default);
                                                // SafeFrameServiceCreation is used to automatically remove the frame
                                                // from the list of frames if something goes bad.
                                                safeFrameServiceCreation.SetOperationSuccess(viewShown);
                                            }
                                        }
                                    }*/
                                }
                            });
                    }
                    else
                    {
                        ActivationViewSwitcher activationViewSwitcher = null;
                        var activateEventArgs = (args as IViewSwitcherProvider);
                        if (activateEventArgs != null)
                        {
                            activationViewSwitcher = activateEventArgs.ViewSwitcher;
                        }

                        if (activationViewSwitcher != null)
                        {
                            _ = activationViewSwitcher.ShowAsStandaloneAsync(
                                ApplicationView.GetApplicationViewIdForWindow(CoreWindow.GetForCurrentThread()), ViewSizePreference.Default);
                        }
                        else
                        {
                            //TraceLogger.GetInstance().LogError(ViewMode.None, "App.OnAppLaunch", "Null_ActivationViewSwitcher");
                        }
                    }
                    // Set the preLaunched flag to false
                    _preLaunched = false;
                }
                else // for touch devices
                {
                    if (rootFrame.Content == null)
                    {
                        // When the navigation stack isn't restored navigate to the first page,
                        // configuring the new page by passing required information as a navigation
                        // parameter
                        if (!rootFrame.Navigate(typeof(MainPage), argument))
                        {
                            // We couldn't navigate to the main page,
                            // kill the app so we have a good stack to debug
                            throw new SystemException();
                        }
                    }
                    if (ApplicationView.GetForCurrentView().ViewMode != ApplicationViewMode.CompactOverlay)
                    {
                        if (!Windows.Foundation.Metadata.ApiInformation.IsTypePresent("Windows.Phone.UI.Input.HardwareButtons"))
                        {
                            // for tablet mode: since system view activation policy is disabled so do ShowAsStandaloneAsync if activationViewSwitcher exists in
                            // activationArgs
                            ActivationViewSwitcher activationViewSwitcher = null;
                            var activateEventArgs = (args as IViewSwitcherProvider);
                            if (activateEventArgs != null)
                            {
                                activationViewSwitcher = activateEventArgs.ViewSwitcher;
                            }
                            if (activationViewSwitcher != null)
                            {
                                var viewId = (args as IApplicationViewActivatedEventArgs).CurrentlyShownApplicationViewId;
                                if (viewId != 0)
                                {
                                    _ = activationViewSwitcher.ShowAsStandaloneAsync(viewId);
                                }
                            }
                        }
                        // Ensure the current window is active
                        Window.Current.Activate();
                    }
                }
            }
        }

        /// <summary>
        /// Invoked when application execution is being suspended.  Application state is saved
        /// without knowing whether the application will be terminated or resumed with the contents
        /// of memory still intact.
        /// </summary>
        /// <param name="sender">The source of the suspend request.</param>
        /// <param name="e">Details about the suspend request.</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            SuspendingDeferral deferral = e.SuspendingOperation.GetDeferral();
            //TODO: Save application state and stop any background activity
            deferral.Complete();
        }

        private static Frame CreateFrame()
        {
            var frame = new Frame();
            // frame.FlowDirection = LocalizationService.GetInstance().GetFlowDirection();
            return frame;
        }

        private static void SetMinWindowSizeAndActivate(Frame rootFrame, Size minWindowSize)
        {
            // SetPreferredMinSize should always be called before Window.Activate
            ApplicationView appView = ApplicationView.GetForCurrentView();
            appView.SetPreferredMinSize(minWindowSize);

            // Place the frame in the current Window
            Window.Current.Content = rootFrame;
            Window.Current.Activate();
        }
    }
}
