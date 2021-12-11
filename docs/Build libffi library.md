# Build libffi library

- Step 1: Make sure that cygwin(64) is installed (including the tool "make", category Devel)
- Step 2: Download the latest release from https://github.com/libffi/libffi and unpacked it to a preferred location
- Step 3: Note the preferred location as cygwin path in a notepad (a next step uses it)
  - Example: Windows folder: c:\\my_folder\\libffi\\... is in Cygwin: /cygdrive/c/my_folder/libffi/...
- Step 4: Search for the prepared command line tool from Visual Studio
  - VS2022 (Preview) C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2022\Visual Studio Tools\VC
    - x64 -> x64 Native Tools Command Prompt for VS 2022 Preview
    - x86 -> x86 Native Tools Command Prompt for VS 2022 Preview
  - VS2019 C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2019\Visual Studio Tools\VC
    - x64 -> x64 Native Tools Command Prompt for VS 2019
    - x86 -> x86 Native Tools Command Prompt for VS 2019
  - VS2017 C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2017\Visual Studio Tools\VC
    - See above, same structure
- Step 5: Open the command line as described in step 4
- Step 6: Enter the following command sequences in the command line tool
  - cd to the unpacked location from step 2
  - Execute the following command and replacing {MY_CYGWIN_PATH} by the noted cygwin path from step 3 (code is for x64):  ``c:\cygwin64\bin\sh -lc "(cd $OLDPWD; ./configure CC='{MY_CYGWIN_PATH}/msvcc.sh -m64' CXX='{MY_CYGWIN_PATH}/msvcc.sh -m64' LD='link' CPP='cl -nologo -EP' CXXCPP='cl -nologo -EP' CPPFLAGS='-DFFI_BUILDING_DLL' NM='dumpbin -symbols' STRIP=':' --build='x86_64-w64-cygwin' --host='x86_64-w64-cygwin' --disable-debug --enable-shared --disable-static --disable-dependency-tracking)"``
  - ``c:\cygwin64\bin\sh -lc "(cd $OLDPWD; make)"``
- Step 7: Copy the artifacts from this proces into the SmartIO project
  - All c/c++ headers from [unpacked folder]/x86_64-w64-cygwin\include to [source location]\SmartIO\SmartIO\libs\libffi\includes
  - libffi-{version}.lib from [unpacked folder]/x86_64-w64-cygwin\\.libs to [source location]\SmartIO\SmartIO\libs\libffi
  - libffi-{version}.dll from [unpacked folder]/x86_64-w64-cygwin\\.libs to [source location]\SmartIO\SmartIO\libs\libffi
- Step 8: We are done and we can delete the unpacked and download folder

## Possible adjustments
 - x86 (32 bits):
   - Change the command from step 6:
     - Remove the "-m64" part (two times, CC and CXX)
     - Change "x86_64-w64-cygwin" into "i686-pc-cygwin" (two times, build and host)
   - Use the command line tool: x86 Native Tools Command Prompt for VS 20xx
 - Debug info (Step 6)
   - Activate (Debug): --enable-debug
   - Disable (Release): --disable-debug
 - Library type options:
   - --enable-shared --disable-static
   - --enable-static --disable-shared

More info: https://github.com/libffi/libffi/blob/master/.appveyor.yml