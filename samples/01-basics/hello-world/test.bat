set program="%~1"

%program% > %temp%\hello.txt 
if ERRORLEVEL 1 goto err
fc.exe %temp%\hello.txt expected-output.txt
if ERRORLEVEL 1 goto err

rem сюда попадем в случае успеха
echo Program testing succeeded
rem сообщаем вызывающей программе (Visual Studio) об успехе
exit /B 0

rem сюда попадем в случае ошибки
err:
echo Program testing failed
rem сообщаем вызывающей программе (Visual Studio) о неудаче
exit /B 1