set OUT_DIR=out\build\x64-Debug
mkdir %OUT_DIR%
cmake -B%OUT_DIR% -S.
cmake --build %OUT_DIR% --config Debug
rename %OUT_DIR%\Debug bin