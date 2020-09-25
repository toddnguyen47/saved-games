@echo off

mkdir build
cd build
cmake -G "Ninja" ../
cmake --build .
if errorlevel 0 (
  set gba_path="Z:\DocumentsAndStuff\Downloads\bruh\FE8-Clean.gba"
  set ups_path="Z:\DocumentsAndStuff\Downloads\bruh\FE8-Rebalanced-1.0.5.ups"
  .\test\NupsCli.exe --gba %gba_path%  --ups %ups_path%
)
cd ..
