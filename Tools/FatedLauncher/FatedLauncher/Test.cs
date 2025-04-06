using System;
using System.Drawing;
using System.Windows.Forms;

public partial class Form1 : Form
{
    private NotifyIcon trayIcon;
    private ContextMenuStrip rightClickMenu;
    private ContextMenuStrip leftClickMenu;

    public Form1()
    {
        InitializeComponent();

        // Hide the main form window
        this.WindowState = FormWindowState.Minimized;
        this.ShowInTaskbar = false;

        // Create the tray icon
        trayIcon = new NotifyIcon();
        trayIcon.Icon = SystemIcons.Application; // You can use a custom .ico file here
        trayIcon.Text = "My Tray App";
        trayIcon.Visible = true;

        // Create context menus
        CreateRightClickMenu();
        CreateLeftClickMenu();

        // Handle mouse clicks
        trayIcon.MouseUp += TrayIcon_MouseUp;
    }

    private void CreateRightClickMenu()
    {
        rightClickMenu = new ContextMenuStrip();
        rightClickMenu.Items.Add("Right Option 1", null, (s, e) => MessageBox.Show("Right Option 1 clicked"));
        rightClickMenu.Items.Add("Right Option 2", null, (s, e) => MessageBox.Show("Right Option 2 clicked"));
        rightClickMenu.Items.Add("Exit", null, (s, e) => Application.Exit());
    }

    private void CreateLeftClickMenu()
    {
        leftClickMenu = new ContextMenuStrip();
        leftClickMenu.Items.Add("Left Option A", null, (s, e) => MessageBox.Show("Left Option A clicked"));
        leftClickMenu.Items.Add("Left Option B", null, (s, e) => MessageBox.Show("Left Option B clicked"));
    }

    private void TrayIcon_MouseUp(object sender, MouseEventArgs e)
    {
        if (e.Button == MouseButtons.Right)
        {
            rightClickMenu.Show(Cursor.Position);
        }
        else if (e.Button == MouseButtons.Left)
        {
            leftClickMenu.Show(Cursor.Position);
        }
    }

    protected override void OnFormClosing(FormClosingEventArgs e)
    {
        trayIcon.Visible = false;
        trayIcon.Dispose();
        base.OnFormClosing(e);
    }
}