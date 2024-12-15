# Summary
This readme goes over current instructions of how to create a library project.

# Automatic
This is still the works. At some point Project-Generate will create these files for us.

# Manual

1. Open Solution -> Add Project or Open Visual Studio and Create a Project
2. Select a Static C++ Library Project and place it within the FatedQuest.Libraries directory
3. Right click the project -> Properties. The rest of these instructions are in this panel.
4. In General -> C++ Language Standard -> ISO C++ 20
5. C/C++ -> Advanced -> Forced Include File -> Enter "pch.h"

This is it. Include you file in the solutions you require and everything should work.