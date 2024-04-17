# CMake Build Troubleshooting

When building OASIS on your local machine, you may encounter issues during CMake's build process. Here are some suggestions for identifying your issue and resolving it on certain platforms:

## Common Issues and Solutions

### Clang

You may have an outdated version of the clang compiler, and CMake may have trouble linking the source files as a result. For example, clang 14 will prevent CMake from building the project beyond 87% on some machines. Thus, it is recommended to update your version of the clang compiler using homebrew. You can use the `brew install llvm@15` command to install clang 15 on your machine and the `clang --version` command to check the current version of your clang compiler.

[Further reading](https://stackoverflow.com/questions/64225495/how-to-switch-from-apple-to-homebrew-installed-clang)

### Xcode Command Line Tools

Sometimes, issues can arise due to missing or outdated Xcode Command Line Tools. These tools are essential for compiling and building software on macOS. You can ensure that you have the latest version installed by running the `xcode-select --install` in your terminal. This command will prompt you to install the necessary tools if they are not already installed. Once the installation is complete, try building the project again with CMake.

[Further reading](https://stackoverflow.com/questions/32801638/cmake-error-at-cmakelists-txt30-project-no-cmake-c-compiler-could-be-found)

### IDE

If you would prefer to build this project by using the features of IDE instead of running commands in a terminal, the recommended code editor/IDE to work on contributions to OASIS is Visual Studio Code. To properly have CMake build your project, ensure that you have the CMake and CMake Tools extensions installed in Visual Studio Code. Then, hold down shift + command + P on your keyboard to bring down a drop down menu. Next, select the CMake: Configure option to configure the building settings. Do not worry if CMake reports that it could not find libraries; this is normal. Then, bring down the drop down menu again using the same keyboard shortcut and select the CMake: Build option. If all other settings are working correctly, CMake should successfully build OASIS on your computer.

[Further reading](https://stackoverflow.com/questions/73328916/how-to-set-cmake-build-configuration-in-vscode)

Another potential option you may want to consider is Replit. Replit is an online IDE that can be used within your browser. Each Replit project provides you with a shell that can be used to input commands. In addition, it is integrated with a tool called Nix, which manages software packages. As a result, Replit makes it easier to use CMake to build OASIS. For more information, see the "Replit" section below.

# Replit
If you like to build the project via Replit to avoid having to install the necessary software to build it on your local machine, follow these steps:

1. Create a fork of the OASIS repository on GitHub.
2. If you have not done so already, link your Replit account to your GitHub account.
3. On Replit, press the "Create Repl" button and then press the "Import from GitHub" button, selecting your fork of the repository.
4. In the shell, type in the `mkdir build` to create a directory called `build`. Then type in `cd build` to set `build` as the current directory.
5. Enter the `cmake ..` command to generate the build files. It is likely that the shell will alert you that the `cmake` command is not installed. However, it will also inform you that multiple versions of this command were found in Nix. Select the `cmake         3.24.3  Cross-platform, open-source build systr` option and press enter.
6. After the build files have been generated, enter the command `make -j8` to build the project. Note that the flag `-j8` is necessary as building the project is heavy on the CPU and RAM, and the flag denotes you want to allot 8 threads for compiling. Otherwise, the process will likely terminate earlier on with errors.

## Ongoing Issues

In our testing, we have encountered issues with building OASIS on some machines that stem from other factors. We have used the above tests in an attempt to resolve the issue, but none have done so as of yet. We will continue the investiage the issue. As for now, here is a sample terminal output that CMake produces when encountering an error in the build process:

```
[main] Building folder: Oasis 
[build] Starting build
[proc] Executing command: /usr/local/bin/cmake --build /Users/ericmalla/Downloads/GitHub/Oasis/build --config Debug --target all -j 6 --
[build] [  1%] Built target fmt
[build] [  1%] Building CXX object src/CMakeFiles/Oasis.dir/Add.cpp.o
[build] [  3%] Building CXX object src/CMakeFiles/Oasis.dir/Divide.cpp.o
[build] [  3%] Building CXX object src/CMakeFiles/Oasis.dir/Exponent.cpp.o
[build] [  3%] Building CXX object src/CMakeFiles/Oasis.dir/Multiply.cpp.o
[build] [  4%] Building CXX object src/CMakeFiles/Oasis.dir/Log.cpp.o
[build] [ 85%] Built target Catch2
[build] [ 85%] Building CXX object src/CMakeFiles/Oasis.dir/Subtract.cpp.o
[build] clang: error: unable to execute command: Segmentation fault: 11
[build] clang: error: clang frontend command failed due to signal (use -v to see invocation)
[build] Apple clang version 14.0.0 (clang-1400.0.29.202)
[build] Target: x86_64-apple-darwin21.6.0
[build] Thread model: posix
[build] InstalledDir: /Library/Developer/CommandLineTools/usr/bin
[build] clang: error: unable to execute command: Segmentation fault: 11
[build] clang: error: clang frontend command failed due to signal (use -v to see invocation)
[build] Apple clang version 14.0.0 (clang-1400.0.29.202)
[build] Target: x86_64-apple-darwin21.6.0
[build] Thread model: posix
[build] InstalledDir: /Library/Developer/CommandLineTools/usr/bin
[build] clang: error: unable to execute command: Segmentation fault: 11
[build] clang: error: clang frontend command failed due to signal (use -v to see invocation)
[build] Apple clang version 14.0.0 (clang-1400.0.29.202)
[build] Target: x86_64-apple-darwin21.6.0
[build] Thread model: posix
[build] InstalledDir: /Library/Developer/CommandLineTools/usr/bin
[build] clang: error: unable to execute command: Segmentation fault: 11
[build] clang: error: clang frontend command failed due to signal (use -v to see invocation)
[build] Apple clang version 14.0.0 (clang-1400.0.29.202)
[build] Target: x86_64-apple-darwin21.6.0
[build] Thread model: posix
[build] InstalledDir: /Library/Developer/CommandLineTools/usr/bin
[build] clang: error: unable to execute command: Segmentation fault: 11
[build] clang: error: clang frontend command failed due to signal (use -v to see invocation)
[build] Apple clang version 14.0.0 (clang-1400.0.29.202)
[build] Target: x86_64-apple-darwin21.6.0
[build] Thread model: posix
[build] InstalledDir: /Library/Developer/CommandLineTools/usr/bin
[build] clang: error: unable to execute command: Segmentation fault: 11
[build] clang: error: clang frontend command failed due to signal (use -v to see invocation)
[build] Apple clang version 14.0.0 (clang-1400.0.29.202)
[build] Target: x86_64-apple-darwin21.6.0
[build] Thread model: posix
[build] InstalledDir: /Library/Developer/CommandLineTools/usr/bin
[build] clang: note: diagnostic msg: 
[build] ********************
[build] 
[build] PLEASE ATTACH THE FOLLOWING FILES TO THE BUG REPORT:
[build] Preprocessed source(s) and associated run script(s) are located at:
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Log-b9373e.cpp
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Log-b9373e.sh
[build] clang: note: diagnostic msg: Crash backtrace is located in
[build] clang: note: diagnostic msg: /Users/ericmalla/Library/Logs/DiagnosticReports/clang_<YYYY-MM-DD-HHMMSS>_<hostname>.crash
[build] clang: note: diagnostic msg: (choose the .crash file that corresponds to your crash)
[build] clang: note: diagnostic msg: 
[build] 
[build] ********************
[build] make[2]: *** [src/CMakeFiles/Oasis.dir/Log.cpp.o] Error 254
[build] make[2]: *** Waiting for unfinished jobs....
[build] [ 87%] Built target Catch2WithMain
[build] clang: note: diagnostic msg: 
[build] ********************
[build] 
[build] PLEASE ATTACH THE FOLLOWING FILES TO THE BUG REPORT:
[build] Preprocessed source(s) and associated run script(s) are located at:
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Exponent-c9aa47.cpp
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Exponent-c9aa47.sh
[build] clang: note: diagnostic msg: Crash backtrace is located in
[build] clang: note: diagnostic msg: /Users/ericmalla/Library/Logs/DiagnosticReports/clang_<YYYY-MM-DD-HHMMSS>_<hostname>.crash
[build] clang: note: diagnostic msg: (choose the .crash file that corresponds to your crash)
[build] clang: note: diagnostic msg: 
[build] 
[build] ********************
[build] make[2]: *** [src/CMakeFiles/Oasis.dir/Exponent.cpp.o] Error 254
[build] clang: note: diagnostic msg: 
[build] ********************
[build] 
[build] PLEASE ATTACH THE FOLLOWING FILES TO THE BUG REPORT:
[build] Preprocessed source(s) and associated run script(s) are located at:
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Multiply-96f63b.cpp
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Multiply-96f63b.sh
[build] clang: note: diagnostic msg: Crash backtrace is located in
[build] clang: note: diagnostic msg: /Users/ericmalla/Library/Logs/DiagnosticReports/clang_<YYYY-MM-DD-HHMMSS>_<hostname>.crash
[build] clang: note: diagnostic msg: (choose the .crash file that corresponds to your crash)
[build] clang: note: diagnostic msg: 
[build] 
[build] ********************
[build] make[2]: *** [src/CMakeFiles/Oasis.dir/Multiply.cpp.o] Error 254
[build] clang: note: diagnostic msg: 
[build] ********************
[build] 
[build] PLEASE ATTACH THE FOLLOWING FILES TO THE BUG REPORT:
[build] Preprocessed source(s) and associated run script(s) are located at:
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Divide-a10ced.cpp
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Divide-a10ced.sh
[build] clang: note: diagnostic msg: Crash backtrace is located in
[build] clang: note: diagnostic msg: /Users/ericmalla/Library/Logs/DiagnosticReports/clang_<YYYY-MM-DD-HHMMSS>_<hostname>.crash
[build] clang: note: diagnostic msg: (choose the .crash file that corresponds to your crash)
[build] clang: note: diagnostic msg: 
[build] 
[build] ********************
[build] make[2]: *** [src/CMakeFiles/Oasis.dir/Divide.cpp.o] Error 254
[build] clang: note: diagnostic msg: 
[build] ********************
[build] 
[build] PLEASE ATTACH THE FOLLOWING FILES TO THE BUG REPORT:
[build] Preprocessed source(s) and associated run script(s) are located at:
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Add-3b24fa.cpp
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Add-3b24fa.sh
[build] clang: note: diagnostic msg: Crash backtrace is located in
[build] clang: note: diagnostic msg: /Users/ericmalla/Library/Logs/DiagnosticReports/clang_<YYYY-MM-DD-HHMMSS>_<hostname>.crash
[build] clang: note: diagnostic msg: (choose the .crash file that corresponds to your crash)
[build] clang: note: diagnostic msg: 
[build] 
[build] ********************
[build] make[2]: *** [src/CMakeFiles/Oasis.dir/Add.cpp.o] Error 254
[build] clang: note: diagnostic msg: 
[build] ********************
[build] 
[build] PLEASE ATTACH THE FOLLOWING FILES TO THE BUG REPORT:
[build] Preprocessed source(s) and associated run script(s) are located at:
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Subtract-bd0f5f.cpp
[build] clang: note: diagnostic msg: /var/folders/fb/5cdbm2y52zg9nc859_12yqtr0000gn/T/Subtract-bd0f5f.sh
[build] clang: note: diagnostic msg: Crash backtrace is located in
[build] clang: note: diagnostic msg: /Users/ericmalla/Library/Logs/DiagnosticReports/clang_<YYYY-MM-DD-HHMMSS>_<hostname>.crash
[build] clang: note: diagnostic msg: (choose the .crash file that corresponds to your crash)
[build] clang: note: diagnostic msg: 
[build] 
[build] ********************
[build] make[2]: *** [src/CMakeFiles/Oasis.dir/Subtract.cpp.o] Error 254
[build] make[1]: *** [src/CMakeFiles/Oasis.dir/all] Error 2
[build] make: *** [all] Error 2
[proc] The command: /usr/local/bin/cmake --build /Users/ericmalla/Downloads/GitHub/Oasis/build --config Debug --target all -j 6 -- exited with code: 2
[driver] Build completed: 00:00:20.261
[build] Build finished with exit code 2
```