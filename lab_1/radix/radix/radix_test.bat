set PROGRAM="%~1"

%PROGRAM% 16 10 ff > %TEMP%\output.txt
fc %TEMP%\output.txt out1.txt
if ERRORLEVEL 1 goto err

rem data incorrectly the value of "f" = 15 and radix = 12
%PROGRAM% 12 10 ff > %TEMP%\output.txt
fc %TEMP%\output.txt out2.txt
if ERRORLEVEL 1 goto err

rem int_max = 2147483647
%PROGRAM% 10 16 2147483647 > %TEMP%\output.txt
fc %TEMP%\output.txt out3.txt
if ERRORLEVEL 1 goto err

rem overflow int > int_max 
%PROGRAM% 10 16 214748364553 > %TEMP%\output.txt
fc %TEMP%\output.txt out4.txt
if ERRORLEVEL 1 goto err

rem underflow int = int_MIN
%PROGRAM% 10 16 -2147483648 > %TEMP%\output.txt
fc %TEMP%\output.txt out5.txt
if ERRORLEVEL 1 goto err

rem underflow int < int_MIN
%PROGRAM% 10 16 -2147483648462 > %TEMP%\output.txt
fc %TEMP%\output.txt out6.txt
if ERRORLEVEL 1 goto err

rem input 0
%PROGRAM% 10 16 0 > %TEMP%\output.txt
fc %TEMP%\output.txt out7.txt
if ERRORLEVEL 1 goto err

rem input ABCZDH in 36 radix
%PROGRAM% 36 10 ABCZDH > %TEMP%\output.txt
fc %TEMP%\output.txt out8.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 36 2  > %TEMP%\output.txt
fc %TEMP%\output.txt out9.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1