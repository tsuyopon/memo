# SCons-Partsについて
SCons-PartsはSConsのプラグインです。Intelによって開発されていました。

インストールは次のコマンドで可能です。
```
$ pip install scons-parts
```

ドキュメントなどはほとんど存在していないので、ソースコードは次のコマンドで取得できる。
```
$ git clone https://bitbucket.org/sconsparts/parts.git
```

上記で
- docs/
  - word形式のドキュメントが存在しています。
- samples/
  - 様々な利用サンプルが存在します。

# 関数起点によるソースコードの探し方
利用されている関数はadd_global_objectやadd_global_parts_objectによって、外部で見える関数名と実際に実行しているオブジェクトが定義されている箇所がある。
たとえば、VcsGitという関数を探したければ、vcs/git.pyのソースコードのgit関数を参照すると良いといった感じになります。
```
$ grep -rinH add_global_ .
./site-packages/parts/config.py:724:api.register.add_global_parts_object('ConfigValues', ConfigValues)
./site-packages/parts/config.py:725:api.register.add_global_object('ConfigValues', ConfigValues)
./site-packages/parts/dependson.py:265:api.register.add_global_parts_object('DependsOn', dependsOnEnv, True)
./site-packages/parts/dependson.py:266:api.register.add_global_parts_object('Component', ComponentEnv, True)
./site-packages/parts/dependson.py:267:api.register.add_global_parts_object('REQ', REQ)
./site-packages/parts/filters.py:38:api.register.add_global_object('hasFileExtension', hasFileExtension)
./site-packages/parts/filters.py:39:api.register.add_global_object('HasPackageCatagory', HasPackageCatagory)
./site-packages/parts/installs.py:662:api.register.add_global_object('SetDefaultInstallArguments', SetDefaultInstallArguments)
./site-packages/parts/metatag.py:65:api.register.add_global_parts_object('MetaTag', MetaTag)
./site-packages/parts/metatag.py:66:api.register.add_global_parts_object('MetaTagValue', MetaTagValue)
./site-packages/parts/metatag.py:67:api.register.add_global_parts_object('hasMetaTag', hasMetaTag)
./site-packages/parts/metatag.py:69:api.register.add_global_object('MetaTag', MetaTag)
./site-packages/parts/metatag.py:70:api.register.add_global_object('MetaTagValue', MetaTagValue)
./site-packages/parts/metatag.py:71:api.register.add_global_object('hasMetaTag', hasMetaTag)
./site-packages/parts/node_helpers.py:146:api.register.add_global_parts_object('AbsFile', _AbsFile, True)
./site-packages/parts/node_helpers.py:147:api.register.add_global_parts_object('AbsDir', _AbsDir, True)
./site-packages/parts/node_helpers.py:148:api.register.add_global_parts_object('AbsFileNode', _AbsFileNode, True)
./site-packages/parts/node_helpers.py:149:api.register.add_global_parts_object('AbsDirNode', _AbsDirNode, True)
./site-packages/parts/packaging.py:379:api.register.add_global_object('PackageGroups', PackageGroups)
./site-packages/parts/packaging.py:380:api.register.add_global_object('PackageGroup', PackageGroup)
./site-packages/parts/packaging.py:381:api.register.add_global_object('GetPackageGroupFiles', GetPackageGroupFiles)
./site-packages/parts/packaging.py:382:api.register.add_global_object('GetFilesFromPackageGroups', GetFilesFromPackageGroups)
./site-packages/parts/packaging.py:384:api.register.add_global_object('AddPackageNodeFilter', AddPackageNodeFilter)
./site-packages/parts/packaging.py:386:api.register.add_global_object('ReplacePackageGroupCritera', ReplacePackageGroupCritera)
./site-packages/parts/packaging.py:387:api.register.add_global_object('AppendPackageGroupCritera', AppendPackageGroupCritera)
./site-packages/parts/packaging.py:388:api.register.add_global_object('PrependPackageGroupCritera', PrependPackageGroupCritera)
./site-packages/parts/packaging.py:390:api.register.add_global_object('ReplacePackageGroupCriteria', ReplacePackageGroupCriteria)
./site-packages/parts/packaging.py:391:api.register.add_global_object('AppendPackageGroupCriteria', AppendPackageGroupCriteria)
./site-packages/parts/packaging.py:392:api.register.add_global_object('PrependPackageGroupCriteria', PrependPackageGroupCriteria)
./site-packages/parts/parts.py:88:api.register.add_global_object('Part', Part_factory)
./site-packages/parts/parts.py:89:api.register.add_global_object('part', Part_factory)
./site-packages/parts/pattern.py:278:api.register.add_global_object('Pattern', _Pattern)
./site-packages/parts/pattern.py:279:api.register.add_global_parts_object('Pattern', _Pattern, True)
./site-packages/parts/platform_info.py:339:api.register.add_global_parts_object('ChipArchitecture', ChipArchitecture)  # obsolete
./site-packages/parts/platform_info.py:340:api.register.add_global_parts_object('OSBit', OSBit)  # obsolete
./site-packages/parts/platform_info.py:341:# api.register.add_global_parts_object('Host_Platform',HostSystem)
./site-packages/parts/platform_info.py:342:api.register.add_global_object('ChipArchitecture', ChipArchitecture)  # obsolete
./site-packages/parts/platform_info.py:343:api.register.add_global_object('OSBit', OSBit)  # obsolete
./site-packages/parts/platform_info.py:344:api.register.add_global_object('HostPlatform', HostSystem)
./site-packages/parts/platform_info.py:345:api.register.add_global_object('SystemPlatform', SystemPlatform)
./site-packages/parts/platform_info.py:346:# api.register.add_global_object('ValidatePlatform',ValidatePlatform)
./site-packages/parts/poptions.py:487:api.register.add_global_object('SetOptionDefault', SetOptionDefault)
./site-packages/parts/reporter.py:429:api.register.add_global_object('PrintError', user_report_error)
./site-packages/parts/reporter.py:430:api.register.add_global_object('PrintWarning', user_report_warning)
./site-packages/parts/reporter.py:431:api.register.add_global_object('PrintMessage', user_print_msg)
./site-packages/parts/reporter.py:432:api.register.add_global_object('VerboseMessage', user_verbose)
./site-packages/parts/reporter.py:435:api.register.add_global_parts_object('PrintError', user_report_error)
./site-packages/parts/reporter.py:436:api.register.add_global_parts_object('PrintWarning', user_report_warning)
./site-packages/parts/reporter.py:437:api.register.add_global_parts_object('PrintMessage', user_print_msg)
./site-packages/parts/reporter.py:438:api.register.add_global_parts_object('VerboseMessage', user_verbose)
./site-packages/parts/settings.py:701:api.register.add_global_object('DefaultSettings', DefaultSettings)
./site-packages/parts/version.py:553:api.register.add_global_parts_object('Version', version)
./site-packages/parts/version.py:554:api.register.add_global_parts_object('VersionRange', version_range)
./site-packages/parts/version.py:555:api.register.add_global_object('Version', version)
./site-packages/parts/version.py:556:api.register.add_global_object('VersionRange', version_range)
./site-packages/parts/version_info.py:42:    api.register.add_global_parts_object('PartVersionString', parts_version_text)
./site-packages/parts/version_info.py:43:    api.register.add_global_parts_object('IsPartsExtensionVersionBeta', is_parts_version_beta)
./site-packages/parts/version_info.py:44:    api.register.add_global_parts_object('PartsExtensionVersion', PartsExtensionVersion)
./site-packages/parts/version_info.py:47:    api.register.add_global_object('PartVersionString', parts_version_text)
./site-packages/parts/version_info.py:48:    api.register.add_global_object('IsPartsExtensionVersionBeta', is_parts_version_beta)
./site-packages/parts/version_info.py:49:    api.register.add_global_object('PartsExtensionVersion', PartsExtensionVersion)
./site-packages/parts/api/register.py:29:def add_global_parts_object(key, object, map_env=False):
./site-packages/parts/api/register.py:47:def add_global_object(key, object):
./site-packages/parts/overrides/default_env.py:31:api.register.add_global_object('DefaultEnvironment', Part_DefaultEnvironment)
./site-packages/parts/pieces/ccommand.py:36:api.register.add_global_parts_object('ProgramScanner', SCons.Scanner.Prog.ProgramScanner())
./site-packages/parts/pieces/ccommand.py:37:api.register.add_global_object('ProgramScanner', SCons.Scanner.Prog.ProgramScanner())
./site-packages/parts/pieces/ccopy.py:549:api.register.add_global_object('CCopy', CCopy)
./site-packages/parts/pieces/ccopy.py:550:api.register.add_global_parts_object('CCopy', CCopy)
./site-packages/parts/pieces/part_name.py:54:api.register.add_global_parts_object('PartName', _PartName, True)
./site-packages/parts/pieces/part_version.py:63:api.register.add_global_parts_object('PartVersion', _PartVersion, True)
./site-packages/parts/vcs/file_system.py:115:api.register.add_global_object('VcsFileSystem', file_system)
./site-packages/parts/vcs/file_system.py:116:api.register.add_global_object('VcsPreBuilt', file_system)  # compatibility
./site-packages/parts/vcs/git.py:469:api.register.add_global_object('VcsGit', git)
./site-packages/parts/vcs/null.py:45:api.register.add_global_object('VcsLocal', null_t)
./site-packages/parts/vcs/reuse.py:178:api.register.add_global_object('VcsReuse', reuse_part_vcs)
./site-packages/parts/vcs/reuse.py:179:api.register.add_global_object('VcsUsePriorPart', reuse_part_vcs)
./site-packages/parts/vcs/smart_svn.py:260:api.register.add_global_object('VcsSmartSvn', smart_svn)
./site-packages/parts/vcs/svn.py:367:api.register.add_global_object('VcsSvn', svn)
```

# 詳細



```
vcs: version control system
```

# docs配下のドキュメントについて
word形式で見にくいので以下に内容を添付しておきます。

