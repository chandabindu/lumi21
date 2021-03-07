#include "G4UImessenger.hh"
#include "globals.hh"

class lumiPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWith3Vector;

class lumiPrimaryGeneratorMessenger: public G4UImessenger{

public:
  lumiPrimaryGeneratorMessenger(lumiPrimaryGeneratorAction*);
  virtual ~lumiPrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  lumiPrimaryGeneratorAction* primaryGenAction;
  G4UIdirectory* gunDir;
  G4UIcmdWithAnInteger* setGunCmd;
  G4UIcmdWithADouble* setRasterCenterX;
  G4UIcmdWithADouble* setRasterCenterY;
  G4UIcmdWith3Vector* setBeamDirection;
};
