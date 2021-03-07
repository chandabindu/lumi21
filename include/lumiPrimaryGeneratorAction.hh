#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "g4root.hh"

class G4ParticleGun;
class G4Event;
class lumiPrimaryGeneratorMessenger;

class lumiPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction{
public:
  lumiPrimaryGeneratorAction();
  virtual ~lumiPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event *event);
  void GeneratePrimaries_origin(G4Event *event);
  void GeneratePrimaries_raster1x4(G4Event *event);
  void GeneratePrimaries_raster4x4(G4Event *event);
  void GeneratePrimaries_raster6x4(G4Event *event);
  void GeneratePrimaries_raster2x2(G4Event *event);
  void SetBeamType(G4int);
  void SetRasterCenterX(G4double);
  void SetRasterCenterY(G4double);
  void SetBeamDirection(G4ThreeVector);

private:
  G4ParticleGun* fParticleGun;
  G4int runType;
  lumiPrimaryGeneratorMessenger *primaryMessenger;
  G4double raster_center_x;
  G4double raster_center_y;

};
