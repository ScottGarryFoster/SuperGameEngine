using FatedQuestLibraries;
using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;

class FatedLauncher
{
    static public IFilePaths StandardFilePaths;

    [STAThread]
    static void Main()
    {
        StandardFilePaths = new FilePaths();
        string builtDirectory = Path.Combine(StandardFilePaths.RepositoryDirectory(), "built");

        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);

        NotifyIcon trayIcon = new NotifyIcon();
        trayIcon.Icon = new Icon("Icon.ico");
        trayIcon.Text = "FatedLauncher";
        trayIcon.Visible = true;

        ContextMenuStrip menu = new ContextMenuStrip();

        // Super Generator
        string superGeneratorDirectory = Path.Combine(builtDirectory, "SuperGenerator");
        string superGeneratorLaunch = GetFindReleaseOrDebugLocation(superGeneratorDirectory, "SuperGenerator");
        if(!string.IsNullOrWhiteSpace(superGeneratorLaunch))
        {
            menu.Items.Add("Run SuperGenerator", null, (s, e) => RunExe(superGeneratorLaunch));
        }

        // Super Game Engine Generation
        string sgeRegeneratePath = Path.Combine(StandardFilePaths.RepositoryDirectory(), "SuperGameEngine", "Regenerate");
        if(!File.Exists(sgeRegeneratePath))
        {
            sgeRegeneratePath = Path.Combine(StandardFilePaths.RepositoryDirectory(), "SuperGameEngine", "Generate-Tools-With-Tests.bat");
            if (!File.Exists(sgeRegeneratePath))
            {
                sgeRegeneratePath = string.Empty;
            }
        }
        
        if(sgeRegeneratePath != string.Empty)
        {
            menu.Items.Add("Generate SuperGameEngine", null, (s, e) => RunExe(superGeneratorLaunch));
        }

        menu.Items.Add("Exit", null, (s, e) => Application.Exit());

        trayIcon.ContextMenuStrip = menu;

        Application.Run();
        trayIcon.Visible = false;
    }

    static void RunExe(string exePath)
    {
        try
        {
            Process.Start(exePath);
        }
        catch (Exception ex)
        {
            MessageBox.Show($"Error: {ex.Message}");
        }
    }

    static string GetFindReleaseOrDebugLocation(string launchPath, string exePrefix)
    {
        string release = Path.Combine(launchPath, "Release");
        try
        {
            if (Directory.Exists(release))
            {
                release = Path.Combine(release, $"{exePrefix}_release.exe");
                try
                {
                    if (File.Exists(release))
                    {
                        return release;
                    }
                }
                catch (Exception ex)
                {

                }
            }
        }
        catch (Exception ex)
        {

        }

        string debug = Path.Combine(launchPath, "Debug");
        try
        {
            if (Directory.Exists(debug))
            {
                debug = Path.Combine(debug, $"{exePrefix}_debug.exe");
                try
                {
                    if (File.Exists(debug))
                    {
                        return debug;
                    }
                }
                catch (Exception ex)
                {

                }
            }
        }
        catch (Exception ex)
        {

        }

        return string.Empty;
    }
}