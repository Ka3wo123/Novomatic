set OUT_DIR=out\build\x64-Debug

if not exist "%OUT_DIR%" (
    mkdir "%OUT_DIR%"
)

cmake -B"%OUT_DIR%" -S.
cmake --build "%OUT_DIR%" --config Debug

copy .\SFML\bin %OUT_DIR%\Debug\
