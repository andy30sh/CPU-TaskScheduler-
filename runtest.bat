@echo off
cls
g++ ./scheduler.cpp -o ./scheduler.exe

baseline.exe ./data_1.txt ./out_1.txt
baseline.exe ./data_2.txt ./out_2.txt
baseline.exe ./data_3.txt ./out_3.txt
baseline.exe ./data_4.txt ./out_4.txt
baseline.exe ./data_5.txt ./out_5.txt

scheduler.exe ./data_1.txt ./my_1.txt
scheduler.exe ./data_2.txt ./my_2.txt
scheduler.exe ./data_3.txt ./my_3.txt
scheduler.exe ./data_4.txt ./my_4.txt
scheduler.exe ./data_5.txt ./my_5.txt

echo "Test 1"
Rem echo "Baseline" 
.\compute_stats.exe .\data_1.txt .\out_1.txt
Rem echo "Schedule" 
.\compute_stats.exe .\data_1.txt .\my_1.txt 
echo "-------------------------------------------"


echo "Test 2"
Rem echo "Baseline" 
.\compute_stats.exe .\data_2.txt .\out_2.txt
Rem echo "Schedule" 
.\compute_stats.exe .\data_2.txt .\my_2.txt 
echo "-------------------------------------------"


echo "Test 3"
Rem echo "Baseline" 
.\compute_stats.exe .\data_3.txt .\out_3.txt
Rem echo "Schedule" 
.\compute_stats.exe .\data_3.txt .\my_3.txt 
echo "-------------------------------------------"


echo "Test 4"
Rem echo "Baseline" 
.\compute_stats.exe .\data_4.txt .\out_4.txt
Rem echo "Schedule" 
.\compute_stats.exe .\data_4.txt .\my_4.txt 
echo "-------------------------------------------"


echo "Test 5"
Rem echo "Baseline" 
.\compute_stats.exe .\data_5.txt .\out_5.txt
Rem echo "Schedule" 
.\compute_stats.exe .\data_5.txt .\my_5.txt 