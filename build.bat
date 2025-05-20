setlocal

md BuildResults
md %temp%\ExtendedUnreal
for %%a in (4.27 5.0 5.1 5.2 5.3 5.4 5.5) do call :build %%a
rd /s /q %temp%\ExtendedUnreal
goto :eof

:build
set epic=
for /f "tokens=2* skip=2" %%a in ('reg query "HKLM\SOFTWARE\EpicGames\Unreal Engine\%1" /v "InstalledDirectory"') do set epic=%%b
if "%epic%"=="" goto :eof
md %temp%\ExtendedUnreal\%1
call "%epic%\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Plugin="%CD%\ExtendedUnreal.uplugin" -Package="%temp%\ExtendedUnreal\%1" -Rocket >BuildResults\LogBuild-%1.txt
rd /s /q %temp%\ExtendedUnreal\%1\Binaries
rd /s /q %temp%\ExtendedUnreal\%1\Intermediate
md %temp%\ExtendedUnreal\%1\Config
copy Config\FilterPlugin.ini %temp%\ExtendedUnreal\%1\Config\FilterPlugin.ini
del ExtendedUnreal-%1.zip
if not exist %temp%\ExtendedUnreal\%1\ExtendedUnreal.uplugin goto :eof
tar -a -c -f BuildResults\ExtendedUnreal-%1.zip -C %temp%\ExtendedUnreal\%1\ *
goto :eof
