# Address Parsing Tool User Guide

1. Using the Python Code

* Open a command prompt and navigate to the directory containing the Python code.
* Run the following command to generate the address_parsing.exe file:
  pyinstaller --onefile --hidden-import=openpyxl --windowed address_parsing.py
* The generated address_parsing.exe file will be located in the ./dist folder.
* You can use the .exe file without needing the Python code.

2. Using the Parsing Tool

* The parsing tool executable (.exe) file is for Windows only.
* Run the .exe file and specify the input file (.txt) and output file (.xlsx).
* Click the button to generate and save the results to an Excel file.
