set PROGRAM="%~1"

rem check empty file
%PROGRAM% input\empty.txt > %TEMP%\empty.txt
if NOT ERRORLEVEL 1 goto err         

rem check matrix with determinant = 0
%PROGRAM% input\zero.txt > %TEMP%\zero.txt 
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\zero.txt output\zero.txt
if ERRORLEVEL 1 goto err

rem check matrix with determinant close to 0
%PROGRAM% input\small.txt > %TEMP%\small.txt 
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\small.txt output\small.txt
if ERRORLEVEL 1 goto err

rem check normal matrix
%PROGRAM% input.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt output\output.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1