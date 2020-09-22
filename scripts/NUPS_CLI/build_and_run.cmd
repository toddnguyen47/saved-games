@echo off

mkdir build
cd build
cmake -G "Ninja" ../
cmake --build .
if errorlevel 0 (
  set gba_path="C:\Users\i1A771792\Downloads\Fire-Emblem-The-Sacred-Stones-vanilla.GBA"
  set ups_path="C:\Users\i1A771792\Downloads\FE8-Rebalanced-1.0.5.ups"
  .\test\NupsCli.exe --gba %gba_path%  --ups %ups_path%
)
cd ..
