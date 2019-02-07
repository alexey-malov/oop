@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

:: Тестируем имя из одного слова
%PROGRAM% < Boris.txt > %OUT% || goto err
fc %OUT% Boris-out.txt || goto err

:: Тестируем имя из нескольких слов
%PROGRAM% < HarryPotter.txt > %OUT% || goto err
fc %OUT% HarryPotter-out.txt || goto err

:: Тестируем пустое имя
%PROGRAM% < Empty.txt > %OUT% || goto err
fc %OUT% Empty-out.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
