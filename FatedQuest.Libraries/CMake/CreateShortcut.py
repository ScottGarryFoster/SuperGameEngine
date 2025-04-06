import sys
import os
import subprocess

def CreateShortcut(source, destination):
    """
    Creates a windows shortcut.

    Args:
        source (string): Path to the location to launch.
        destination (string): Path to the new shortcut.
    """

    # Ensure destination ends with .lnk
    if not destination.lower().endswith(".lnk"):
        destination += ".lnk"

    source = os.path.abspath(source)
    destination = os.path.abspath(destination)
    working_dir = os.path.dirname(source)

    powershell_script = f'''
        $WScriptShell = New-Object -ComObject WScript.Shell
        $Shortcut = $WScriptShell.CreateShortcut("{destination}")
        $Shortcut.TargetPath = "{source}"
        $Shortcut.WorkingDirectory = "{working_dir}"
        $Shortcut.IconLocation = "{source},0"
        $Shortcut.Save()
        '''

    subprocess.run(["powershell", "-NoProfile",
                    "-ExecutionPolicy", "Bypass",
                    "-Command", powershell_script],
                    check=True)
    print(f"Shortcut created: {destination}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python CreateShortcut <sourcePathToLaunch:string> <destinationOfShortcut:string>")
        sys.exit(1)

    source = sys.argv[1]
    destination = sys.argv[2]

    CreateShortcut(source, destination)