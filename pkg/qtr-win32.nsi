!include "MUI.nsh"

name "Qtr Installer"
outFile "qtr-win32.exe"
installDir "$PROGRAMFILES\Qtr\"
InstallDirRegKey HKCU "Software\OneZeroLab\Qtr" ""

!insertmacro MUI_PAGE_WELCOME

!insertmacro MUI_PAGE_LICENSE "..\COPYING"

!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_FINISHPAGE_RUN
!define MUI_FINISHPAGE_RUN_CHECKED
!define MUI_FINISHPAGE_RUN_TEXT "Start Qtr"
!define MUI_FINISHPAGE_RUN_FUNCTION "launchQtr"

!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_LANGUAGE "English"

section "Install"

	setOutPath "$INSTDIR"

	file "..\release\libgcc_s_dw2-1.dll"
	file "..\release\mingwm10.dll"
	file "..\release\QtCore4.dll"
	file "..\release\QtGui4.dll"
	file "..\release\QtNetwork4.dll"
	file "..\release\QtScript4.dll"
	file "..\release\qtr.exe"

	writeUninstaller $INSTDIR\uninstall.exe

	createDirectory "$SMPROGRAMS\Qtr"
	createShortCut "$SMPROGRAMS\Qtr\Qtr.lnk" "$INSTDIR\qtr.exe"
	createShortCut "$SMPROGRAMS\Qtr\Uninstall.lnk" "$INSTDIR\uninstall.exe"

	writeRegStr HKCU "Software\Qtr" "" $INSTDIR

	writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qtr" \
                 "DisplayName" "Qtr"
	writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qtr" \
                 "Publisher" "OneZero Lab"
	writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qtr" \
                 "InstallLocation" "$INSTDIR"
	writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qtr" \
                "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
	writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qtr" \
                 "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"
	writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qtr" \
                 "NoModify" 0x00000001
	writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qtr" \
                 "NoRepair" 0x00000001
	

sectionEnd

section "Uninstall"

	delete "$INSTDIR\uninstall.exe"

	deleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qtr"
	deleteRegKey HKCU "Software\Qtr"

	
	delete "$SMPROGRAMS\Qtr\Qtr.lnk"
	delete "$SMPROGRAMS\Qtr\Uninstall.lnk"

	rmDir "$SMPROGRAMS\Qtr"

	delete "$INSTDIR\libgcc_s_dw2-1.dll"
	delete "$INSTDIR\mingwm10.dll"
	delete "$INSTDIR\QtCore4.dll"
	delete "$INSTDIR\QtGui4.dll"
	delete "$INSTDIR\QtNetwork4.dll"
	delete "$INSTDIR\QtScript4.dll"
	delete "$INSTDIR\qtr.exe"

sectionEnd


Function launchQtr
  ExecShell "" "$INSTDIR\qtr.exe"
FunctionEnd