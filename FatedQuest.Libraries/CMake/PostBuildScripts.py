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

def FindCSharpProjectFiles(directory):
    """
    Finds all C Sharp files in a given directory

    Args:
        directory (string): the directory to search for C Sharp projects.

    Returns:
        All project files found in the given directory.
    """
    projectFiles = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".csproj"):
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

def CleanCSProjFile(filePath, debug=False):
    """
    Remove all <ItemGroup CMakeLists.txt> entries from the given .csproj file.

    Args:
        filePath: Path to the .csproj file.
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
            customBuilds = itemGroup.findall("msbuild:None", namespace)
            for customBuild in customBuilds:
                include = customBuild.get("Include", "").lower()
                if include.endswith("cmakelists.txt"):
                    if debug:
                        print(f"DEBUG: Found <ItemGroup None> in {filePath}, removing it.")
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
                print(f"DEBUG: Removed {removedEntries} <ItemGroup> <None> entries from {filePath}")
            return True
        else:
            if debug:
                print(f"DEBUG: No <ItemGroup None cmakelists.txt> entries found in {filePath}")
            return False


    except Exception as e:
        print(f"ERROR: Exception occurred while processing {filePath}: {e}")
        return False
        
def CleanCSProjFileNoConsole(filePath, debug=False):
    """
    Ensure that the given .csproj file has <OutputType>WinExe</OutputType>.

    Args:
        filePath: Path to the .csproj file.
        debug: True means more debug logs will be printed.

    Returns:
        True if modified/written successfully, False otherwise.
    """
    import os, xml.etree.ElementTree as ET

    if not filePath or not os.path.isfile(filePath):
        print(f"ERROR: Invalid file path: {filePath}")
        return False

    try:
        if debug:
            print(f"DEBUG: Attempting to open {filePath}")

        tree = ET.parse(filePath)
        root = tree.getroot()

        # Standard MSBuild namespace handling
        namespace = {"msbuild": "http://schemas.microsoft.com/developer/msbuild/2003"}
        ET.register_namespace("", namespace["msbuild"])

        ns = "{http://schemas.microsoft.com/developer/msbuild/2003}"

        modified = False

        # Find or create PropertyGroup with OutputType
        propGroups = root.findall(f"{ns}PropertyGroup")
        outputTypeElement = None
        for pg in propGroups:
            ot = pg.find(f"{ns}OutputType")
            if ot is not None:
                outputTypeElement = ot
                break

        if outputTypeElement is not None:
            if outputTypeElement.text == "Exe":
                if debug:
                    print(
                        f"DEBUG: Changing <OutputType> from {outputTypeElement.text} to WinExe in {filePath}"
                    )
                outputTypeElement.text = "WinExe"
                modified = True
            else:
                if debug:
                    print(f"DEBUG: Already WinExe in {filePath}")
        else:
            # No OutputType defined, add one into the first PropertyGroup
            if not propGroups:
                # If no property groups exist at all, create one
                pg = ET.SubElement(root, f"{ns}PropertyGroup")
            else:
                pg = propGroups[0]
            ET.SubElement(pg, f"{ns}OutputType").text = "WinExe"
            if debug:
                print(f"DEBUG: Added <OutputType>WinExe</OutputType> to {filePath}")
            modified = True

        if modified:
            tempFile = filePath + ".tmp"
            with open(tempFile, "wb") as file:
                tree.write(file, encoding="utf-8", xml_declaration=True)
                file.flush()
                os.fsync(file.fileno())
            os.replace(tempFile, filePath)  # atomic replace
            return True
        else:
            return False

    except Exception as e:
        print(f"ERROR: Exception occurred while processing {filePath}: {e}")
        return False

def main():
    parser = argparse.ArgumentParser(description="Find all .vcproj files in a given directory.")
    parser.add_argument("directory", nargs="?", default=os.getcwd(), help="Directory to search in (default: current directory)")
    parser.add_argument("--debug", action="store_true", default=False, help="Enable debug logging")
    parser.add_argument("--noconsole", action="store_true", default=False, help="True means any console only application will become a windows application for CSharp")
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

    cSharpProjectFiles = FindCSharpProjectFiles(args.directory)
    if cSharpProjectFiles:
        numberOfReplaces = 0
        for file in cSharpProjectFiles:
            if CleanCSProjFile(file, args.debug):
                numberOfReplaces += 1
            if args.noconsole:
                if CleanCSProjFileNoConsole(file, args.debug):
                    numberOfReplaces += 1

        print(f"Cleaned {numberOfReplaces} files in {args.directory}")
    else:
        print("No .csproj files found.")

    sys.exit(1)

if __name__ == "__main__":
    main()
