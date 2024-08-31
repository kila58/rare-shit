@echo off

echo Creating dirctory on system drive...
mkdir "%SystemDrive%\PCS"

echo Copying PCS files
copy /V /Y /B "%CD%\PCS.dll" "%SystemDrive%\PCS\PCS.dll"
copy /V /Y /B "%CD%\PCSinjector.exe" "%SystemDrive%\PCS\PCSinjector.exe"
copy /V /Y /B "%CD%\__keys__.lua" "%SystemDrive%\PCS\__keys__.lua"
copy /V /Y /B "%CD%\__helpers__.lua" "%SystemDrive%\PCS\__helpers__.lua"
copy /V /Y /B "%CD%\__init__.lua" "%SystemDrive%\PCS\__init__.lua"
copy /V /Y /B "%CD%\functions.txt" "%SystemDrive%\PCS\functions.txt"
copy /V /Y /B "%CD%\lua5.1.dll" "%SystemDrive%\PCS\lua5.1.dll"

pause >nul
