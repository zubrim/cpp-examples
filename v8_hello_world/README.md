v8_hello_world
==================================================

This is a Hello World program with static linking for Google V8 engine. It is not a trivial task to build it on Windows in an *unprepared* environment due to lack of some essential details in documentation.


Building Tips
--------------------------------------------------

### Requirements for the development environment:

 - Visual Studio 2015 update 3
 - VC++, Python Tools and Windows SDK must be installed with VS 2015
 - Debugging Tools for Windows: download and install [Windows 10 SDK](<https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk>)
 - Environment variables (use your modified __assets/setenv.bat__ under admin): 
   - `CPP_V8_ROOT` for v8 root folder
   - `CPP_DT_ROOT` for depot tools root folder
   - `GYP_MSVS_VERSION=2015`
   - `DEPOT_TOOLS_WIN_TOOLCHAIN=0`
   - `PATH=$(CPP_DT_ROOT);%PATH%` Check that the DT path is ahead of any Python installation.

 ### Depot tools
 
 - [Download](<https://storage.googleapis.com/chrome-infra/depot_tools.zip>)
 - `# cd $(CPP_V8_ROOT)`
 - `# gclient sync`

 ### Building static libraries
  - `# cd $(CPP_V8_ROOT)`
  - `# fetch v8`
  - `# gclient sync`
  - `# python tools/dev/v8gen.py x64.release`
  - `# gn args out.gn/x64.release`
     - opens text editor, edit with additional values from __assets/out.gn/x64.release/args.gn__:
     - `is_component_build = false`
     - `v8_static_library = true`
     - this should override settings in __v8.gni__, if not - modify it
  - `# ninja -C out.gn/x64.release`
  
 ### Project Settings
  1. Configuration Properties > Debugging > Environment
      - `PATH=%PATH%;$(CPP_V8_ROOT)\out.gn\x64.release\;`
      - this is a path to __natives_blob.bin__ and __snapshot_blob.bin__
      - alternatively, these file must be copied to *.exe directory
  2. Configuration Properties > General > Output and Intermediate Directories
      - `build\$(Platform)\$(Configuration)\bin\`
      - `build\$(Platform)\$(Configuration)\obj\`
  3. C/C++ > General > Additional Include Directories
      - `$(CPP_V8_ROOT)\include\;`
  4. Linker > General > Additional Library Directories
      - `$(CPP_V8_ROOT)\out.gn\x64.release\obj\third_party\icu;$(CPP_V8_ROOT)\out.gn\x64.release\obj\src\inspector;$(CPP_V8_ROOT)\out.gn\x64.release\obj;`
  5. Linker > Input > Additional dependencies
      - `v8_base_0.lib;v8_base_1.lib;v8_libbase.lib;v8_external_snapshot.lib;v8_libplatform.lib;v8_libsampler.lib;icuuc.lib;icui18n.lib;inspector.lib;winmm.lib;dbghelp.lib;shlwapi.lib;%(AdditionalDependencies)`
  6. C/C++ > Code Generation > Runtime Library
      - `Multi-threaded (/MT)`
        
 ### References
  - [Checking out and Building Chromium for Windows](<https://chromium.googlesource.com/chromium/src/+/master/docs/windows_build_instructions.md>)
  - [Building V8](<https://github.com/v8/v8/wiki/Building-with-GN>)
  - [How to build V8 on Windows and not go mad](<https://medium.com/dailyjs/how-to-build-v8-on-windows-and-not-go-mad-6347c69aacd4>)
   
 
 