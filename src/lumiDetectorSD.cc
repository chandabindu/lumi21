#include "lumiDetectorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"

#include "G4SDManager.hh"
#include "G4VProcess.hh"

lumiDetectorSD::lumiDetectorSD(G4String SDName, G4int detID) :G4VSensitiveDetector(SDName){
  hitsCollection = NULL;
  HCID = -1;
  fDetID = detID;
  collectionName.insert("lumihce_"+G4String(std::to_string(detID)));
}


lumiDetectorSD::~lumiDetectorSD(){
}

void lumiDetectorSD::Initialize(G4HCofThisEvent *hce){
  hitsCollection = new lumiDetectorHitsCollection(SensitiveDetectorName,collectionName[0]);
  if(HCID<0){
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  }
  hce->AddHitsCollection(HCID,hitsCollection);
  // G4cout << "HCID: " << HCID << G4endl;
}

G4bool lumiDetectorSD::ProcessHits(G4Step *aStep, G4TouchableHistory *){
  const G4Track* aTrack = aStep->GetTrack();
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();

  if(preStepPoint->GetStepStatus()==fGeomBoundary){
    lumiDetectorHit *this_hit = new lumiDetectorHit();
    
    G4TouchableHistory *theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
    G4VPhysicalVolume *myPV = theTouchable->GetVolume(0);
    G4String pvName = myPV->GetName();
    this_hit->SetDetID(fDetID);
    G4ParticleDefinition* particle =aTrack->GetDefinition();
    
    this_hit->SetParticleID( particle->GetPDGEncoding() );
  //  G4bool fHitBefore = (*hitsCollection)[0]->GetHitBefore();
  //  if (particle_name=="e-"){
  //if(!fHitBefore){ // if it is the first hit
    //    (*hitsCollection)[0]->SetHitBefore(true);
    //    (*hitsCollection)[0]->SetEdep(0.0); 
      
    G4ThreeVector hit_pos = preStepPoint->GetPosition();
    this_hit->SetHitPos(hit_pos);

    G4double Etot = aTrack->GetTotalEnergy();
    this_hit->SetEtot(Etot);
    G4double Ekin = aTrack->GetKineticEnergy();
    this_hit->SetEkin(Ekin);

    G4int trackID = aTrack->GetTrackID();
    this_hit->SetTrackID(trackID);

    G4ThreeVector vertex_pos = aTrack->GetVertexPosition();
    this_hit->SetVertexPos(vertex_pos);

    G4ThreeVector momentum = aTrack->GetMomentum();
    this_hit->SetMomentum(momentum);
    
    const G4VProcess *creatorProcess = aTrack->GetCreatorProcess();
    if(creatorProcess!=0){
      G4String processName = creatorProcess->GetProcessName();
      this_hit->SetCreatorProcess(processName);
    }

    hitsCollection->insert(this_hit);
    return true;
  }
  else
    return false;
  //}
    // if(detID ==this_hit->GetDetID()){
    //   G4double edep = aStep->GetTotalEnergyDeposit();
    //   this_hit->AddEdep(edep);
    // }
  //}

}
