using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace FatedLauncher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ContextMenuStrip menu;
        private NotifyIcon trayIcon;
        private Timer menuCloseTimer;

        private MenuManager menuManager;

        public MainWindow()
        {
            InitializeComponent();

            this.menuManager = new MenuManager();

            // Set up tray icon
            trayIcon = new NotifyIcon
            {
                Icon = System.Drawing.SystemIcons.Application,
                Visible = true,
                Text = "Tray App"
            };

            trayIcon.MouseClick += (s, e) =>
            {
                if (e.Button == MouseButtons.Left)
                {
                    this.menuManager.ShowMainMenu();
                }
            };

            // Set up tray menu
            //this.menu = new ContextMenuStrip();
            //this.menu.Items.Add("Open Window", null, (s, e) => ShowWindow());
            //this.menu.Items.Add("Option A", null, (s, e) => ShowMessage("Option A"));
            //this.menu.Items.Add("Exit", null, (s, e) => ExitApp());

            this.StateChanged += (s, e) =>
            {
                if (this.WindowState == WindowState.Minimized)
                    this.Hide();
            };

            this.Closing += (s, e) =>
            {
                e.Cancel = true;
                this.Hide();
            };

            this.Loaded += (s, e) => { this.Hide(); };
        }

        private void ShowWindow()
        {
            this.Show();
            this.WindowState = WindowState.Normal;
            this.Activate();
        }

        private void ShowMessage(string text)
        {
            System.Windows.MessageBox.Show($"You clicked: {text}", "Tray Option");
        }

        private void ExitApp()
        {
            trayIcon.Visible = false;
            trayIcon.Dispose();
            System.Windows.Application.Current.Shutdown();
        }
    }
}
