import re
import argparse


def UpdatePaths(inputPath, outputPath, newRelativeDirectory):
    """
    Updates a Visual Studio .sln file to prepend a prefix to project paths.

    Args:
        inputPath: Path to the Visual Studio .sln file
        outputPath: Path to the project folder including the .sln filename
        newRelativeDirectory: Path to the new project folder including the .sln filename
    """

    # Regex pattern for Project lines:
    # Group 1: Project type GUID and name part (Everything before the Relative path)
    # Group 2: The actual relative path to the project file
    # Group 3: The project GUID part (Everything after the Relative path)
    projectMatcher = re.compile(
        r'(Project\("{[^"]+}"\) = "[^"]+", )"([^"]+)"(, "{[^"]+}")'
    )

    try:
        # Read the existing lines of the file.
        with open(inputPath, 'r', encoding='utf-8-sig') as file:
            lines = file.readlines()

        newLines = []
        for line in lines:

            # Looks for Project definitions
            match = projectMatcher.match(line)
            if match:
                firstSectionOfLineMatch = match.group(1)
                pathToProjectMatch = match.group(2)
                restOfTheLineMatch = match.group(3)

                # Check if it's already prefixed to avoid build\build\path
                if not pathToProjectMatch.startswith(newRelativeDirectory):

                    # Combine prefix and path, ensuring path separators are handled
                    # Visual Studio uses backslashes for paths
                    cleanRelativeDirectory = newRelativeDirectory.strip('\\').strip('/')
                    newPathToProject = f"{cleanRelativeDirectory}\\{pathToProjectMatch}"

                    # Construct the new line
                    completeLine = f'{firstSectionOfLineMatch}"{newPathToProject}"{restOfTheLineMatch}\n'
                    newLines.append(completeLine)
                else:
                    newLines.append(line)
            else:
                newLines.append(line)

        # Write the new file out. This happens regardless.
        with open(outputPath, 'w', encoding='utf-8-sig') as f:
            f.writelines(newLines)

        print(f"Successfully created: {outputPath}")

    except Exception as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Prefix project paths in a VS Solution file.")
    parser.add_argument("input", help="Path to the source .sln file")
    parser.add_argument("output", help="Path to the output .sln file")
    parser.add_argument("--prefix", default="build", help="Prefix to add (default: build)")

    args = parser.parse_args()
    UpdatePaths(args.input, args.output, args.prefix)