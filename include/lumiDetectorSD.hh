#include "G4VSensitiveDetector.hh"
#include "lumiDetectorHit.hh"
#include "G4Step.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class lumiDetectorSD : public G4VSensitiveDetector{
public:
  lumiDetectorSD(G4String SDName, G4int detID);
  virtual ~lumiDetectorSD();

  virtual void Initialize(G4HCofThisEvent *hce);
  virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *);
  inline void SetDetID(G4int a){ fDetID=a;};
private:
  lumiDetectorHitsCollection* hitsCollection;
  G4int HCID;
  G4int fDetID;
};
