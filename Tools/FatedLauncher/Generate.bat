@echo off
setlocal

rem Call CMake including the Tools Chain.
cmake -B build 
python ../../FatedQuest.Libraries/CMake/PostBuildScripts.py build/ --noconsole

pause