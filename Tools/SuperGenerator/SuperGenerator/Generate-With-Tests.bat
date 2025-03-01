cmake -S . -B build -DENABLE_TESTS=ON
python ../../../FatedQuest.Libraries/CMake/PostBuildScripts.py build/
pause