@ECHO OFF
xcopy "Z:\Repo\repository\include\iris" "%~dp0include\iris" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\glad" "%~dp0include\glad" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\KHR" "%~dp0include\KHR" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\SDL2" "%~dp0include\SDL2" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\png.h" "%~dp0include" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\pngconf.h" "%~dp0include" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\pngdebug.h" "%~dp0include" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\pnginfo.h" "%~dp0include" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\pnglibconf.h" "%~dp0include" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\pngpriv.h" "%~dp0include" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\pngstruct.h" "%~dp0include" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\include\zlib.h" "%~dp0include" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\libs\libpng.a" "%~dp0libs" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\libs\libSDL2.a" "%~dp0libs" /R /Y /F /I /Q /S
xcopy "Z:\Repo\repository\libs\libz.a" "%~dp0libs" /R /Y /F /I /Q /S
PAUSE