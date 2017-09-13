cin_redirection
==============================================

Program Description
----------------------------------------------

An example of redirecting (emulating) std::cin

Purpose:

Say you have a library that takes input from the console and processes it. You may want to generate sucn input in you program and feed it automatically to the library.

Documentation
----------------------------------------------

- All of the code is sufficiently commented.
- Doxygen generated documentation is in the __docs__ folder

Building Tips
----------------------------------------------

Set Project Properties:

* Configuration Properties > General > Output and Intermediate Directories
    - `build\$(Platform)\$(Configuration)\bin\`
    - `build\$(Platform)\$(Configuration)\obj\`
