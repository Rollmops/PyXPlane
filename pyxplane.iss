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
Source: "setup.py"; DestDir: {app}
Source: "TODOs"; DestDir: {app}

[Code]
procedure OnDirEditChange(Sender: TObject);
begin
  WizardForm.NextButton.Enabled := FileExists(AddBackslash(WizardDirValue) + 'huhu.txt');
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