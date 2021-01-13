# Microsoft Developer Studio Project File - Name="Sample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=Sample - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Sample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Sample.mak" CFG="Sample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Sample - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "Sample - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Sample - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f Sample.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Sample.exe"
# PROP BASE Bsc_Name "Sample.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "make --file ../Makefile"
# PROP Rebuild_Opt ""
# PROP Target_File "Sample.gba"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "Sample - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f Sample.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Sample.exe"
# PROP BASE Bsc_Name "Sample.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "make --file ../Makefile"
# PROP Rebuild_Opt ""
# PROP Target_File "Sample.gba"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "Sample - Win32 Release"
# Name "Sample - Win32 Debug"

!IF  "$(CFG)" == "Sample - Win32 Release"

!ELSEIF  "$(CFG)" == "Sample - Win32 Debug"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\source\BdBackground.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdBlend.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdCutScene.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdCutSceneData.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdFontData.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdGame.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdGameEngine.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdGameIntro.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdGameIntroData.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdGfxData.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdGif.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdJpeg.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdJpegSlow.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdMan.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdMap.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdMapData.all.rodata.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdMapData.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdMenu.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdMenuData.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdMusic.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdRnd.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdScroll.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdStats.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdString.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BdVblank.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BoulderDash.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\BdBackground.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdBlend.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdCutScene.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdCutSceneData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdFontData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdGame.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdGameEngine.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdGameIntro.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdGameIntroData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdGfxData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdGif.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdJpeg.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdMan.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdMap.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdMapData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdMenuData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdMusic.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdRnd.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdScreenmode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdScroll.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdStats.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdString.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BdVblank.h
# End Source File
# Begin Source File

SOURCE=..\..\include\BoulderDash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gba.h
# End Source File
# Begin Source File

SOURCE=..\..\include\krawall.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mtypes.h
# End Source File
# Begin Source File

SOURCE=..\..\include\types.h
# End Source File
# End Group
# Begin Group "Build"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lnkscript
# End Source File
# Begin Source File

SOURCE=..\Makefile
# End Source File
# End Group
# Begin Group "Asm files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\assembly\BdJpega.s
# End Source File
# Begin Source File

SOURCE=..\..\assembly\BdJpegPixel.s
# End Source File
# Begin Source File

SOURCE=..\..\assembly\crt0.s
# End Source File
# End Group
# End Target
# End Project
