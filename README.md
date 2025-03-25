# RSI
for barrier_gate
Add the Batch File to Startup
There are multiple ways to add the batch file to the Windows startup process. Choose one of the following methods:

Method 1: Use the Startup Folder
1.Press Win + R, type shell:startup, and press Enter. This opens the Startup folder .
2. Copy the batch file (app_autorun.bat) into this folder.
   -Alternatively, you can create a shortcut to the batch file and place the shortcut in the Startup folder.
3. Restart your computer to test if the script runs automatically.

Method 2: Use the Registry Editor
1. Press Win + R, type regedit, and press Enter to open the Registry Editor .
2. Navigate to the following key:
   - HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
3. Right-click on the right pane, select New > String Value, and name it something like BarcodeAutorun.
4. Double-click the new string value and set its value to the full path of the batch file:
   - C:\path\to\your\barcode_autorun.bat
5. Close the Registry Editor and restart your computer to test.
