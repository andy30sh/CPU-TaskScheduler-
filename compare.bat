@echo off
cls
echo "Baseline" 
.\compute_stats.exe .\data_1111.txt .\out_1111.txt
echo "Schedule" 
.\compute_stats.exe .\data_1111.txt .\my_1111.txt 