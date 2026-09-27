@echo off
echo Building K-Way Merge vs Pairwise Merge C Project...
gcc src/main.c src/k_way_merge.c src/pairwise_merge.c -o main.exe
if %ERRORLEVEL% EQU 0 (
    echo Build successful! Executing...
    echo.
    main.exe
) else (
    echo Build failed!
)
