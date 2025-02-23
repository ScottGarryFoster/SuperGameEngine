import xml.etree.ElementTree as ET
import sys
import os
import argparse

def FindCProjectFiles(directory):
    """
    Finds all C++ files in a given directory

    Args:
        directory (string): the directory to search for C++ projects.

    Returns:
        All project files found in the given directory.
    """
    projectFiles = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".vcxproj"):
                projectFiles.append(os.path.join(root, file))
    return projectFiles

def CleanProjectFiles(filePath, debug=False):
    """
    Remove all <CustomBuild CMakeLists.txt> entries from the given .vcxproj file.

    Args:
        filePath: Path to the .vcxproj file.
        debug: True means more debug logs will be printed.

    Returns:
        True if the project could be read, false if it could not be read or written.
    """
    if not filePath or not os.path.isfile(filePath):
        print(f"ERROR: Invalid file path: {filePath}")
        return False

    try:
        if debug:
            print(f"DEBUG: Attempting to open {filePath}")
        tree = ET.parse(filePath)
        root = tree.getroot()
        namespace = {"msbuild": "http://schemas.microsoft.com/developer/msbuild/2003"}
        ET.register_namespace("", namespace["msbuild"])

        removedEntries = 0
        for itemGroup in root.findall("msbuild:ItemGroup", namespace):
            customBuilds = itemGroup.findall("msbuild:CustomBuild", namespace)
            for customBuild in customBuilds:
                include = customBuild.get("Include", "").lower()
                if include.endswith("cmakelists.txt"):
                    if debug:
                        print(f"DEBUG: Found <CustomBuild> in {filePath}, removing it.")
                    itemGroup.remove(customBuild)
                    removedEntries += 1

        if removedEntries > 0:
            tempFile = filePath + ".tmp"
            with open(tempFile, "wb") as file:
                tree.write(file, encoding="utf-8", xml_declaration=True)
                file.flush()
                os.fsync(file.fileno())  # Force write to disk

            os.replace(tempFile, filePath)  # Ensure atomic replacement
            if debug:
                print(f"DEBUG: Removed {removedEntries} <CustomBuild> entries from {filePath}")
            return True
        else:
            if debug:
                print(f"DEBUG: No <CustomBuild cmakelists.txt> entries found in {filePath}")
            return False


    except Exception as e:
        print(f"ERROR: Exception occurred while processing {filePath}: {e}")
        return False

def main():
    parser = argparse.ArgumentParser(description="Find all .vcproj files in a given directory.")
    parser.add_argument("directory", nargs="?", default=os.getcwd(), help="Directory to search in (default: current directory)")
    parser.add_argument("--debug", action="store_true", default=False, help="Enable debug logging")
    args = parser.parse_args()
    
    projectFiles = FindCProjectFiles(args.directory)
    if projectFiles:
        numberOfReplaces = 0
        for file in projectFiles:
            if CleanProjectFiles(file, args.debug):
                numberOfReplaces += 1
        print(f"Cleaned {numberOfReplaces} files in {args.directory}")
    else:
        print("No .vcxproj files found.")
    sys.exit(1)

if __name__ == "__main__":
    main()
