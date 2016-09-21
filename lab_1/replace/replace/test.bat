set PROGRAM="%~1"

%PROGRAM% empty.txt %TEMP%\empty.txt
if NOT ERRORLEVEL 1 goto err         

%PROGRAM% input.txt %TEMP%\output.txt "ma" "mama"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt mama.txt
if ERRORLEVEL 1 goto err

%PROGRAM% input.txt %TEMP%\output.txt "1231234" "LOOK"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt nums.txt
if ERRORLEVEL 1 goto err

%PROGRAM% input.txt %TEMP%\output.txt "heathens" ""
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt without_heathens.txt
if ERRORLEVEL 1 goto err

%PROGRAM% input.txt %TEMP%\output.txt "You" "NO ONE"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt without_you.txt
if ERRORLEVEL 1 goto err

%PROGRAM% non-existing.txt %TEMP%\output.txt "search string" "replace string" > %TEMP%\non-existing.txt
IF NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\non-existing.txt expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1