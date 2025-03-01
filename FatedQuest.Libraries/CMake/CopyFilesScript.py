import os
import shutil
import sys
from pathlib import Path


def CopyDirectory(source: str, destination: str, forceOverride: bool, addToDirectory: bool):
    """
    Copies one directory to another.

    Args:
        source (string): Source of files, directory.
        destination (string): Place to copy to, directory.
        forceOverride (bool): If True, always overwrite destination, false only when newer.
        addToDirectory (bool): If True, files will be added to destination, false directory is deleted first.
    """
    sourcePath = Path(source).resolve()
    destinationPath = Path(destination).resolve()

    if not sourcePath.exists() or not sourcePath.is_dir():
        print(f"Error: Source directory '{source}' does not exist or is not a directory.")
        return

    # If there is a directory and we are not adding files then delete the files
    if destinationPath.exists() and not addToDirectory:
        shutil.rmtree(destination)

    # When can ensure destination exists.
    if not destinationPath.exists() or not destinationPath.is_dir():
        destinationPath.mkdir(parents=True, exist_ok=True)

    for root, _, files in os.walk(sourcePath):
        relativePath = Path(root).relative_to(sourcePath)
        destinationDirectory = destinationPath / relativePath
        destinationDirectory.mkdir(parents=True, exist_ok=True)

        for file in files:
            sourceFile = Path(root) / file
            destinationFile = destinationDirectory / file

            # If there is no file, do not bother checking the time.
            if destinationFile.exists():
                # forceOverride is false then check the time.
                if forceOverride or sourceFile.stat().st_mtime > destinationFile.stat().st_mtime:
                    shutil.copy2(sourceFile, destinationFile)
                    print(f"Success: Copied (overwritten): {sourceFile} -> {destinationFile}")
                else:
                    print(f"Success: Skipped (not newer): {sourceFile}")
            else:
                shutil.copy2(sourceFile, destinationFile)
                print(f"Success: Copied: {sourceFile} -> {destinationFile}")


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python CopyDirectory "
              "<sourceDirectory:string> "
              "<destination:string> "
              "<forceOverride:[true|false]> "
              "<addToDirectory:[true|false]>")
        sys.exit(1)

    sourceDirectory = sys.argv[1]
    destinationDirectory = sys.argv[2]
    forceOverride = sys.argv[3].lower() in ('true', '1', 'yes') if len(sys.argv) == 5 else False
    addToDirectory = sys.argv[4].lower() in ('true', '1', 'yes') if len(sys.argv) == 5 else True

    CopyDirectory(sourceDirectory, destinationDirectory, forceOverride, addToDirectory)
