set PROGRAM="%~1"

%PROGRAM% input\wrong-argv.txt "must be error" > %TEMP%\wrong-argv.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\wrong-argv.txt output\wrong-argv.txt
if ERRORLEVEL 1 goto err

%PROGRAM% input\empty.txt > %TEMP%\empty.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt output\empty.txt
if ERRORLEVEL 1 goto err

%PROGRAM% input\fail-in-reading.txt > %TEMP%\fail-in-reading.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\fail-in-reading.txt output\fail-in-reading.txt
if ERRORLEVEL 1 goto err

%PROGRAM% input\non-existing.txt > %TEMP%\non-existing.txt
IF NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\non-existing.txt output\expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

rem check normal matrix
%PROGRAM% input\input.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt output\output.txt
if ERRORLEVEL 1 goto err

rem check normal matrix
%PROGRAM% input\input2.txt > %TEMP%\output2.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output2.txt output\output2.txt
if ERRORLEVEL 1 goto err

rem check matrix with determinant = 0
%PROGRAM% input\zero.txt > %TEMP%\zero.txt 
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\zero.txt output\zero.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1