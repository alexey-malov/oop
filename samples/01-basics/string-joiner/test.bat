rem @echo off
SET program="%~1"
if %program% == "" goto err

%program% > out.txt || goto testFailed
fc.exe out.txt empty.txt || goto testFailed

%program% Hello > out.txt || goto testFailed
fc.exe out.txt hello.txt || goto testFailed

%program% Hello " world" ! > out.txt
if ERRORLEVEL 1 goto testFailed
fc.exe out.txt helloworld!.txt
if ERRORLEVEL 1 goto testFailed


echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bat <Path to program>
exit /B 1