[SETUP]

RestartIfNeededByRun=false
AlwaysRestart = no 
AppName=tuxlerVPN
AppVerName=tuxlerVPN
Appversion=2.3.0.8
VersionInfoVersion=2.3.0.8
AppPublisher=Tuxler Privacy Technologies, Inc.
DefaultDirName = {pf}\tuxlerVPN
DefaultGroupName= tuxlerVPN
LicenseFile=../build/license.txt
PrivilegesRequired=admin
DisableProgramGroupPage=yes
WizardImageFile=Install.bmp
WizardSmallImageFile=setuplogo.bmp
SetupIconFile=..\ico.ico
UsePreviousAppDir=no
UsePreviousGroup=no
UsePreviousSetupType=no
UsePreviousTasks=no
UsePreviousUserInfo=no
UninstallDisplayIcon={app}\tuxlerVPN.exe
Compression=lzma
SolidCompression=yes
DisableReadyPage   = yes
OutputBaseFilename=tuxlerVPNSetup
DisableStartupPrompt=yes
DisableWelcomePage=1
SignTool=MySign
SignedUninstaller=yes

[Languages]
Name: mytrans; MessagesFile: "1Default.isl"


[FILES]

;Source: "..\release\vcredist_x86.exe"; DestDir: {tmp}; Flags: deleteafterinstall;             
Source: "..\release\*.dll"; DestDir: "{app}";   Flags:  overwritereadonly ignoreversion;   
Source: "..\release\tuxlerVPN.exe"; DestDir: "{app}";   Flags:  overwritereadonly ignoreversion; 
Source: "..\..\ExtensionHelperApp\ExtensionHelperApp\Output\ExtensionHelperApp.exe"; DestDir: "{app}";  DestName: "ExtensionHelperAppHelperTuxler.exe"; Flags:  overwritereadonly ignoreversion; 
Source: "..\release\platforms\*.dll"; DestDir: "{app}\platforms";   Flags:  overwritereadonly ignoreversion;
Source: "..\release\imageformats\*.dll"; DestDir: "{app}\imageformats";   Flags:  overwritereadonly ignoreversion;  
Source: "..\release\bearer\*.dll"; DestDir: "{app}\bearer";   Flags:  overwritereadonly ignoreversion;
Source: "..\release\sensors\*.dll"; DestDir: "{app}\sensors";   Flags:  overwritereadonly ignoreversion;  
Source: "..\build\license.txt"; DestDir: "{app}";   Flags:  overwritereadonly ignoreversion;     
Source: "..\sources.7z"; DestDir: "{app}";   Flags:  overwritereadonly ignoreversion recursesubdirs;    

[Icons]

Name: "{group}\Uninstall TuxlerVPN"; Filename: "{uninstallexe}"
Name: "{commondesktop}\tuxlerVPN"; Filename: "{app}\tuxlerVPN.exe"; WorkingDir: "{app}"  ;
Name: "{commonprograms}\tuxlerVPN"; Filename: "{app}\tuxlerVPN.exe"; WorkingDir: "{app}" ;
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\tuxlerVPN"; Filename: "{app}\tuxlerVPN.exe"; WorkingDir: "{app}" ;


[code]

const
  WM_CLOSE = $0010;
	NET_FW_SCOPE_ALL = 0;
	NET_FW_IP_VERSION_ANY = 2;
	NET_FW_PROFILE_DOMAIN = 0;
	NET_FW_PROFILE_STANDARD = 1;
	NET_FW_IP_PROTOCOL_TCP = 6;
	NET_FW_ACTION_ALLOW = 1;

  type HANDLE = LongInt;
     HMODULE = HANDLE;
pHMODULE = Array[0..255] of HMODULE;
LPDWORD = DWORD; PDWORD = Array[0..255] of DWORD;
LPTSTR = String;
const PROCESS_QUERY_INFORMATION = $400;
PROCESS_VM_READ = $10;
MAX_LENGTH = 255;


