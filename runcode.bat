@echo off
cls
g++ ./scheduler.cpp -o ./scheduler.exe
scheduler.exe ./data_1111.txt ./my_1111.txt
scheduler.exe ./data_2222.txt ./my_2222.txt
scheduler.exe ./data_3333.txt ./my_3333.txt

echo "Data 1"
Rem echo "Baseline" 
.\compute_stats.exe .\data_1111.txt .\out_1111.txt
Rem echo "Schedule" 
.\compute_stats.exe .\data_1111.txt .\my_1111.txt 
echo "-------------------------------------------"


echo "Data 2"
Rem echo "Baseline" 
.\compute_stats.exe .\data_2222.txt .\out_2222.txt
Rem echo "Schedule" 
.\compute_stats.exe .\data_2222.txt .\my_2222.txt 
echo "-------------------------------------------"


echo "Data 3"
Rem echo "Baseline" 
.\compute_stats.exe .\data_3333.txt .\out_3333.txt
Rem echo "Schedule" 
.\compute_stats.exe .\data_3333.txt .\my_3333.txt 