### Getting Started Guide.docx
```
Parts Getting Started Guide
Contents
Parts Getting Started Guide	1
Introduction	3
Our Philosophy	3
How SCons Works	3
So what is Parts?	3
Setup	4
Getting Started	5
Getting Started Basics	5
Hello world Sample	5
Creating a Part	5
Creating the Master SConstruct File	6
Building the Sample	6
Output Directories	7
Tool Chains	7
Selecting Different Tools Chains	7
Configurations	8
Modes	8
A More Complex Example	8
Part Name and Versions	9
Platforms	9
Adding values to the environment	10
SDKs	11
DependsOn	11
Version range	11
Sub-Parts	14
Simple example	14
More Complex	16
 Example	16
Note on use of subparts	22
Build Targets	22
Focused targets	23
Unit Testing	24
Simple example	24
Bring it all together	28
VCS objects	28
Pattern	30
Wrap up	31


Introduction
SCons (from Software Construction) is a cross-platform, open-source, make-replacement, build system written in Python. 
While makefiles have a specialized, sometimes arcane, syntax that is interpreted by the make utility, the configuration files for SCons are Python code. 
The use of Python enables a clean and simple way to define scripts without a need to know Python in detail. It also enables an easy way to extend SCons and use Python facilities to debug and solve issues that are difficult to solve in classic Make or IDE project systems. 
Our Philosophy
	•	Any developer can build the product: A product should always be build-able by a developer, not just on a special box or by special people with special knowledge of what special items must be set up to make the build work. 
	•	Extend SCons, do not wrapper it: Instead of making a tool that hides the use of SCons, we use the ability of SCons to extend logic and functionality naturally. This means we use SCons as is, but get some extras for free. It also means the ideal build functionality of SCons should work as documented, and our new logic should work on top of this. However, nothing is perfect and there are a few rough edges. This document points out these areas.
How SCons Works
At a high level, SCons is just a running Python script. The way SCons is defined, you can write a powerful build script in SCons without being a Python expert or even knowing you are using Python. The general flow of a SCons build is as follows:
	•	Invoke SCons.
	•	Process any command-line arguments.
	•	Look for a SConstruct file (equivalent to a makefile for Make users).
	•	Read this SConstruct file (referred to as the “read phase”) 
	•	Process the resulting actions described in the SConstruct file until it is done (referred to as the “execution/build phase”).
So what is Parts?
One of the core issues with SCons is its inability to scale to large projects. Much like Make systems, SCons’ lack of structure idioms prevents different groups in large development projects from easily sharing code in a plug-and-play fashion.
To help address this lack of structure, we defined a concept called a Part. A Part is much like a component. In fact the two are generally interchangeable; however, we used a different term that does not collide with any preconceived notions of what a component might be. 
The Python Part function in the SConstruct file loads another file with information on how to build a given component. It is much like the SCons SConscript() function. The difference is that the Part function sets up a common structure to prevent redefinition of common concept idioms in incompatible ways. This standardizing and extension of these build idioms is the core idea of what a Part is and what the Part function does. The end result is an easy way to build a product with hundreds or thousands of components, while allowing you to easily plug-and-play each component into one or more products or personal development builds. 
The natural design of SCons lets you define what you want to happen, not how, thus providing a better way to define how to build code in a cross platform way. Instead of building files with a specific tool in a specific order in a specific shell environment, you can tell SCons to build a result from specific sources without worrying about what tools to use, the order of the sources to be built, the exact location of the tools on the given system, the shell used, or even the platform. SCons also lets you try different tools chains at a higher level and create portable scripts.
Notice that we refer to the Parts extension to SCons which introduces a Part function that defines a component-like entity called a Part.  And one or more of those entities are collectively called Parts! Further, the script that describes how to define one of those entities is called a Parts file!!  This document will try to provide enough contexts to avoid confusion of definition.
Setup
To setup SCons and Parts on your system, you will need to have an installed version of Python. For many POSIX based systems, there is a predefined python package to install, or the system may already have it installed. For Windows you will have to install Python by downloading a package from the internet, as Windows does not ship with it. I recommend the python package from ActiveState. You will want Python version 2.4 or better to use Parts. As of the time of this writing Python 3.0 is not supported.
You will want to download the latest stable version of SCons from www.scons.org. Currently this is version 1.2.0. Follow the instructions for installing SCons on the website. If you are a Windows user, they have a nice Windows installer
To get Parts you can download a package from parts.tigris.org or check out the code with SVN. There should also be a nice installer for windows provided. Just make sure you uninstall any previous versions first. If you checkout or download a compressed file, you will need to do these steps to install
	•	unpack the file into a directory ( only needed if you did not checkout a tagged or trunk version)
	•	open a command prompt to the directory where the code was checked out
	•	elevate permission to allow for a safe install 
	•	run the command "python setup.py install"
	•	to verify install run the command "parts".  (This will print out the version installed)

Getting Started
Before we start with basic samples, it is recommended that users read the user guide on SCons first. That describes important basics about SCons and how it works. We will try to cover the basics and separate what is built into SCons vs. what is added via the Parts extension. 
	•	Getting Started Basics
The basis of all SCons systems is the SConstruct file. This is like the Makefile in Make systems. A file with this default name is the input file that SCons uses to figure out what needs to be done for a given build. By default SCons allows the user to call other SConstruct files in a recursive manner much like one would in a Make system. However, like in Make, this can be difficult to use for large projects. To help avoid these problems the Parts extension adds a notion of a Parts file to the idea of the SConstruct file. By defining a Part we define a SCons Environment with a number of standard and extended build idioms preconfigured. The SConstruct file will define the call to all the Parts files needed to create the final product output. This allows any component to be plugged into any SConstruct, with little worry about what “product” it is being used in.
	•	Hello world Sample
Let’s start with a simple example in the form of compiling the classic “hello world” program.
	•	Creating a Part
Suppose we want to create a simple “hello world” program. In a normal SConstruct file this is very simple; using the Parts extension it will look a little more complex. Keep in mind this sample will grow, and very soon you would see that the slightly more complicated example will look much cleaner as the specification becomes more complex. First assume our simple “hello world” program exists in hello.c
#include <stdio.h>
int main()
{
	printf(“hello world\n”);
	return 0;
}
We want to create a Parts file that contains the instructions for what we want to build with SCons. We create a Parts file that defines this Part as independent of all other Parts. For purposes of this sample we will call this file hello.parts.
Import('*')
out=env.Program(“hello”,”hello.c”)
env.InstallTarget(out)
The first line tells SCons to import everything into this file that has been exported by the Parts extension. The Parts extension uses this feature to define a common build environment.  It also provides access to many utility functions that extend SCons’ ability to help the user define what is to be built in a portable way. The second line tells SCons that we want it to build  a program/executable called hello from the source file hello.c. For most functions defined in SCons, the first parameter is a target name, with the second being a single file or a collection of input files. The last line is a Parts function that tells SCons to copy the output of the Program() call from the build directory to the install “sandbox” from which you can safely run the program . In our example this will cause SCons to build an object file and link it as a runnable program on Linux, or an .exe file on Windows. It will then copy the final output file to the install sandbox, looking at the file extension to figure out if it should go in a bin or lib subdirectory or some other location. 
	•	Creating the Master SConstruct File
Next we need to create a SConstruct file so we can tell SCons to build something. SCons is unaware of any .Parts files; we need a SConstruct file to reference them. For this simple example the file is very simple.
from parts import *
Part('hello','hello.parts')
The first line is a Python directive that imports the Parts extensions. This is much like #include in C/C++. The second line is a function that defines our Parts file under a SCons alias of hello. This alias can be used on the command line to control what Part or set of Parts SCons will build. The Part function can take many more optional arguments, see the User Guide for more details.
	•	Building the Sample
Given that all three files are saved in the same directory, open your favorite Command prompt shell and change directory to where these files reside. Once there, type the command “SCons all”.  You should see the following output on Windows with the Microsoft compiler installed.
>SCons all
scons: Reading SConscript files ...
scons: done reading SConscript files.
scons: Building targets ...
cl /nologo /Od /MDd /W3 /Zc:wchar_t /RTC1 /DWIN32 /D_WINDOWS /D_WIN32_WINNT=0x501 /c hello.c /Fobuild\debug\hello\hello.obj hello.c
link /OUT:build\debug\hello\hello.exe /LIBPATH:build\debug\hello /LIBPATH:. build\debug\hello\hello.obj
Microsoft (R) Incremental Linker Version 8.00.50727.762
Copyright (C) Microsoft Corporation.  All rights reserved.

mt -nologo -outputresource:build\debug\hello\hello.exe;1 -manifest build\debug\hello\hello.exe.manifest
Embedded build\debug\hello\hello.exe.manifest successfully into build\debug\hello\hello.exe
Install file: "build\debug\hello\hello.exe" as "install\bin32\hello.exe"
PARTS: Generating SDK file for Part hello_0.0.0.
PARTS: Done -- Generating SDK file for Part hello_0.0.0.
Parts: Writing version mapping file for part alias [hello]
PARTS: Writing -- Done
scons: done building targets.
SCons found the latest version of the compiler on your system, set up an appropriate build environment, and built the code correctly. In the above sample it saw that VS 2005 was installed, created the correct environment, built hello.exe, and even linked in the default Manifest file generated by the linker. It then copied the file to an install sandbox which by default is the install directory in the directory where the SConstruct file resided. Currently SCons defines the default compiler on windows to be Microsoft C++ while on Linux, Mac the default is GCC.
	•	Output Directories
There will be a number of output directories created. You should see a build directory which contains the object files that have been built. There will be an install directory which contains the final binaries in a directory structure that should allow you to run the program. 
	•	Tool Chains
Many developers often have to develop code on more than one system and have it compile with more than one compiler. One of the great advantages of SCons is that it generally makes this very easy to do as long as you define it in the SConstruct when you create a new Environment. Parts extends the SCons notion of tools and adds a notion called Tool Chains, which are named set of tools that can be used to build your code. Unlike SCons, these tool chains can be defined on the command line in a standard way to control what tools are used to build all your code. These tool chains can also be manually set by the user in the Parts file, or in the Parts call.
	•	Selecting Different Tools Chains
This ability to select different tools to compile with, makes it easy to test one’s code with different tools, and helps make the code more stable, portable, and robust. Taking the last sample one can type “SCons all toolschain=icl,mstools”. Given that you have the Intel compiler installed, you will see SCons rebuild all your code with the latest version of the Intel Compiler installed on your system, with compatibility set for the latest version of Microsoft installed on you system.
If you have more than one version of the Intel compiler installed, or more than one version of the Microsoft compiler installed you may want to control which version is used. For example, assume you have both VC 2003 (cl version 7.1) and VS 2005(cl version 8.0). Saying “toolchain=cl” on the command line will tell Parts to configure SCons with the latest version of CL it can find. This means it will find and use version 8.0, If you wanted to use version 7.1, simply specify “toolchain=cl_7.1”.  If you want to use the Intel Compiler version 10.1 with VC 2003 you can say “toolchain=icl_10.1,mstools_7.1”. Want to switch it to use VS 2005? Just say “toolchain=icl_10.1,mstools_8.0”.
The general form for all tools is <tool name>_<tool version>, where the version is optional.  In cases of more than one matching version, the best, that is, newest, version is chosen. So “tools=cl_7” will select 7.1 over 7.0 if both are installed, while “tools=cl_7.0” will select cl 7.0, not 7.1
	•	Configurations
Most build systems have some notion of a configuration. A build configuration, in general, is a set of flags, defines, and settings used to build the code with. Common configurations are debug and release, where debug would have settings to reduce optimization and add debugging information, while release would have no debugging information and settings to increase runtime performance. Parts allows for the definition of user configurations. It ships with a basic debug and release settings. However these mostly likely may not meet many project needs or notion of what debug or release are. In such cases, it is best to override and extend with your own configuration. Details on how to do this are defined in the User Guide. For the examples in this document we will use the built in configurations. To set the configuration to use, add "config=<configuration name>" on the command line. For the current example we ran the command “SCons all”; this is the same as the command “SCons all config=debug”. Running “SCons all config=release” would build the example with the default release settings 
	•	Modes
Modes are a way to control how your Part builds, independent of the configuration. For example it is common to want to define Tracing or Assertion to be compiled in the code. Often this is independent of optimizations or whether or not the binary is being built with debug information. Modes can be very convenient in that they add a dimension to your ability to control how your Part may compile without having to define a large set of configurations. For example, it can be a lot simpler to say “SCons all config=release mode=tracing,assertion” than having to define a new configuration and then specifying “config=assert_tracing_release”.  Parts allows you to define your build either ways with user defined configurations, or with the use of  mode value.
A More Complex Example
Most projects require many different Parts to be created. It is not uncommon for a project to require 50 - 100 different Parts to make the final product. Within this collection of Parts, different Parts often depend on other Parts and any Part may have a requirement to depend on certain version(s) of another Part. We will extend the previous sample to depend on a different Part and show how it can depend on a certain version range of that component to help prevent mismatches from happening.
To do this let’s move the “hello world” print function to a shared library. Most projects contain an executable that binds to one or more dynamically linked libraries. Let’s make a new Part called print_msg which will create the shared library that prints the message to the screen.
First make a header file:
//print_msg.h
#ifdef WINDOW_OS
# ifdef PRINT_EXPORTS
#	define PRINT_API __declspec(dllexport)
# else
#	define PRINT_API __declspec(dllimport)
# endif
#else
#	define PRINT_API
#endif
PRINT_API void print_msg();
Next create a source file:
#include "print_msg.h"
#include <stdio.h>
void print_msg()
{
	printf(“hello world”);
}
Now we need to modify our parts file. This new file is much like the last one but you will notice a few new items.  Version 2 of our Parts file would look like this:
Import('*')
env.PartVersion('1.0.0')
env.PartName('print_msg')
#files
cpp_files=['print_msg.c']
if env['TARGET_PLATFORM']['OS']='win32':
    env.Append(CPPDEFINES= ['WINDOW_OS'])
env.Append(CPPDEFINES= ['PRINT_EXPORTS'])
outputs=env.SharedLibrary('print_msg',cpp_files)
env.InstallTarget(outputs)
env.SdkInclude(['print_msg.h'])
Part Name and Versions
The PartName function allows us to define a constant value for a given part. Unlike the alias value used in the Part() call in the Sconstruct, this value is constant. If no PartName is called the alias provided by the Part() call is used instead. PartVersion() allows one to define a version value which consists of three period-separated numbers. If a version is not provided 0.0.0 will be used. The name and the version are important in forming relationships between different Parts such as dependencies, and can be used to provide many different build targets. This will be clearer in the examples below
Platforms
Next you will see an if statement.  This is basic Python code.  In the env object, Parts defines the variable HOST_PLATFORM, as what platform we are building on, and TARGET_PLATFORM, as what platform we are building for. Each System Platform object in Parts maps to a SCons based HOST/TARGET_OS and a HOST/TARGET_ARCH that is new in SCons 1.3. If using an older version of SCons Parts will add these values. You can use these values directly or you can control both via the System Platform object HOST_PLATFORM or TARGET_PLATFORM. Using these objects you can refer to the OS or ARCH value via members. The OS value is the general operating system, for example win32 is used for Windows, posix is used for Linux, sunos is used for Solaris. The ARCH value (short for architecture) is the general chip architecture of the system being used. Values such as 'x86', 'x86_64', 'ia64' are used instead of more detail chip types, since 99.9% of the time that detail is not needed. There are many different platforms defined by SCons. Using the platform value we can target certain settings to be applied on certain platforms. In our example we add certain defines for the build if we are targeting the win32 platform. This is a common usage pattern for these variables with some other possibilities listed below. The aim is to make it easier for the developer to specify platform specific conditions

1) if env[‘TARGET_PLATFORM’] = ‘any-any’:
2) if env[‘TARGET_PLATFORM’] = ‘win32-any’:
3) if env[‘TARGET_PLATFORM’] = ‘any-x86’:
4) if env[‘TARGET_PLATFORM’] = ‘x86’:
5) if env[‘TARGET_PLATFORM’] = ‘win32’:
6) if env[‘TARGET_PLATFORM’] = ‘posix-x86_64’:
7) if env[‘TARGET_PLATFORM’] = ‘sunos-ia64’:
Each of the above conditions would be True for:
	•	Any combination of OS and CPU architecture
	•	A Windows OS on any CPU architecture 
	•	Any OS on a 32-bit x86 architecture
	•	Any OS on a 32-bit x86 architecture
	•	A Windows OS on any CPU architecture
	•	Any Posix based OS on a 64-bit x86 architecture
	•	Sun’s Solaris OS on an Intel Itanium architecture


Adding values to the environment
For our example we need to define WINDOW_OS and PRINT_EXPORTS. To do this we need to add these values to CPPDEFINES. The recommended way to add a value is to call SCons Append() or Prepend() functions. In the case of CPPDEFINES, order does not matter so we just append the new value via the call to env.Append() as seen above. Note that we call it twice, one is in the if block and one is not. The use of the if logic with the platform value allows us the needed control to add values in certain cases as in the case of the WINDOWS_OS define. In the case of PRINT_EXPORTS, this value will always be added, no matter the platform used.
CPPDEFINES is one of the many values defined by SCons that controls what is passed to the command line of the compiler. Other values exist such as CFLAGS or CXXFLAGS that control what flags are used for the C or C++ compiler. The SCons Man pages document these well, so refer to them to determine what to add to. Parts adds some of its own values, but these tend to control action of the Parts extension. 
The next line tells SCons to create a SharedLibrary. Unlike Program, which creates an executable, this function will create a .dll or .so file depending on the platform. SCons also provides functions to build static libraries or individual object files.
SDKs
Parts adds a concept called SDK. This is a set of directories that contain data that can be used to build from. There are a set of SDK based functions that in general mirror the InstallXXX() based function in Parts.  By default object passed to an InstallXXX() call will be automatically added to the SDK, so a call to InstallTarget is the same as calling SdkTarget() and passing the outputs to InstallTarget(). 
Some SDK functions will add information to be passed on to other Parts that may depend on the defining Part. The last call in this parts file does exactly this. The call to SdkInclude() will cause SCons to copy the header file to the SDK include area. Other Parts that are dependent on this Part will have the path to this file automatically added to the compilers INCLUDE path.
DependsOn
In the example below we will see a Parts defined function called DependsOn(). This function allows a Part to automatically receive values from another part which it needs to build against. Values such as include path, Lib path and lib are common values that can be shared. In our example let’s modify the hello.parts file so it will depend on the print_msg Part. 
For consistency we will add a PartName and PartVersion function. The main difference will be adding the DependsOn call. This will tell SCons and the Parts extension that this Part depends on another Part. This does two main things: It tells the Parts extension how to map dependency information better for SCons, and it also allows the Parts extension to map other values such a LIBS or PATH values to help the dependent Parts build better. Below is the modified file.
Import('*')
env.PartVersion('1.0.0')
env.PartName('hello')
env.DependsOn([Component('print_msg','1.*')])

ret=env.Program("hello","hello.c")
env.InstallTarget(env.Sdk(ret))
The DependsOn call can be called multiple times, or be given a collection of component objects. A Component has three main arguments: The name of the dependent component, an optional version range, and an optional “requires” parameter which allows a user to say how to depend on the given component
Version range
The version range is used to specify which version of a component to map to if more than one version of the component was defined in the SConstruct. In this example we say that any version having the number “1” as a first version specifier is adequate. Parts will map to SCons the latest 1.X.X version it can find in the SConstruct file. If only a 2.X.X version was defined, Parts will cause a build error complaining that it cannot find the version that maps to the requested version. If no version is provided, Parts will map to the latest version of any Part with the name of the requested component.
Assume our SConstuct file is as follows:
from parts import *
Part('hello','hello/hello.parts')
Part('print','print_msg/print_msg.parts')
This will cause the following (modified to show version mapping points in bold):
SCons: Reading SConscript files ...
...
Copying file: "print_msg\print_msg.h"
 to SDK as: "sdks\print_msg_1.0.0_x86\include\print_msg.h"
cl /nologo /Od /MDd /W3 /Zc:wchar_t /RTC1 /DWIN32 /D_WINDOWS /D_WIN32_WINNT=0x501 /Isdks\print_msg_1.0.0_x86\include /c hello\hello.c /Fobuild\debug\hello\hello.obj
hello.c
link /OUT:build\debug\hello\hello.exe /LIBPATH:build\debug\hello /LIBPATH:hello /LIBPATH:sdks\print_msg_1.0.0_x86\lib\debug print_msg.lib build\debug\hello\hello.obj
Microsoft (R) Incremental Linker Version 8.00.50727.762
Copyright (C) Microsoft Corporation.  All rights reserved.
...
SCons: done building targets.

Let us modify the example to show what could happen if we had multiple versions of print_msg. Version 4 of print_msg.parts looks like this:
Import('*')

env.PartVersion('2.0.0')
env.PartName('print_msg')

#files
cpp_files=['print_msg.c']

if env['TARGET_OS']=='win32':
    env.Append(CPPDEFINES= ['WINDOW_OS'])
env.Append(CPPDEFINES= ['PRINT_EXPORTS'])

outputs=env.SharedLibrary('${PART_NAME}_${PART_VERSION}',cpp_files)

sdk_outs=env.Sdk(outputs)
env.InstallTarget(sdk_outs)

env.SdkInclude(['print_msg.h'])
We will define a PartVersion 1.0.0, 1.5.0, 1.5.2 and a 2.0.0 of the same-named Part. Notice for simplicity we use a variable defined by Parts to control the name of the binary. The ${PART_NAME}_${PART_VERSION} will be expanded by SCons to print_msg_1.0.0, SCons then will add a postfix and/or prefix to this value depending on the platform. For this example on Windows it would add .dll to the end, giving “print_msg_1.0.0.dll”. On Linux it would add ‘lib’ to the beginning and .so to the end, giving “libprint_msg_1.0.0.so”.
To show how version mapping works we will need four different versions of the hello Part file that specify different versions of print_msg. The version that maps to 1.0.0 of print message looks like this:
Import('*')
env.PartVersion('1.0.0')
env.PartName('hello1.0.0')
env.DependsOn([Component('print_msg','1.0.0')])

ret=env.Program('${PART_NAME}',"hello.c")
env.InstallTarget(env.Sdk(ret))
 Notice that in this example we map exactly to the version 1.0.0. This hello Part will fail to map to any other version. As an alternative, which is much like our previous example, we have a less restrictive specification:
Import('*')
env.PartVersion('1.0.0')
env.PartName('hello1.5.2')
env.DependsOn([Component('print_msg','1.*')])

ret=env.Program('${PART_NAME}',"hello.c")
env.InstallTarget(env.Sdk(ret))
This will map to version 1.5.2 of print_msg. This happens because the filter tells us to map to the best match of “1.*”. In our set of versions, 1.0.0, 1.5.0, 1.5.2 and 2.0.0, version 1.5.2 is the best match. Unfortunately there are cases when the latest is not the greatest. In these cases we often want to not use a version. To say this we can use “!” as the not operator and separate the ranges by a comma (‘,’). Suppose we want any version of 1.* but not 1.5.2.  We can simply do so as shown in our next example:
Import('*')
env.PartVersion('1.0.0')
env.PartName('hello1.5.0')
env.DependsOn([Component('print_msg','1.*,!1.5.2')])

ret=env.Program('${PART_NAME}',"hello.c")
env.InstallTarget(env.Sdk(ret))
For our assumed set of versions, we will map to 1.5.0 as this is the best match.
Ranges can also be defined using a ‘-‘ dash. The above line of '1.*,!1.5.2' could also be written as '1-1.9.*,!1.5.2'.
To map to the to the 2.0.0 version we would simple say “2.*” in the version field, such as
Import('*')
env.PartVersion('1.0.0')
env.PartName('hello2.0.0')
env.DependsOn([Component('print_msg','2.*')])

ret=env.Program('${PART_NAME}',"hello.c")
env.InstallTarget(env.Sdk(ret))
given a SConstruct file such as:
from parts import *
Part('hello1','hello_1/hello.parts')
Part('hello2','hello_1.0.0/hello.parts')
Part('hello3','hello_1.5.0/hello.parts')
Part('hello4','hello_2/hello.parts')

Part('print1','print_msg_1.0.0/print_msg.parts')
Part('print2','print_msg_1.5.0/print_msg.parts')
Part('print3','print_msg_1.5.2/print_msg.parts')
Part('print4','print_msg_2.0.0/print_msg.parts')
one could build all versions in at the same time and have the correct versions mapped. 
Sub-Parts
Sub-Parts is the ability to define a Part with in another Part. This is much like the ability in SCons or Make to call other SConstruct file or makefiles, but with more structure. The need for defining a Sub-Part comes from a Part being a set of related Parts that need to be grouped and versioned together as a component. While any Sub-Part can be defined as an independent Part, the ability to group them is a convenience that is useful in large projects. Sub-Parts share the same version value with the root Part. The name of the Part is defined as the parent Part separated by a ‘.’ separator.
Simple example
A common example of the use of a Sub-Part is in case of a proxy and a driver. The user uses the API defined in the proxy Part, but doesn’t know that the proxy uses a driver to define the implementation of the API. To run the program you need both the proxy and driver to be built, but from the users point of view, only the proxy is needed to build the code. Such a Part file for the proxy would look like this:
Import('*')
env.PartVersion('1.0.0')
env.PartName('proxy')

env.Part('driver','driver/driver.parts')
env.DependsOn([Component('proxy.driver',env.PartVersion(),requires=REQ.DEFAULT_INTERNAL )])

#files
cpp_files=['proxy.cpp']

if env['TARGET_OS']=='win32':
    env.Append(CPPDEFINES= ['WINDOW_OS'])
env.Append(CPPDEFINES= ['PROXY_EXPORTS'])

outputs=env.SharedLibrary('${PART_NAME}_${PART_SHORT_VERSION}',cpp_files)

sdk_outs=env.Sdk(outputs)
env.InstallTarget(sdk_outs)

env.SdkInclude(['proxy.h'])

In this example we call env.Part(...) with values that define the Sub-Part. Notice that, on the next line we tell the system that we depend on the Sub-Part, and that we refer to it via its full name, “proxy.driver” not the short name “driver”. When we depend on it we get the current defined version via a call to PartVersion with no arguments. This ensures that we map to the exact version. The Parts extension sees Parts and Sub-Parts as the same thing. No implicit mapping happen when defining a Sub-Part, everything needs to be explicit. 
Currently the SubPart is designed to inherit the PartVersion of its parent. 
So no call to PartVersion is needed in the SubPart.
Requires argument in Component 
One feature shown in this sample is the ability to define how you depend on a component. By default depending on a component will pass information about outputted CPPPATH, CPPDEFINE, LIBPATH and LIB value of the dependent part. This information is defined by using the SdkInclude, SdkLib (or SdkTarget) funtions or their similar Install counterparts. By default your component will also depend on any components that your dependant components depend on. However in many cases this is not the desired behavior as the real dependency is hidden and forwarding it would add extra values to the link or include path that is not needed to build a component. Adding these unneeded values can look messy, and in some cases, can allow unwanted dependence between components. In this sample we don’t want anyone that depends on the proxy component to depend on the driver. To help with this we use the requires argument and pass it value from the REQ object. 
REQ object
The REQ is an object that stands for “requires”. It contains a bunch of values on how we can depend on an object. By default components depend on the value of REQ. DEFAULT. This value differs from REQ. DEFAULT_INTERNAL in that _INTERNAL values don’t allow the dependency data to be passed to the defining Part.  Values in REQ allow control over passing everything from PATH, LIBS ,DEFINEs and FLAGS. By default only PATH,LIBS and DEFINES are passed. FLAGS have to be exported and imported explicitly.
The driver Sub-Part would look like this:
Import('*')

env.PartName('driver')
#files
cpp_files=['driver.cpp']

if env['TARGET_OS']=='win32':
    env.Append(CPPDEFINES= ['WINDOW_OS'])
env.Append(CPPDEFINES= ['DRIVER_EXPORTS'])

outputs=env.SharedLibrary('${PART_NAME}_${PART_SHORT_VERSION}',cpp_files)

sdk_outs=env.Sdk(outputs)
env.InstallTarget(sdk_outs)

env.SdkInclude(['driver.h'])
Technically the call to the PartName function is not needed, since by default the name maps to the Alias defined in the Part() call. It is here for clarity. Notice that there is no PartVersion call as there is only one version for a Part as a whole which is used by all Sub-Parts
More Complex Example
Since Sub-Parts require explicit mapping when defining dependency information, more complex use cases can be designed. For example a common pattern found in SConstructs, is to define a Part that itself defines Sub-Parts, where the parent Part “DependsOn” some Sub-Parts and not others (see example below). These optional Sub-Parts need explicit mapping from the SConstruct even though this SConstruct maps its parent Part. By stating a dependency on a given Sub-Part, the parent Part can control what is added by default. This ability allows different Sub-Parts to be used depending on the platform or some other value. Also it allows optional components to be used only if requested explicitly. In the next example we will define an “engine” Part that further defines three Sub-Parts, two of which are required, and one that is optional. The required Sub- Parts are called “common” and “core”, and the optional Sub-Part will be called “optional”. For this example we will define this directory structure for engine:
engine
├───common
├───core
├───include
└───optional

In common we will define a common.cpp which will look like this:
#include "common.h"
#include <iostream>

void common(std::string const& s)
{
	std::cout<<"Common called from "<<s<<std::endl;
}
In common.parts we will define
Import('*')

env.PartName('common')

#files
cpp_files=['common.cpp']

if env['TARGET_OS']=='win32':
    env.Append(CPPDEFINES= ['WINDOW_OS'])
env.Append(CPPDEFINES= ['COMMON_EXPORTS'])
env.Append(CPPPATH= [AbsDir('../include')])

outputs=env.SharedLibrary('${PART_NAME}_${PART_SHORT_VERSION}',cpp_files)

sdk_outs=env.Sdk(outputs)
env.InstallTarget(sdk_outs)

env.SdkInclude([AbsFile('../include/common.h')],sub_dir='engine',add_to_path=False)
AbsDir and AbsFile
Notice the new functions called AbsFile and AbsDir. These functions are also methods on the SCons Environment object “env”, and like the SCons File() and Dir() methods return a SCons File or Dir node object. The reason for these functions is that by current design SCons assumes a tree structure for mapping values such as path, or file names. In this design all files and paths will be in the SConstruct/Parts file containing directory or below. In this example all our header files are in engine/include directory, which is not in or under the directory of the current Parts file. While SCons does support the ability to access these paths correctly, it provides some ugly syntax that is confusing at best, error inducing at worst. The AbsFile() and AbsDir() hides this ugly syntax and returns a node that refers to the location as an absolute path value. This allows the use of the more natural “../include” statement without having to do a more complex and error prone creation of an absolute path. Also this helps to correctly set optional arguments in SCons Dir and File node objects.
sub_dir and add_to_path arguments
The other new syntax we show here is in the SdkInclude call. In this example we want all uses of engine to say #include <engine/common.h> not #include <common.h>. This is a common practice used to help prevent headers with common names from causing unknown compiler problems. The argument, sub_dir=’engine’, will cause the header files to be copied to the sdk include area under a subdirectory called engine. 
Turning to the add_to_path=False argument. By default the sub directory and the root that contains the subdirectory are added to the PATH. This would allow both #include <engine/common.h> and #include <common.h> to compile. In our case we want to prevent this. So the argument of add_to_path=False allows us to tell Parts to not add the subdirectory to the path values forwarded to SCons. The sub_dir argument is standard on all SdkXXX and InstallXXX functions. The add_to_path only affects SdkInclude, SdkLib, SdkTarget functions.
The core directory looks similar. Here is core.cpp
#include "core.h"
#include <common.h>

void core()
{
	common("core");
}
And core.parts
Import('*')

env.PartName('core')
env.DependsOn([Component('engine.common',env.PartVersion())])

#files
cpp_files=['core.cpp']

if env['TARGET_OS']=='win32':
    env.Append(CPPDEFINES= ['WINDOW_OS'])
env.Append(CPPDEFINES= ['CORE_EXPORTS'])
env.Append(CPPPATH= [AbsDir('../include')])

outputs=env.SharedLibrary('${PART_NAME}_${PART_SHORT_VERSION}',cpp_files)

sdk_outs=env.Sdk(outputs)
env.InstallTarget(sdk_outs)

env.SdkInclude([AbsFile('../include/core.h')],sub_dir='engine',add_to_path=False)
The only real difference is that core has a line to depend on engine.common Sub-Part.
Optional is similar to core.cpp. Here is the optional.cpp file:
#include "optional.h"
#include <common.h>

void optional()
{
	common("optional");
}
And the optional.parts file
Import('*')

env.PartName('optional')
env.DependsOn([Component('engine.common',env.PartVersion())])

#files
cpp_files=['optional.cpp']

if env['TARGET_OS']=='win32':
    env.Append(CPPDEFINES= ['WINDOW_OS'])
env.Append(CPPDEFINES= ['OPTIONAL_EXPORTS'])
env.Append(CPPPATH= [AbsDir('../include')])

outputs=env.SharedLibrary('${PART_NAME}_${PART_SHORT_VERSION}',cpp_files)

sdk_outs=env.Sdk(outputs)
env.InstallTarget(sdk_outs)

env.SdkInclude([AbsFile('../include/optional.h')],sub_dir='engine',add_to_path=False)
In the include directory we define some headers file.
engine.h
#include "common.h"
#include "core.h"

inline void engine() {common("engine");core();}
common.h
#include <string>

#ifdef WINDOW_OS
# ifdef COMMON_EXPORTS
#	define COMMON_API __declspec(dllexport)
# else
#	define COMMON_API __declspec(dllimport)
# endif
#else
#	define COMMON_API
#endif

COMMON_API void common(std::string const& str);
core.h
#ifdef WINDOW_OS
# ifdef CORE_EXPORTS
#	define CORE_API __declspec(dllexport)
# else
#	define CORE_API __declspec(dllimport)
# endif
#else
#	define CORE_API
#endif

CORE_API void core();

And optional.h
#ifdef WINDOW_OS
# ifdef OPTIONAL_EXPORTS
#	define OPTIONAL_API __declspec(dllexport)
# else
#	define OPTIONAL_API __declspec(dllimport)
# endif
#else
#	define OPTIONAL_API
#endif

OPTIONAL_API void optional();
In the root engine directory we define engine.parts:
Import('*')
env.PartVersion('2.0.33')
env.PartName('engine')

env.Part('common','common/common.parts')
env.Part('core','core/core.parts')
env.Part('optional','optional/optional.parts')

# by depending on engine you automatically depend on engine.core
env.DependsOn([Component('engine.core',env.PartVersion())])

env.SdkInclude(['include/engine.h'],sub_dir='engine',add_to_path=False)

The important portion of this example is to understand that the engine depends on Sub-Part engine.core. We know that engine.core depends on engine.common. If some Part depends on engine it would be the same as depending on engine.core, or depending on engine.core and engine.common. The only difference is that engine defines a headers file to be copied to the SDK, because of this depending on engine.core instead of engine would mean that engine.h would not exist in the SDK. To depend on engine.optional the Part would have to state this dependence explicitly.
To show this we will make a Part that depends on just engine and one that depends on engine and engine.optional. The first example will have a Parts file such as
Import('*')
env.PartVersion('1.0.0')
env.PartName('main')
env.DependsOn([Component('engine','2.*')])

ret=env.Program("main1","main.cpp")
env.InstallTarget(env.Sdk(ret))
notice that only the engine is used as the value to depend on. In this example main.cpp would look like this:
#include "engine/engine.h"

int main()
{
	engine();
	return 0;
}
Notice that the #include is for “engine/engine.h”. If this was changed to just “engine.h” the build would fail with an error about not being able to find engine.h header file. If this was built you would see something like this:
 ( reduced to show dependence mapped data)
...
cl /nologo /Od /MDd /W3 /Zc:wchar_t /RTC1 /EHsc /GR /DWIN32 /D_WINDOWS /D_WIN32_WINNT=0x501 /Isdks\engine_2.0.33_x86\include /c main\main.cpp /Fobuild\debug\main1\main.obj
main.cpp
link /OUT:build\debug\main1\main1.exe /LIBPATH:build\debug\main1 /LIBPATH:main /LIBPATH:sdks\engine_2.0.33_x86\lib\debug engine.common_2.0.lib engine.core_2.0.lib build\debug\main1\main.obj
...
In the case where we would want to depend on engine.optional we need to only make a few changes. For example let us change our main.cpp program to look like this:
#include "engine/engine.h"
#include "engine/optional.h"

int main()
{
	engine();
	optional();
	return 0;
}
Without engine.optional added, we would have not been able to build. A simple change to the main.parts file
Import('*')
env.PartVersion('1.0.0')
env.PartName('main2')
env.DependsOn([Component('engine','2.*'),Component('engine.optional','2.*')])

ret=env.Program("main2","main.cpp")
env.InstallTarget(env.Sdk(ret))
is all that is needed.
To build all this, a simple SConstruct file needs to be defined.
from parts import *
Part('proxy','proxy/proxy.parts')
Part('engine','engine/engine.parts')

Part('main1','main/main.parts')
Part('main2','main2/main.parts')
Notice that like all other previous SConstuct files, we only define the Parts we need. To add the engine Part which contains three Sub-Parts, we only need to define the root engine Parts. 
Note on use of subparts
In practice this can be very useful when defining complex components as pieces of a build. However, it is best to only use Sub-Parts when they are needed and to keep them simple in structure. While complex and super Parts can be defined, this can cause complex and hard to maintain dependencies to be created if care is not taken. For example one could take the extreme of defining a GUI application with three super Parts called model, view and controller. The reality of this in practice so far is that the dependency mapping between model, controller and viewer Sub-Parts are often more complex to understand and deal with than to just breaking the super Parts in to smaller simple Parts with no or very simple Sub-Parts,. One case may have only three Parts, and the other may seem to have a larger and unmanageable number of Parts (possibly 20 or 30 or more), however our experience has shown that it easier for a large group of people to deal with larger set of simple Parts that a smaller set of complex Parts.
Build Targets
Parts defines a set of build targets for each part that is defined. So far we have only shown the 'all' target that will cause all parts to build. In a large project it is often desired to target the building of a given Part. SCons by default defines a lot of different targets. However knowing the value of these items is not always easy. SCons defines a function called Alias() to help simplify grouping of items to be built to a known name. Parts uses this function internally to setup a number of standard build targets. By default the part alias can be used to build a given target. In the current example the value of "proxy" can be used. This will build the part with the alias of "proxy" and anything that it depends on, such as the proxy.driver Sub-Part. Likewise if we only want to build the driver Part, then we would use the value of "proxy.driver". Another way to say this is to add a focused build concept. In this case the target "alias::proxy" is the same as saying "proxy" and "alias::proxy.driver" is the same as saying "proxy.driver". The use of "alias::" is an example of focused build target. Unlike most focused build targets alias:: only works with part alias values.
Focused targets
It is not uncommon to have shared Parts used between different builds. Often the same Part may be given different part alias values in different Sconstructs. This makes it hard to know what the correct target is. Parts defines high level target concepts to help define standard targets. These targets are defined in the general form of <concept>::[<part name>[ _<part version>]]. Build concepts that are currently supported are name::, build::, sdk:: and install::. Colon-colon (“::”) was used as it is one of the few tokens that does not have a predefined meaning on the command line, and it also maps well as a namespace separator in C++ and other languages today. It only seems natural to reuse this as a separator here as well. There are a few other concepts whom we will cover latter. The name:: target is ideally the most useful as it allows to build a part and all its subparts in a common way among projects. It is not uncommon for various reasons to have a Sconstruct with more than one version of a given Part. A simple example of a command line that could be used would look like this for the example we used to introduce sub-parts:

1) scons name::
2) scons name::proxy
3) scons name::proxy_1.0.0
4) scons name::proxy_1.0
5) scons name::proxy_1
6) scons name::proxy.driver
7) scons name::proxy.driver_1.0.0
8) scons name::proxy.driver_1.0
9) scons name::proxy.driver_1

Each of the above lines would build:
	•	this is the same as saying "scons all"
	•	Build any defined version of the Part named "proxy"
	•	Build  only version 1.0.0 for the Part named "proxy"
	•	Build only version 1.0.* for Part "proxy"
	•	the same as above but for version 1.* of "proxy"
	•	Build any defined version of the Part named "proxy.driver"
	•	Build  only version 1.0.0 for the Part named "proxy.driver "
	•	Build only version 1.0.* for Part "proxy.driver "
	•	the same as above but for version 1.* of "proxy.driver "

The important point to keep in mind is that unless more than one version of a Part is defined; the common target used will not have a version. If you define a SConstruct to build all versions of a Part, these extra aliases allow easy verification of regression and fixes between the releases. They also help greatly when we need to verify that a bug has always existed, or may have only existed on a given OS or compiler combination.
Other concept targets allow more focused building of a part. For example "build::" will only build the Part. While sdk:: will also create a SDK for a part but not copy data into the install sand box. The use of "Install::" will also add the files to the install sand box. The concepts are in a sense layered and calling a given alias will have different effects. In general:
1) "build::" will just build the part and any dependent data in the build directory, this includes any dependent items that have to be added to the SDK for it to build
2) "sdk::" will build and create the SDK for the defined Part and any dependent parts
3)"install:: will do everything "sdk::" would do, as well as, add needed files in the install sandbox.
4)"alias::" will build everything directly dependent on the defined part alias, which includes everything "install::" does
4) "name::" differs from "alias::" in that it will build all Sub-Parts of the requested part name even if there was no explicit dependence stated.

Unit Testing
One common need for development of code is proper unit testing. When defining a large system it is often difficult for different groups to validate their changes by running tests belonging to other groups. Likewise the running of simple unit tests can often help people triage where and why a product maybe broken without complex debugging of the entire application. To help with this, Parts adds a relatively general UnitTest function which is defined to compile a set of sources as a test. It can also run this test in a sand box to allow common and portable ways to run against possible data files. Since UnitTest is not bound to a given unit testing suite such as TUT or some in house system, it should adapt easily to custom needs.
Simple example
To create a simple example we will modify the print_msg Part we have already defined. We will create a common directory structure that looks like:
print_msg
├───src
└───utest
In this structure the primary source is in the directory “src” and the unit test code is under the “utest” directory. Unit test can be defined in a single Part or as its own Sub-Part. In this example we will show it as a single Part with the main module being built. 
Given that we have some tests in directory “utest”, in this case we will assume we have test1.cpp and test2.cpp, that do some sort of testing, we can modify the Parts file to look like the one shown below. What these tests do is not as important for this example, as it is that we have some tests that compile.
Import('*')

env.PartVersion('1.0.0')
env.PartName('print_msg')

env2=env.Clone()
env2.UnitTest("test1",["test1.cpp"],src_dir='../utest')
env2.UnitTest("test2",["test2.cpp"],src_dir='../utest')

#files
cpp_files=['print_msg.cpp']

if env['TARGET_OS']=='win32':
    env.Append(CPPDEFINES= ['WINDOW_OS'])
env.Append(CPPDEFINES= ['PRINT_EXPORTS'])

outputs=env.SharedLibrary('print_msg',cpp_files)

sdk_outs=env.Sdk(outputs)
env.InstallTarget(sdk_outs)

env.SdkInclude(['print_msg.h'])

As a practice in SCons, when building more than one binary type, it is good to clone the environment to prevent values from being shared that may prevent a component from building. By default any given Part file is given a unique environment in the variable env. In this example we make a new one for all the unit tests called env2. After the clone we call UnitTest to define two different unit tests we want to define. The first test is called test1 and the second is test2. We pass both of them a list of all source files to be built. The last parameter is only needed to help SCons in dealing with directories above that of the current defining Parts file. This is much like the AbsFile and AbsDir present before. Since in this example utest is at the same level as src, and the Parts file is being defined in the “src” directory, we need to use the src_dir to correctly build the unit test.
By default UnitTest has some basic behavior features. For one, the call to UnitTest will by default depend on the current defining Part. This means that the output of test1 will depend on print_msg.dll and anything the print_msg depends on as well. In certain cases you may need to have your unit test to depend on other Parts as well, for example a common unit testing API. To do this in this example a simple DependsOn(...)  call to this other component is needed on the environment value that will call the unit test.
Another feature is the Sandbox. This is a directory structure that is made to run the unit tests in. By default the binaries are copied to the #INSTALL_BIN location and a script is generated to run all these binaries as if they were running in the sandbox. This allows us the use of another argument in the UnitTest call, data_src. This variable allows you to pass a set of files to be added to the sandbox for testing. For example one may need to read a xml file to test that a xml parser read and processed the test correctly. By being able to copy these files in to the sandbox, it makes available a standard way for all test programs to easily find the data files since all these files will be in the current working directory or in some subdirectory from the test program point of view.
In this directory a script will be created to run the unit tests correctly outside of SCons. This is very helpful for debugging purposes and in cases when tweaks to the running of the test are needed. Such needs might be customizing the Shell environment, or custom command line arguments that may not be passed in the common cases.
The function UnitTest creates a unique name based on the Part name, version and test being defined. This prevents clashes when different Parts defines Parts with common names for their test, such as the name “test”. Likewise, to help with the running of the test, a unique set of aliases are defined to help run the given test or a set of tests defined in a Part.
Since a well written code may have a lot of unit tests and building a given target may take a long time if every unit test is built, in most cases you don’t want to build the tests by default. Because of this unit tests are not considered a portion of the “all” target defined by Parts, but instead require the use of a different target. By default to build all unit tests one would use the target concept of “utest::” and to build ( if they need to be built) and run the test one would use the target concept of “run_test::”. Just as before these build concepts take the general form of utest::<part name>[_<part version>]. A simple example of command line that could be used would look like this for our current sample:
1) scons utest::
2) scons utest::print_msg
3) scons utest::print_msg_1.0.0
4) scons utest::print_msg_1.0
5) scons utest::print_msg_1
6) scons utest::print_msg@test1
7) scons utest::print_msg@test1_1
8) scons utest::print_msg@test1_1.0
9) scons utest::print_msg@test1_1.0.0

Each of the above lines would build:
	•	all unit tests define in the SConstruct
	•	all unit tests defined for any version in the Part named print_msg
	•	all unit tests defined only for version 1.0.0 of the Part named print_msg
	•	all unit tests defined for version 1.0.* for Part print_msg
	•	the same as above but for version 1.* of print_msg
	•	would build unit test “test1” for any version of Part print_msg. Saying utest::print_msg@test2 would do the same, but for test2 instead
	•	would build unit test “test1” for any version of Part print_msg 1.*
	•	same as above but for version 1.0.*
	•	same as above but exactly for version 1.0.0

The important point to keep in mind is that if you define a SConstruct to build all versions of a Part, these extra aliases allow easy verification of regression and fixes between the releases, and help greatly to verify whether a particular bug has always existed, or may have only existed on a given OS or compiler combination. If you only define one version of a Part the simple "utest::<part name> form is the easiest to use. 
In the previous example we showed a unit test being called within a simple Part. However depending on how the user may want to organize the code and the Parts file, it is common for Sub-Parts to be used to define the unit tests. In this case we will modify the engine example to add a new Sub-Part for the unit tests. The new directory tree will look similar to before:
engine
├───common
├───core
├───include
├───utest
└───optional
The only difference is the new utest directory. The engine.parts file will add a new Part line:
Import('*')
env.PartVersion('2.0.33')
env.PartName('engine')

env.Part('common','common/common.parts')
env.Part('core','core/core.parts')
env.Part('optional','optional/optional.parts')
env.Part('tests','utest/unit_test.parts')

# by depending on engine you automatically depend on engine.core
env.DependsOn([Component('engine.core',env.PartVersion())])

env.SdkInclude(['include/engine.h'],sub_dir='engine',add_to_path=False)
everything else is the same except the new utest.parts file which will look like this:
Import('*')

env.PartName('unit_tests')
env.DependsOn([Component('engine.core',env.PartVersion())])

env.UnitTest("test",["test.cpp"])
In this file we see that the Sub-Part we called unit_tests ( the full name will be engine.unit_tests) depends on engine.core. We define one unit test which we call “test”. Unlike before we don’t need to Clone() environment as we only define one test and each Part gets a unique environment defined for it. If we decided to define more than one test and one of those tests needed to set some special values, such as a special define or a compiler flag, then it would be a good idea to clone the environment.
When running this test the previous alias would work via replacing print_msg with engine. However the important addition is that utest::engine will build all tests defined in engine and any Sub-Part. utest::engine.unit_tests will build only tests in the Sub-Part engine.unit_tests. If there was a unit test defined in engine.common then it would build when utest::engine was used as the build target, but not when engine.unit_test was used.
This wraps up the basics of unit tests. To run the test simply replace utest:: with run_utest::. The use of run_utest:: is the same as utest:: expect it adds a command to run the unit tests. Greater detail of the API and how to customize it is given in the API section of the document.
Bring it all together
So far we have gone over a number of common cases which one may want to use when defining a Part. As stated before, the goal of the Parts extension is to define a standard on top of SCons to allow large projects to have a more plug-and-play model of adding, versioning and sharing different Parts, without every component owner in the project stepping on others toes. In this last example we will bring it all together and make a bigger example showing off checking out of source and the pattern object. 
VCS objects
The VCS object stands for Version Control system. These objects are defined and given to a Part call to tell it to checkout or copy some file locally. These objects differ from the Source control methods in SCons in that they process checkout actions at the time the SConstruct is being read, and not as part of the build phase. The end result is that everything requested is checked out or copied before SCons does a dependence check, and copies only happen when a request to update the code is made or if it is clear that the code doesn’t exist. This tends to work better than having SCons always updating from your version control system every time you build. 
Currently Parts defines a SVN VCS object and a prebuilt VCS object. The SVN object allow for checkouts and updates from SVN while the prebuilt object is for accessing data on a server, or a file system, which is useful for third party code. The VCS object is passed to the Part function via the vcs_type argument. Using this object will cause the argument, that points to the Parts file, to be appended to final checkout location. An example of this in a SConstuct would look like this:
from parts import *
path=Dir('#svn/base').abspath.replace('\\','/')
SetOptionDefault('SVN_SERVER','file:///'+path)


Part('proxy','proxy.parts',vcs_type=VcsSvn(repository='proxy/',server='file:///'+path))
Part('engine','engine.parts',vcs_type=VcsSvn(repository='engine/'))
Part('print_msg','src/print_msg.parts',vcs_type=VcsSvn(repository='print_msg/'))

Part('main','main.parts',vcs_type=VcsSvn(repository='main/'))
All VCS objects take at least two parameters: server and repository. Server will point to the location to get the data from and repository points to where on the server to get the data from. In the above sample the line “Part('proxy','proxy.parts',vcs_type=VcsSvn(repository='proxy/',server='file:///'+path))” is the long form of doing this. This will check out from our SVN server the Part “proxy” to the $CHECK_OUT_DIR. By default this is defined as #repository/$PART_ALIAS. 
Normally when defining lots of Parts, they all come out of the same server, with some exceptions coming from different locations. Setting the default value for the $SVN_SERVER variable is the best way to easily set the server for the defined Parts. In the above example this is how the rest of the Parts get the correct server. The above example would output something like this if nothing was checked out before.
SCons: Reading SConscript files ...
Setting default value of SVN_SERVER to file:///C:/home/jason/code/work/parts/samples/full/svn/base
Warning! Sources do not seem to exist, but no update flags given.
Overriding flags to get sources.
svn checkout --non-interactive file:///C:/home/jason/code/work/parts/samples/full/svn/base/proxy/ "vcs\proxy"
A    vcs\proxy\proxy.cpp
A    vcs\proxy\proxy.h
A    vcs\proxy\proxy.parts
A    vcs\proxy\driver
A    vcs\proxy\driver\driver.h
A    vcs\proxy\driver\driver.parts
A    vcs\proxy\driver\driver.cpp
Checked out revision 2.

Warning! Sources do not seem to exist, but no update flags given.
Overriding flags to get sources.
svn checkout --non-interactive file:///C:/home/jason/code/work/parts/samples/full/svn/base/engine/ "vcs\engine"
A    vcs\engine\include
A    vcs\engine\include\engine.h
A    vcs\engine\include\optional.h
A    vcs\engine\include\common.h
…
After this, the command “SCons all” will just try to build the code,. There will be no attempt to update the sources from SVN. To have the build update the sources add UPDATE_ALL=true on the command line. This will result in a command that will cause the source to be updated. Such output would look like this:
>SCons all UPDATE_ALL=true
SCons: Reading SConscript files ...
Setting default value of SVN_SERVER to file:///C:/home/jason/code/work/parts/samples/full/svn/base
svn switch --non-interactive file:///C:/home/jason/code/work/parts/samples/full/svn/base/proxy/ "vcs\proxy"
At revision 2.
svn switch --non-interactive file:///C:/home/jason/code/work/parts/samples/full/svn/base/engine/ "vcs\engine"
At revision 2.
svn switch --non-interactive file:///C:/home/jason/code/work/parts/samples/full/svn/base/print_msg/ "vcs\print_msg"
At revision 2.
svn switch --non-interactive file:///C:/home/jason/code/work/parts/samples/full/svn/base/main/ "vcs\main"
At revision 2.
SCons: done reading SConscript files.
SCons: Building targets ...
PARTS: Mapping version information
PARTS: Done -- Mapping version information
SCons: `all' is up to date.
SCons: done building targets.
Since there are no changes in our sample nothing was updated, but the SVN command was run to update the sources.
As stated the part file is found relative to where the checkout code exists for the current Part. For proxy the Part file is expected to exist in #vcs/proxy/proxy.parts. For print_msg Part it would be expected to live in #vcs/print_msg/src/print_msg.parts. Removing the vcs_type parameter will cause the Part function to look for the file relative to the directory of the SConstruct file instead of $CHECK_OUT_DIR. This is important since a common mistake made when switching from a Part that is local on disk to one in a VCS location is not modifying the Part file location, as these relative locations often don’t match up exactly.
Pattern
When defining the list of files to build it is often more convenient and safe to define some sort of pattern of file that need to be processed. SCons, until recently, did not provide any means to do this and even then this process has some limiting abilities. This ability is called Glob. Since Parts was written before this ability existed, an object called Pattern was defined. Pattern much like the name suggests allows for the ability to define a simple wildcard pattern to include and/or exclude certain file patterns. The main difference between Glob and Pattern is that Glob returns a list of nodes on disk, and has knowledge of other location such as the VariantDir. This allows Glob to preemptively find certain nodes that will be created while Pattern cannot. Pattern on the other hand allows for the ability to keep tree structure and allows for the ability to perform recursive searches. Pattern also returns a Pattern object, which is not a first class object in SCons, but is in most Parts functions. This does cause some issues, but for the most part these are minor for the power gain.
A common example of using this would be to get all the sources to build as a program or a shared object. It is common for many code bases to layout sources in a similar structure as the namespaces used in the sources. For example a layout such as:
src
└───mylib
    ├───functor
    ├───generic
    │   ├───abilities
    │   ├───convert
    │   ├───factory
    │   └───iterators
    └───types
 Each of the directories may or may not contain many files. To get all these files simply saying:
