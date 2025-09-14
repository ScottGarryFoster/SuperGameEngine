@echo off
pip install psutil
python KillApplication.py %*
set EXITCODE=%ERRORLEVEL%
exit /b %EXITCODE%