function CloseHandle(hObject : HANDLE) : BOOL;
external 'CloseHandle@kernel32.dll stdcall delayload';

function OpenProcess(dwDesiredAccess : DWORD; bInheritHandle : Boolean; dwProcessId : DWORD) : HANDLE;
external 'OpenProcess@kernel32.dll stdcall delayload';
function EnumProcesses(var pProcessIds : PDWORD; cb : DWORD; var pBytesReturned : DWORD) : BOOL;
external 'EnumProcesses@psapi.dll stdcall delayload';
function EnumProcessModulesEx(hProcess : HANDLE; var lphModule : pHMODULE; cb : DWORD; var lpcbNeeded : LPDWORD; dwFilterFlag : DWORD) : BOOL;
external 'EnumProcessModulesEx@psapi.dll stdcall delayload';function EnumProcessModules(hProcess : HANDLE; var lphModule : pHMODULE; cb : DWORD; var lpcbNeeded : LPDWORD) : BOOL;
external 'EnumProcessModules@psapi.dll stdcall delayload';
function GetModuleFileNameExA(hProcess : HANDLE; hModule : HMODULE; lpFilename : LPTSTR; nSize : DWORD) : DWORD;
external 'GetModuleFileNameExA@psapi.dll stdcall delayload';
function zylIsAppRunning(procName : String; fullPath : Boolean) : Boolean;
var found : Boolean;
filenameEnd : Integer;
filename : String;
NA : DWORD;
entry : DWORD;
maxEntries : DWORD;
processes : PDWORD;
lpFilename : LPTSTR;
hProcess : HANDLE;
hMod : pHMODULE;
isModuleShot: Boolean;
begin
SetLength(lpFilename, MAX_LENGTH);
found := False;
if (EnumProcesses(processes, SizeOf(processes), maxEntries)) then
begin
entry := 0;
maxEntries := maxEntries / SizeOf(maxEntries);
while ((not found) and (entry < maxEntries)) do begin
hProcess := OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ, False, processes[entry]);
if (hProcess <> 0) then
begin
isModuleShot := False;
if IsWin64 then
begin
isModuleShot := EnumProcessModulesEx(hProcess, hMod, SizeOf(hMod), NA, $3);
end else begin
isModuleShot := EnumProcessModules(hProcess, hMod, SizeOf(hMod), NA);
end;
if (isModuleShot) then
if (GetModuleFileNameExA(hProcess, hMod[0], lpFilename, Length(lpFilename)) > 0)
then begin
filenameEnd := Pos(#0, lpFilename);
filename := Copy(Lowercase(lpFilename), 1, filenameEnd - 1);
if (not fullpath) then
filename := ExtractFileName(filename);
if (AnsiLowercase(filename) = AnsiLowercase(procName)) then
found := True;
end;
CloseHandle(hProcess);
end;
entry := entry + 1;
end;
end;
Result := found;
end;


function countInstall() : Boolean;
var
  WinHttpReq: Variant;
begin
  begin
    begin
      try
      begin
      WinHttpReq := CreateOleObject('WinHttp.WinHttpRequest.5.1');
      WinHttpReq.Open('GET', 'http://ipsharkk.com/count_install.php?app_type=desktop', true)
      WinHttpReq.SetTimeouts(0, 2000, 2000, 2000)
      WinHttpReq.Send()
      WinHttpReq.WaitForResponse(2);
      end
      Except
      end;
    end;
  end;
  Result := true;
end;
   
function countUnInstall() : Boolean;
var
  WinHttpReq: Variant;
begin
  begin
    begin
      try
      begin
      WinHttpReq := CreateOleObject('WinHttp.WinHttpRequest.5.1');
      WinHttpReq.Open('GET', 'http://ipsharkk.com/count_install.php?type=uninstall&app_type=desktop', true)
      WinHttpReq.SetTimeouts(0, 2000, 2000, 2000)
      WinHttpReq.Send()
      WinHttpReq.WaitForResponse(2);
      end
      Except
      end;
    end;
  end;
  Result := true;
end;

function IsWindowsNT6: Boolean;
var
	Version: TWindowsVersion;
begin
	GetWindowsVersionEx(Version);
	Result := (Version.NTPlatform and (Version.Major >= 6));
end;

procedure AddFirewallException(AppName, FileName: string);
var
	FirewallObject: Variant;
	FirewallManager: Variant;
	FirewallProfile: Variant;
	PolicyObject: Variant;
	NewRule: Variant;
begin
	try
		if IsWindowsNT6() then
		begin
			// create new inbound firewall exception:
			PolicyObject := CreateOleObject('HNetCfg.FwPolicy2');
			NewRule := CreateOleObject('HNetCfg.FWRule');
			NewRule.Name := AppName + '';
			NewRule.Applicationname := FileName;
			NewRule.Protocol := NET_FW_IP_PROTOCOL_TCP;
			NewRule.EdgeTraversal := True;
			NewRule.Action := NET_FW_ACTION_ALLOW;
			NewRule.Enabled := True;
			PolicyObject.Rules.Add(NewRule);
		end
		else
		begin
			FirewallObject := CreateOleObject('HNetCfg.FwAuthorizedApplication');
			FirewallObject.ProcessImageFileName := FileName;
			FirewallObject.Name := AppName;
			FirewallObject.Scope := NET_FW_SCOPE_ALL;
			FirewallObject.IpVersion := NET_FW_IP_VERSION_ANY;
			FirewallObject.Enabled := True;

			FirewallManager := CreateOleObject('HNetCfg.FwMgr');

			FirewallProfile := FirewallManager.LocalPolicy.GetProfileByType(NET_FW_PROFILE_STANDARD);
			FirewallProfile.AuthorizedApplications.Add(FirewallObject);

			FirewallProfile := FirewallManager.LocalPolicy.GetProfileByType(NET_FW_PROFILE_DOMAIN);
			FirewallProfile.AuthorizedApplications.Add(FirewallObject);
		end;
	except
	end;
end;

procedure RemoveFirewallException(AppName, FileName: string);
var
	FirewallManager: Variant;
	FirewallProfile: Variant;
	PolicyObject: Variant;
begin
	try
		if IsWindowsNT6() then
		begin
			PolicyObject := CreateOleObject('HNetCfg.FwPolicy2');
			PolicyObject.Rules.Remove(AppName + '');
		end
		else
		begin
			FirewallManager := CreateOleObject('HNetCfg.FwMgr');

			FirewallProfile := FirewallManager.LocalPolicy.GetProfileByType(NET_FW_PROFILE_STANDARD);
			FireWallProfile.AuthorizedApplications.Remove(FileName);

			FirewallProfile := FirewallManager.LocalPolicy.GetProfileByType(NET_FW_PROFILE_DOMAIN);
			FireWallProfile.AuthorizedApplications.Remove(FileName);
		end;
	except
	end;
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin

	if (CurStep = ssPostInstall) then
	begin
		AddFirewallException('tuxlerVPN', ExpandConstant('{app}\tuxlerVPN.exe'));
		AddFirewallException('tuxlerVPN Helper 2', ExpandConstant('{app}\ExtensionHelperAppHelperTuxler.exe'));
	end;

     if (CurStep=ssDone) then
  begin
   if not WizardSilent then
   begin
    countInstall();
   end
  end;

end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
	if CurUninstallStep = usUninstall then
	begin
		RemoveFirewallException('tuxlerVPN', ExpandConstant('{app}\tuxlerVPN.exe'));
		RemoveFirewallException('tuxlerVPN Helper 2', ExpandConstant('{app}\ExtensionHelperAppHelperTuxler.exe'));
    countUnInstall();
	end;
end;


function InitializeUninstall(): Boolean;
  var
    ErrorCode: Integer;
    NetFrameWorkInstalled : Boolean;
    Result1 : Boolean;
    msi20Path : string;
    hWnd : Integer;
    ResultCode : Integer;
    Wnd: HWND;
begin

Wnd := FindWindowByWindowName('Tuxler');

Exec(ExpandConstant('{app}\tuxlerVPN.exe'), '--uninstall-close', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);
Exec(ExpandConstant('{sys}\taskkill.exe'),'/f /im ExtensionHelperAppHelperTuxler.exe','',SW_HIDE,ewWaitUntilTerminated,ErrorCode);
while zylIsAppRunning('ExtensionHelperAppHelperTuxler.exe', false) do Sleep(1000);

if Wnd <> 0 then
begin

SendMessage(Wnd, WM_CLOSE, 0, 111);

end

Result := true;
end;

    
 function getExePath(Default: String): String;
  var
     exepath : String;

 begin
     exepath := ExpandConstant('{srcexe}');
     result := exepath;
 end;

 function InitializeSetup(): Boolean;
var
    ErrorCode: Integer;
    NetFrameWorkInstalled : Boolean;
    Result1 : Boolean;
    msi20Path : string;
    hWnd : Integer;
    ResultCode : Integer;
    Wnd: HWND;
    ResultCode:   Integer;
    V: string;
    ipos: Integer;
    FilePath: string;
     FileName: string;

begin
  Exec(ExpandConstant('{sys}\taskkill.exe'),'/f /im ExtensionHelperAppHelperTuxler.exe','',SW_HIDE,ewWaitUntilTerminated,ErrorCode);

  while zylIsAppRunning('ExtensionHelperAppHelperTuxler.exe', false) do Sleep(1000);

Wnd := FindWindowByWindowName('Tuxler');

if Wnd <> 0 then
begin

SendMessage(Wnd, WM_CLOSE, 0, 111);

end

 Exec(ExpandConstant('{sys}\taskkill.exe'),'/f /im TuxlerFreeResidentialVPN.exe','',SW_HIDE,ewWaitUntilTerminated,ErrorCode);
  while zylIsAppRunning('TuxlerFreeResidentialVPN.exe', false) do Sleep(1000);



 if RegQueryStringValue(HKCU, 'Software\Microsoft\Windows\CurrentVersion\Run', 'Tuxler', V) then
begin

      ipos := Pos('"', V);

      if ipos <> 0 then begin

      V := Copy(V, 2, Length(V)-1);

      ipos := Pos('"', V);

      if ipos <> 0 then begin

      V := Copy(V, 1, ipos-1);



 Exec(V, '--uninstall-close', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);

 FileName := ExtractFileName(V);

 if (CompareStr(FileName, 'TuxlerFreeResidentialVPN.exe') = 0) then begin
 
  FilePath := ExtractFileDir(V);

  DelTree(FilePath, True, True, True);

 end; 
 end;
end; 
end;  
Result := true;       
end;

[UnInstallRun]
Filename: "{app}\tuxlerVPN.exe"; Parameters: "--uninstall"     ;
;Filename: "{app}\privoxy\privoxy.exe"; Parameters: "--uninstall"     ;
               
[Run]
;Filename: {tmp}\vcredist_x86.exe; Parameters: "/q /norestart"; StatusMsg: Installing VC++ 2013 Redistributables...
Filename: "{app}\tuxlerVPN.exe"; Description: {cm:LaunchProgram, TuxlerEvo}; Flags: nowait; Parameters:  "--install ""--UNIQUE_ID={code:getExePath}"""
;Filename: "http://tuxler.com/public/wp/choose-your-tuxler"; Flags: shellexec runasoriginaluser postinstall; Description: "Confirm email address";

[Registry]
ROOT: HKCU; Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "Tuxler"; ValueData: """{app}\tuxlerVPN.exe"" --auto-start";


