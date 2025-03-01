cmake -S . -B build
python ../FatedQuest.Libraries/CMake/PostBuildScripts.py build/

Rem Copy Runtime SDL2
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2redistnuget-src\build\native\bin\x64 build\SuperGameEngine\Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2redistnuget-src\build\native\bin\x64 build\SuperGameEngine\Release false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2redistnuget-src\build\native\bin\x64 build\SuperGameEngine\Tools_Debug false

Rem Copy Runtime SDL2 Image
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2imageredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2imageredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Release false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2imageredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Tools_Debug false

Rem Copy Runtime SDL2 Mixer
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2mixerredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2mixerredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Release false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2mixerredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Tools_Debug false

Rem Copy Runtime Zlib
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\zlibredistnuget-src\build\native\bin\x64\Debug build\SuperGameEngine\Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\zlibredistnuget-src\build\native\bin\x64\Release build\SuperGameEngine\Debug false

python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\zlibredistnuget-src\build\native\bin\x64\Debug build\SuperGameEngine\Tools_Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\zlibredistnuget-src\build\native\bin\x64\Release build\SuperGameEngine\Tools_Debug false

python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\zlibredistnuget-src\build\native\bin\x64\Release build\SuperGameEngine\Release false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\zlibredistnuget-src\build\native\bin\x64\Debug build\SuperGameEngine\Release false


pause