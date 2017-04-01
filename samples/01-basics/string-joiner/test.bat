rem @echo off
SET program="%~1"
if %program% == "" goto err

%program% > out.txt
if ERRORLEVEL 1 goto testFailed
fc.exe out.txt empty.txt
if ERRORLEVEL 1 goto testFailed

%program% Hello > out.txt
if ERRORLEVEL 1 goto testFailed
fc.exe out.txt hello.txt
if ERRORLEVEL 1 goto testFailed

%program% Hello " world" ! > out.txt
if ERRORLEVEL 1 goto testFailed
fc.exe out.txt helloworld!.txt
if ERRORLEVEL 1 goto testFailed


echo OK
exit /B

:testFailed
echo Testing failed
exit /B

:err
echo Usage: test.bat <Path to program>
