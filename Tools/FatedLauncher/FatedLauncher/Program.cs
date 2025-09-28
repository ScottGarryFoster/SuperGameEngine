using FatedQuestLibraries;
using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

class FatedLauncher
{
    static public IFilePaths StandardFilePaths;

    [STAThread]
    static void Main()
    {
        StandardFilePaths = new FilePaths();
        string builtDirectory = Path.Combine(StandardFilePaths.RepositoryDirectory(), "built");

        System.Windows.Forms.Application.EnableVisualStyles();
        System.Windows.Forms.Application.SetCompatibleTextRenderingDefault(false);

        NotifyIcon trayIcon = new NotifyIcon();
        trayIcon.Icon = new Icon("Icon.ico");
        trayIcon.Text = "FatedLauncher";
        trayIcon.Visible = true;

        ContextMenuStrip menu = new ContextMenuStrip();
        menu.Renderer = new DarkModeRenderer();

        menu.Items.Add(MakeHeading("Fated Launcher"));
        RunSuperGenerator(builtDirectory, menu);

        menu.Items.Add(MakeHeading("Generate"));
        GenerateSuperGameEngine(menu);
        GenerateDocumentationSiteGenerator(menu);

        ToolStripMenuItem exit = new ToolStripMenuItem("Exit", null, (s, e) => System.Windows.Forms.Application.Exit());
        exit.Enabled = true;
        exit.Font = new Font(exit.Font, FontStyle.Bold);
        exit.ForeColor = Color.White;
        menu.Items.Add(exit);

        trayIcon.ContextMenuStrip = menu;

        System.Windows.Forms.Application.Run();
        trayIcon.Visible = false;
    }

    private static void GenerateDocumentationSiteGenerator(ContextMenuStrip menu)
    {
        // Documentation Site Generator Generation
        string sgeRegeneratePath = Path.Combine(StandardFilePaths.RepositoryDirectory(), "Tools", "DocumentationSiteGenerator", "Regenerate");
        if (!File.Exists(sgeRegeneratePath))
        {
            sgeRegeneratePath = Path.Combine(StandardFilePaths.RepositoryDirectory(), "Tools", "DocumentationSiteGenerator", "Generate-With-Tests.bat");
            if (!File.Exists(sgeRegeneratePath))
            {
                sgeRegeneratePath = string.Empty;
            }
        }

        if (sgeRegeneratePath != string.Empty)
        {
            menu.Items.Add(MakeRunable("Generate Documentation Site Generator", sgeRegeneratePath));
        }
    }

    private static void GenerateSuperGameEngine(ContextMenuStrip menu)
    {
        // Super Game Engine Generation
        string sgeRegeneratePath = Path.Combine(StandardFilePaths.RepositoryDirectory(), "SuperGameEngine", "Regenerate");
        if (!File.Exists(sgeRegeneratePath))
        {
            sgeRegeneratePath = Path.Combine(StandardFilePaths.RepositoryDirectory(), "SuperGameEngine", "Generate-Tools-With-Tests.bat");
            if (!File.Exists(sgeRegeneratePath))
            {
                sgeRegeneratePath = string.Empty;
            }
        }

        if (sgeRegeneratePath != string.Empty)
        {
            menu.Items.Add(MakeRunable("Generate SuperGameEngine", sgeRegeneratePath));
        }
    }

    private static void RunSuperGenerator(string builtDirectory, ContextMenuStrip menu)
    {
        // Super Generator
        string superGeneratorDirectory = Path.Combine(builtDirectory, "SuperGenerator");
        string superGeneratorLaunch = GetFindReleaseOrDebugLocation(superGeneratorDirectory, "SuperGenerator");
        if (!string.IsNullOrWhiteSpace(superGeneratorLaunch))
        {
            menu.Items.Add(MakeRunable("Run SuperGenerator", superGeneratorLaunch));
        }
    }

    static void RunExe(string exePath)
    {
        if(!File.Exists(exePath))
        {
            MessageBox.Show($"File not found {exePath}");
            return;
        }

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

    private static ToolStripMenuItem MakeHeading(string text)
    {
        ToolStripMenuItem heading = new ToolStripMenuItem(text);
        heading.Enabled = true;
        heading.Font = new Font(heading.Font, FontStyle.Bold);
        heading.BackColor = Color.FromArgb(54, 19, 90);
        heading.ForeColor = Color.FromArgb(202, 178, 251);

        return heading;
    }

    private static ToolStripMenuItem MakeRunable(string text, string run)
    {
        ToolStripMenuItem heading = new ToolStripMenuItem(text);
        heading.Enabled = true;
        heading.Font = new Font(heading.Font, FontStyle.Bold);
        heading.ForeColor = Color.White;

        heading.Click += (s, e) => RunExe(run);

        return heading;
    }
}