cpp_files=Pattern(src_dir  = 'mylib', includes = ['*.cpp','*.c'])
will return a pattern object that will get all source files of interest. However since Pattern is not a Node object in SCons you can say the ideal
cpp_files=Pattern(src_dir  = 'mylib', includes = ['*.cpp','*.c'])
# Error SCons doesn’t know what a pattern is..
env.SharedLibrary(‘mylib’,cpp_files)
to get around this Pattern provides a function that will return a flattened list to pass to SCons functions. To correct above sample simply say this:
cpp_files=Pattern(src_dir  = 'mylib', includes = ['*.cpp','*.c']).files()
env.SharedLibrary(‘mylib’,cpp_files)

Parts functions like SdkXXX() functions know how to deal with Pattern and allow for more ideal usage. For instance given the current example, it would be needed to define the headers we want to copy to the sdk directory. Such headers would need to have the structure preserved to ensure that the user code compiles correctly. Simply saying
env.SdkInclude(Pattern(src_dir  = '.', includes = ['*.hpp','*.h']))
would copy all *.hpp and *.h files into the SDK to be used by all Parts that would depend on the mylib Part. The tree structure form the original source will be preserved and only files that match the simple pattern will be copied. Keep in mind like most SCons functions a flattened list is returned. This list if passed to any other SCons or Parts functions will not preserve the tree structure that was provided by Pattern. Hopefully this will be improved over time with support from SCons. 
Wrap up
Hopefully you have enough understanding of the basic usage of Parts. Please consult the User Guide for more technical details. Please feel free posting questions or comments to the User forum at parts.tigris.org.
```

### PartsScripts.docx
```
User Guide on Parts cache scripts

