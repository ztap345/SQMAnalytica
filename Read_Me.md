## SQMAnalytica V1
### Author: Zack Pater

# To run:
### open the Capstone.sln file in Visual Studios
### click the green arrow in the toolbar at the top
*NOTE*: running in Debug mode is slower than running in Release mode (can be changed with the dropdown menu in VS)
*NOTE*: must run in x86 mode. The version of SFML being used does not support X64 (would only matter if running on extremely large data sets)

# To choose input files:
### create an ifstream object with the file path and name
ex:
```c++
//file inside Capstone folder with source
ifstream data("filename.txt")
//file on machine. make sure to use \\ to escape the \(backslash). 
ifstream data("C:\\my\\file\\path\\filename.txt")
```
*NOTE*: Drive letter not always C
### add file to the dataCollection vector
ex:
```c++
//reference it as a pointer using &
dataCollection.push_back(&data)
```

# To choose output files:
### change argument in SQM.Output()
ex:
```c++
//must be different from input file otherwise it will overwrite log data
SQM.Output("C:\\my\\output\\path\\filename.txt")
```