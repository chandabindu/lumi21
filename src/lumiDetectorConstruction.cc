#include "lumiDetectorConstruction.hh"
#include "lumiDetectorMessenger.hh"
#include "lumiDetectorSD.hh"

#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GDMLParser.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "CLHEP/Units/SystemOfUnits.h"

lumiDetectorConstruction::lumiDetectorConstruction()
  :G4VUserDetectorConstruction(){
  detectorMessenger = new lumiDetectorMessenger(this);
}

lumiDetectorConstruction::~lumiDetectorConstruction(){
  delete detectorMessenger;
}

G4VPhysicalVolume* lumiDetectorConstruction::Construct(){
  gdmlParser.SetOverlapCheck(true);
  G4cout<< gdml_filename << " is used ." <<G4endl;
  gdmlParser.Read(gdml_filename);

  G4VPhysicalVolume* world_PV = gdmlParser.GetWorldVolume();

  
  //  Visualization
  G4VisAttributes* motherVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,0.0,0.0));
  motherVisAtt->SetVisibility(true);
  motherVisAtt->SetForceWireframe(true);
  world_PV->GetLogicalVolume()->SetVisAttributes(motherVisAtt);

  const G4GDMLAuxMapType* auxmap = gdmlParser.GetAuxMap();
  G4GDMLAuxMapType::const_iterator map_iter = auxmap->begin();
  while (map_iter!=auxmap->end()){
    G4GDMLAuxListType::const_iterator list_iter = (*map_iter).second.begin();

    while (list_iter!=(*map_iter).second.end()){
      const G4VisAttributes* visAtt = ((*map_iter).first)->GetVisAttributes();
      if((*list_iter).type=="Visibility"){
	G4Colour colour(1.0,1.0,1.0);
	if (visAtt)
	  colour = visAtt->GetColour();
	G4VisAttributes newAtt(colour);
	newAtt.SetForceSolid(true);
	newAtt.SetForceWireframe(false);
	if( (*list_iter).value=="true"){
	  newAtt.SetVisibility(true);
	}
	if( (*list_iter).value=="false")
	  newAtt.SetVisibility(false);
	
	((*map_iter).first)->SetVisAttributes(newAtt);
      }
      
      if ((*list_iter).type == "Color"){
	G4Colour colour(1.0,1.0,1.0);
	if (G4Colour::GetColour( (*list_iter).value, colour)){
	  G4VisAttributes colourAtt(colour);
	  ((*map_iter).first)->SetVisAttributes(colourAtt);
	}
      }
	
      list_iter++;
    }
    map_iter++;
  }
  G4cout<< "world_PV returned " << G4endl;
  return world_PV;
}

void lumiDetectorConstruction::ConstructSDandField(){

  const G4GDMLAuxMapType* auxmap = gdmlParser.GetAuxMap();
  G4cout<< "Construct SDandField " << G4endl;
  G4SDManager *sdManager = G4SDManager::GetSDMpointer();
  sdManager->SetVerboseLevel(1);
  
  char detector_name[200];
  G4int i=0;
  for(G4GDMLAuxMapType::const_iterator
	iter = auxmap->begin();
      iter !=auxmap->end(); iter++){
    
    G4LogicalVolume* mylogic = (*iter).first;
    for(G4GDMLAuxListType::const_iterator
	  vit = (*iter).second.begin();
	vit!=(*iter).second.end();vit++){
      if((*vit).type =="SensDet"){

	while(  vit!=(*iter).second.end() && (*vit).type!="DetNo" ){
	    vit++;
	}
	if ((*vit).type == "DetNo"){
	  G4cout << "Add DetNo" << G4endl;
	  G4String det_name = "SensDet_" + G4String((*vit).value);
	  lumiDetectorSD* aDetector = new lumiDetectorSD(det_name, atoi((*vit).value));
	  sdManager->AddNewDetector(aDetector);
	  G4cout << "Added SensDet " << det_name << " to sdManager" << G4endl;
	  mylogic->SetSensitiveDetector(aDetector);
	}
      } // end of if there is a SensDet
    } // end of aux list iter
  } // end of auxmap/logicV iter

}

void lumiDetectorConstruction::SetGDML(const G4String& filename){
  gdml_filename = filename;
}
  
