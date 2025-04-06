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

        public MainWindow()
        {
            InitializeComponent();

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
                    ShowLeftClickMenuAtCursor();
                }
            };

            // Set up tray menu
            this.menu = new ContextMenuStrip();
            this.menu.Items.Add("Open Window", null, (s, e) => ShowWindow());
            this.menu.Items.Add("Option A", null, (s, e) => ShowMessage("Option A"));
            this.menu.Items.Add("Exit", null, (s, e) => ExitApp());

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

        private void ShowLeftClickMenuAtCursor()
        {
            var pos = System.Windows.Forms.Control.MousePosition;
            this.menu.Show(pos);
            StartMenuCloseWatcher();
        }

        private void StartMenuCloseWatcher()
        {
            if (menuCloseTimer == null)
            {
                menuCloseTimer = new Timer();
                menuCloseTimer.Interval = 100;
                menuCloseTimer.Tick += (s, e) =>
                {
                    if (!this.menu.Visible)
                    {
                        menuCloseTimer.Stop();
                        return;
                    }

                    // If left mouse is clicked outside the menu
                    if (System.Windows.Forms.Control.MouseButtons != MouseButtons.None)
                    {
                        var mousePos = System.Windows.Forms.Control.MousePosition;
                        if (!this.menu.Bounds.Contains(mousePos))
                        {
                            this.menu.Close();
                        }
                    }
                };
            }

            menuCloseTimer?.Start();
        }
    }
}
