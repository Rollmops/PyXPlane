[Setup]
OutputDir=build
AppName=PyXPlane
AppVersion=0.1
DisableProgramGroupPage=yes
DefaultDirName="C:\Program Files\X-Plane"
AppendDefaultDirName=no
AlwaysShowDirOnReadyPage=no
DirExistsWarning=no

[Files]
Source: "build\win.xpl"; DestDir: "{app}\Resources\plugins\PyXPlane\64"
Source: "lib\libboost*.dll"; DestDir: "{app}\Resources\plugins\PyXPlane\64"
Source: "scripts\*.py"; DestDir: "{app}\Resources\plugins\PyXPlane\Scripts"

[Code]
procedure OnDirEditChange(Sender: TObject);
begin
  WizardForm.NextButton.Enabled := DirExists(AddBackslash(WizardDirValue) + 'Resources')
    and FileExists(AddBackslash(WizardDirValue) + 'X-Plane.exe');
end;

procedure CurPageChanged(CurPageID: Integer);
begin
  if CurPageID = wpSelectDir then
    OnDirEditChange(nil);
end;

procedure InitializeWizard;
begin
  WizardForm.SelectDirLabel.Caption := 'X-Plane installation directory';
  WizardForm.SelectDirBrowseLabel.Caption := 'Please select a valid X-Plane installation directory, then press Next';
  WizardForm.DirEdit.OnChange := @OnDirEditChange;

end;