Introduction
Currently Parts generates various cache files to keep information on parts and notes between runs:
	•	global_data.cache. Contains information on SConstruct files.
	•	nodeinfo.cache. Contains list of parts, sections and scons aliases, including information of dependency between parts.
	•	part_map.cache. Contains additional information on mapping between parts and aliases.
	•	vcs/*.cache. Contains information on version control system (vcs) used. Names of cache files in “vcs” directory are the corresponding part aliases.
This document provides information on the usage of “parts_util” package and scripts located in parts/scripts directory which can be used for manipulations on Parts *.cache files.


Prerequisites
To successfully use scripts the system should have Parts and all prerequisites installed:
	•	Python 2.7.3.
	•	Scons 2.1.0.
	•	Parts 0.10.1.0 or later. Parts should be installed into Python distribution of located at the same level as “scripts” directory.


Overview of scripts
scripts/parts_dump_cache.py
This script unpickles and dumps contents of cache file to stdout in human readable format. pprint module is used to format the output. It can be used for eye analysis of cache contents or for comparison of two caches e.g. to find regressions in new drop of Parts.

Script usage:
parts_dump_cache.py [--scons-version=SCONSVERSION] [--include-parts=REGEX] [--exclude-parts=REGEX] [--include-nodes=REGEX] [--exclude-nodes=REGEX] [--include-aliases=REGEX] [--exclude-aliases=REGEX] path/to/cache/file

Here “path/to/cache/file” is path to any of supported Parts cache files. See “Introduction” section for the list of supported cache files.

Options: 
	•	scons-version: scons version to work with. If omitted then the highest version among supported and found on the system ones is used. See “Prerequisites” section for the information on supported scons version(s).
	•	include-parts: name of part alias to filter in. Regular expression can be used. Use this option multiple times if multiple aliases need to be specified. This option is applicable for “nodeinfo.cache” file only.
	•	exclude-parts: the same as “include-parts” but for filtering out.
	•	include-nodes: the same as “include-parts” but for filtering in of specific nodes (e.g. files or directories).
	•	exclude-nodes: the same as “include-nodes” but for filtering out.
	•	include-aliases: the same as “include-parts” but for filtering in of specific scons aliases (targets).
	•	exclude-aliases: the same as “include-aliases” but for filtering out.


scripts/parts_dump_dependency.py
This script dumps the information of dependency between parts to stdout in xml or human-readable format. Note that dependency info in xml format replaces *.mapping files for parts 0.9.x. The major differences between .mapping format and an existing xml one are:
	•	There were multiple *.mapping files. There will be a single xml file with dependency info now.
	•	*.mapping files were in plain text format. Current one will be in xml format as a universal and easy-to-parse one.
	•	Current format contains much more information. It is assumed this format will represent dependency info for current and future Parts releases and should not be changed (only supplemented with new stuff if necessary).
Possible usage models of dependency file are:
	•	Check of invalid (e.g. circular) dependencies in the product
	•	Check that specific requirements for dependencies are fulfilled
	•	Creation of dependency graph based on this file
	•	Visual investigation of dependencies of specific part(s).
	•	Search of bugs and regressions in newer version of Parts e.g. by diffing two dependency files generated by stable and development branches of Parts.
You can find an example of xml dependency file in Appendix 1.

Script usage:
parts_dump_dependency.py [--scons-version=SCONSVERSION] [--include-parts=REGEX] [--exclude-parts=REGEX] [--output-format=OUTPUTFORMAT] [--verbosity=VERBOSITY] path/to/cache/file

Here “path/to/cache/file” is path to nodeinfo.cache file. No other Parts cache files are supported.

Options:
	•	scons-version: scons version to work with. If omitted then the highest one among supported and found on the system is used. See “Prerequisites” section for the information on supported scons version(s).
	•	include-parts: name of part alias to filter in. Regular expression can be used. Use this option multiple times if multiple aliases need to be specified.
	•	exclude-parts: the same as “include-parts” but for filtering out.
	•	output-format: format of output dumped. Choices are “xml”, “txt”. Default is “xml”. “txt” is a human readable format suitable for quick eye analysis.
	•	verbosity: verbosity of output. Applicable for “txt” output format only, while for “xml” output format whole dependency information is always dumped. Choices are “low”, “medium”, “full”. Default is “low”. For “low” verbosity each part is dumped on single line followed by indented list of parts it depends on. Only section, alias and version are dumped, therefore the output is the most compact one. For “full” verbosity whole dependency information is dumped and tagged accordingly. For “medium” verbosity the output is the same as for “full” one except information on requirements which is dumped in more compact form.


scripts/parts_process_nodes.py
This script iterates over nodes (files, directories, aliases or values) and applies custom callback(s) (python function(s)) to each node. Examples of callback actions are check of coding guidelines for source file, check of copyright year for source file, etc.

Script usage:
parts_process_nodes.py [--scons-version= SCONSVERSION] [--include-parts= REGEX] [--exclude-parts= REGEX] --callback-module= CALLBACKMODULE [--callback-factory= CALLBACKFACTORY] [--node-type= NODETYPE] [--nodes-root-dir=NODESROOTDIR] [--include-nodes= REGEX] [--include-extensions= INCLUDEEXTENSIONS] [--output-format | f= OUTPUTFORMAT] path/to/cache/file

Here “path/to/cache/file” is path to nodeinfo.cache file. No other Parts cache files are supported.

Options:
	•	scons-version: scons version to work with. If omitted then the highest one among supported and found on the system is used. See “Prerequisites” section for the information on supported scons version(s).
	•	include-parts: name of part alias to filter in. Regular expression can be used. Use this option multiple times if multiple aliases need to be specified.
	•	exclude-parts: the same as “include-parts” but for filtering out.
	•	callback-module: Path to python script containing the implementation of callback class for node processing. Use this option multiple times if multiple scripts need to be specified.
	•	callback-factory: Name of factory method to create an instance of callback class. Default is “createNodeCallbackObject”.
	•	node-type: Type of nodes to process. Choices are “file”, “dir”, “value”, “alias”. Default is “file”.
	•	nodes-root-dir: Directory which paths of nodes are relative to. Applicable for “file” and “dir” node types only. If not specified it is assumed to be directory where .parts_cache resides.
	•	include-nodes: the same as “include-parts” but for filtering in of specific nodes.
	•	include-extensions: node extensions to filter in. Exact extensions should be specified, but not regular expressions. Applicable for “file” node type only. Use this option multiple times if multiple extensions need to be specified.
	•	output-format: output format. Choices are “txt”, “xml”. Default is “xml”.

Factory method in callback module should create an instance of process_node_ifc.NodeCallback class (see below) or descendant of it.


Overview of “parts_util” package
parts/parts_util directory contains python package which provides various API to work with cache files. One can import them and use this API to create custom scripts for cache processing.

scons_setup.py
This module contains API to setup scons environment to successfully import and use scons stuff.
	•	getSupportedVersions(): return a list of supported scons versions found on the system.
	•	setupDefault(): Update environment with paths to default scons installation to allow further imports of scons stuff. “Default” means the one with highest version among supported ones.
	•	setup(sconsVersion): Update environment with paths to installation of scons with specific version. Version should be one of the supported ones.

parts_setup.py
This module contains API to setup Parts environment to successfully import and use Parts stuff.
	•	setupDefault(): Update environment with paths to default parts installation to allow further imports of Parts stuff.

cache_unpickle.py
This module contains API to unpickle cache file and extract needed info from it.
	•	class NodeinfoParser: class to parse nodeinfo.cache file and extract information stored. Currently extraction of aliases, section names and nodes is supported.
	•	__init__(self, nodeinfoPath, reportProgress=None): create class instance and initialize it with path to nodeinfo.cache. Arguments are:
	•	nodeinfoPath: path to nodeinfo.cache file.
	•	reportProgress: callback method called to report progress of instance creation. Interface of callback is reportProgress(percentsDone).
	•	getPartName(self, partAlias): get part name.
	•	getAliases(self): get the list of part aliases.
	•	getSectionNames(self, partAlias): get list of section names for specific part alias. Arguments are:
	•	partAlias: alias of part to get sections for
	•	getNodes(self, partAlias, section = 'build', nodeType = None, extensions = [], masks = [], existingOnly = True): get list of tuples (nodeId, nodeInfo) for specific part alias and section. See documentation of scripts/process_nodes.py for explanation what “nodeId” and “nodeInfo” are. Arguments are:
	•	partAlias: alias of part to get nodes for
	•	section: name of section. Default is "build". Can be None meaning that nodes for any section should be returned.
	•	nodeType: type of node (SCons.Node.FS.File, SCons.Node.FS.Dir, etc). Default is None meaning that nodes of any types should be returned.
	•	extensions: extensions of nodes to be included. Applicable only if "nodeType" is SCons.Node.FS.File. Default is [] meaning that nodes with all extensions should be returned
	•	masks: regexp patterns which returned nodes should match.  Default is [].
	•	existingOnly:  specifies whether only nodes existing on disk should be returned. Default is True.
	•	split(cacheFilePath): split path to cache file into cache root directory, cache directory name, cache key and cache filename. E.g. if cacheFilePath is "zip_package1/.parts.cache/a3e124cd59bd929fed1f43ec55421e66/nodeinfo.cache"  then it will return ("zip_package1", ".parts.cache", "a3e124cd59bd929fed1f43ec55421e66", "nodeinfo") tuple.
	•	unpickle(cacheFilePath, reportProgress=None): unpickle cache file and return its contents as Python object. Currently for all cache files unpickled data is a dict().

process_node_ifc.py
This module contains API to process nodes.
	•	class NodeCallback: callback class containing the API to process nodes.
	•	preprocessNodes(self, parserOptions, args, nodeinfoParser, reportProgress): called before processing each node. Arguments are:
	•	parserOptions: cmd line parser options after cmd line arguments are parsed.
	•	args: list with cmd line arguments (not including options).
	•	nodeinfoParser: instance of cache_unpickle.NodeinfoParser with parsed cache info.
	•	reportProgress: callback method to report percentage progress. Interface of callback is reportProgress(percentsDone).
	•	processNode(self, nodeId, nodeDict, nodeObj): called for each node. Arguments are:
	•	nodeId: path to node for node of "SCons.Node.FS.File" and "SCons.Node.FS.Dir" type; alias for node of "SCons.Node.Alias.Alias" type; value for node of "SCons.Node.Python.Value" type.
	•	nodeDict: dictionary containing frequently used information for node. It can be empty. Currently the following key-value pairs can be present in it:
	•	nodeInfo: instance of parts.pnode.scons_node_info.scons_node_info. It stores various additional information about the node.
	•	depends: list of strings representing dependencies for node. For File node type only.
	•	partAlias: alias of part this node belongs to.
	•	nodeObj: instance of node. It can be None.
	•	postprocessNodes(self, reportProgress): called after each node is processed. Arguments are:
	•	reportProgress: see preprocessNodes().
	•	CALLBACK_FACTORY_NAME: recommended name of method to create instance of callback class.

process_node_sample.py
This module contains example of usage of NodeCallback class.

options_common.py
This module contains API to construct command line parser with options common for all scripts.
	•	getCommonParser(callerModulePath): creates a command line parser with options common for all scripts.
	•	callerModulePath: path where caller module is located.


Appendix 1. Xml format of dependency information.
<root>
  <!-- Whole file consists of multiple "part" blocks. -->

  <!-- This is a block of information for separate single Part. -->
  <part> <!-- Can be present multiple times. -->
    <!-- Start of attributes of specific Part. Set of tags is not limited, it can be extended
         if new attributes are introduced in future version of Parts. -->

    <!-- These are attributes as specified by user. Some keys can be missing which means that user did not specify them.
          The problem here is that arguments of Part() call are not necessary strings so it is not clear how to specify
          them. -->

    <!-- These are real Part's attributes as were resolved by Parts based on declared ones. -->
    <alias>component0.core</alias>
    <name>component0.core</name>
    <version>1.11.19</version>
    <vcs>
      <type>svn</type>
      <server>components/component0_1.11.19</server>
    </vcs>
    <!-- ... etc. Not sure whether we need to specify ALL attributes. Anyway this can be extended with new tags at any time. -->

    <!-- These are key:value0, value1 properties, i.e. **kw args in Part() call. Keys are not predefined
         so they cannot be represented as tags so choosing another format to represent them. -->
    <properties>
      <property key = "mode"> <!-- Can be present multiple times. -->
        <val>MYNODE0</val>
        <val>MYNODE1</val>
      </property>
    </properties>

    <!-- End of attributes of specific Part. -->

    <!-- This is a particular section (build, utest, or custom one) in Part. -->
    <section> <!-- Can be present multiple times. -->
      <!-- Attributes -->

      <name>build</name>
      <alias>build::component0.core</alias>
      <!-- End of attributes. -->

      <!-- This block describes a list of components this section depends on. -->
      <dependsOn>
        <!-- This block contains information specified for each Component() argument passed to DependsOn() method.
             I.e. this section depends on multiple components specified below. -->
        <component> <!-- Can be present multiple times. -->
          <!-- These are arguments of Component() call as specified by user. Expected keys are "name", "versionRange",
           "requires", "section". Some keys can be missing which means that user did not specify them. -->
          <declared>
            <name>component1@CC:icc@mode:foo,bar</name>
            <versionRange>1.8.4-1.*</versionRange>
            <requires>
              <req>
                <key>
                  REQ.FOO_INTERNAL
                </key>
              </req>
              <req>
                <key>
                  REQ.CPPDEFINES
                </key>
              </req>
            </requires>
          </declared>

          <!-- Start of dependency information as was resolved by Parts based on declared information. -->

          <!-- This is resolved Part information. -->
          <part>
            <!-- Alias and section name should be the same as those for certain Part at root level,
                 so we can find this part and all info about its attributes, properties, dependencies, etc. -->
            <alias>component1</alias>
            <section>
              <name>build</name>
            </section>
          </part>

          <!-- These are key:value or key:value0,value1,value2 properties specified in "name" argument
                for Component(). -->
          <properties>
            <property key = "CC"> <!-- Can be present multiple times. -->
              <val>icc</val>
            </property>
            <property key = "mode">
              <val>foo</val>
              <val>bar</val>
            </property>
          </properties>
          <!-- End of resolved Part information. -->

          <!-- This is resolved contents of "requires" argument -->
          <requires>
            <req> <!-- Can be present multiple times. -->
              <key>FOO_INTERNAL</key>
              <internal>True</internal>
              <weight>0</weight>
              <!-- ... etc. -->
            </req>
            <!-- It is always assumed that reqs are added via OR. -->
            <req>
              <key>CPPDEFINES</key>
              <internal>False</internal>
              <weight>0</weight>
            </req>
          </requires>

          <!-- End of dependency information. -->
        </component>

        <!-- Another Component() -->
        <component>
        </component>

        <!-- etc... -->
      </dependsOn>

    </section>

    <!-- Another section -->
    <section>
    </section>

    <!-- etc... -->

  </part>

  <!-- Another Part() -->
  <part>
  </part>

  <!-- etc... -->
</root>
```

# 参考URl
- https://bitbucket.org/sconsparts/parts
- https://bitbucket.org/sconsparts/profile/members
