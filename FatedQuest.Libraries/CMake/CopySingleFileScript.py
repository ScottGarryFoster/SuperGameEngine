import os
import shutil
import sys
from pathlib import Path


def CopySingleFileScript(sourceFilepath: str, destination: str, forceOverride: bool, addToDirectory: bool):
    """
    Copies one directory to another.

    Args:
        sourceFilepath (string): A single filepath
        destination (string): Place to copy to, directory.
        forceOverride (bool): If True, always overwrite destination, false only when newer.
        addToDirectory (bool): If True, files will be added to destination, false directory is deleted first.
    """
    sourcePath = Path(sourceFilepath).resolve()
    destinationPath = Path(destination).resolve()

    if not sourcePath.exists() or not sourcePath.is_file():
        print(f"Error: Source file path '{source}' does not exist or is not a file.")
        return

    # If the destination is a directory, copy the file inside it
    if destinationPath.is_dir():
        destinationPath = destinationPath / sourcePath.name

        # Ensure the destination directory exists
    destinationPath.parent.mkdir(parents=True, exist_ok=True)

    if destinationPath.exists():
        if forceOverride or sourcePath.stat().st_mtime > destinationPath.stat().st_mtime:
            shutil.copy2(sourcePath, destinationPath)
            print(f"Success: Copied (overwritten): {sourcePath} -> {destinationPath}")
        else:
            print(f"Success: Skipped (not newer): {sourcePath}")
    else:
        shutil.copy2(sourcePath, destinationPath)
        print(f"Success: Copied: {sourcePath} -> {destinationPath}")


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python CopySingleFileScript "
              "<sourceFilepath:string> "
              "<destination:string> "
              "<forceOverride:[true|false]> "
              "<addToDirectory:[true|false]>")
        sys.exit(1)

    sourceFilepath = sys.argv[1]
    destinationDirectory = sys.argv[2]
    forceOverride = sys.argv[3].lower() in ('true', '1', 'yes') if len(sys.argv) == 5 else False
    addToDirectory = sys.argv[4].lower() in ('true', '1', 'yes') if len(sys.argv) == 5 else True

    CopySingleFileScript(sourceFilepath, destinationDirectory, forceOverride, addToDirectory)
