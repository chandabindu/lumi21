#include "lumiPrimaryGeneratorMessenger.hh"
#include "lumiPrimaryGeneratorAction.hh"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIdirectory.hh"

lumiPrimaryGeneratorMessenger::lumiPrimaryGeneratorMessenger(lumiPrimaryGeneratorAction* pga)
  :G4UImessenger(), primaryGenAction(pga){

  gunDir = new G4UIdirectory("/lumi/gun/");
  gunDir->SetGuidance("PrimaryGenerator control");

  setGunCmd = new G4UIcmdWithAnInteger("/lumi/gun/beamtype",this);
  setGunCmd->SetParameterName("beamType",true);
  setGunCmd->SetDefaultValue(0);
  setGunCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  setRasterCenterX = new G4UIcmdWithADouble("/lumi/gun/rastercenterX",this);
  setRasterCenterX->SetParameterName("raster_center_x",true);
  setRasterCenterX->SetDefaultValue(0);
  setRasterCenterX->AvailableForStates(G4State_PreInit,G4State_Idle);

  setRasterCenterY = new G4UIcmdWithADouble("/lumi/gun/rastercenterY",this);
  setRasterCenterY->SetParameterName("raster_center_y",true);
  setRasterCenterY->SetDefaultValue(0);
  setRasterCenterY->AvailableForStates(G4State_PreInit,G4State_Idle);

  setBeamDirection = new G4UIcmdWith3Vector("/lumi/gun/beamdirection",this);
  setBeamDirection->SetParameterName("px","py","pz",true,true);
  setBeamDirection->SetDefaultValue(G4ThreeVector(0,0,1));
  setBeamDirection->AvailableForStates(G4State_PreInit,G4State_Idle);

}

lumiPrimaryGeneratorMessenger::~lumiPrimaryGeneratorMessenger(){
  delete gunDir;
  delete setGunCmd;
  delete setRasterCenterY;
  delete setRasterCenterX;
  delete setBeamDirection;
}

void lumiPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue){

  if(command==setGunCmd){
    primaryGenAction->SetBeamType(setGunCmd->GetNewIntValue(newValue));
  }

  if(command==setRasterCenterX){
    primaryGenAction->SetRasterCenterX(setRasterCenterX->GetNewDoubleValue(newValue));
  }

  if(command==setRasterCenterY){
    primaryGenAction->SetRasterCenterY(setRasterCenterY->GetNewDoubleValue(newValue));
  }

  if(command==setBeamDirection){
    primaryGenAction->SetBeamDirection(setBeamDirection->GetNew3VectorValue(newValue));
  }

}

