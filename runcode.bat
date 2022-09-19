@echo off
cls
g++ ./scheduler.cpp -o ./scheduler.exe
scheduler.exe ./data_1111.txt ./my_1111.txt


echo "Baseline" 
.\compute_stats.exe .\data_1111.txt .\out_1111.txt
echo "Schedule" 
.\compute_stats.exe .\data_1111.txt .\my_1111.txt 