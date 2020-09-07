//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
 // fVisAttributes()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  
  //NOTE: ENVELOPE REMOVED BECAUSE IRRELEVANT
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //       G4VisAttributes* MaterialVisAttributes = new G4VisAttributes(blue);
          


  // World
  //
  G4double world_sizeXY = 10*m;
  G4double world_sizeZ  = 10*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

         
                           
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  
     
  // Shape 1
  //  
  G4Material* G4_Si = nist->FindOrBuildMaterial("G4_Si");
  G4ThreeVector posTrack1 = G4ThreeVector(0, 0, -5*mm);
  G4ThreeVector posTrack2 = G4ThreeVector(0, 0, 5*mm);
  G4double Si_Len = 100*mm;
  G4double Si_Wid = 100*mm;
  G4double Si_Dep = 100*um;



     
  // Conical section shape REMOVE THIS      
 // G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
 // G4double shape1_rminb =  0.*cm, shape1_rmaxb = 4.*cm;
 // G4double shape1_hz = 3.*cm;
 // G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
 // G4Cons* solidShape1 =    
  //  new G4Cons("Shape1", 
   // shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
   // shape1_phimin, shape1_phimax);
                      
  G4Box* tracker = 
    new G4Box("tracker",  //its name
              0.5*Si_Len, 0.5*Si_Wid, 0.5*Si_Dep);


  G4LogicalVolume* trackerLogical =                         
    new G4LogicalVolume(tracker,         //its solid
                        G4_Si,          //its material
                        "tracker");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    posTrack1,                    //at position
                    trackerLogical,             //its logical volume
                    "Tracker1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  new G4PVPlacement(0,
                    posTrack2,
		    trackerLogical,
		    "Tracker2",
		    logicWorld,
                    false,
                    0,
                    checkOverlaps);


//  G4VisAttributes* MaterialVisAttributes = new G4VisAttributes (brown);
//tracker ->SetVisAttributes(MaterialVisAttributes);

  //     
  // Shape 2
  // BELOW COMMENTED  OUT AS IRRELEVANT
 // G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
 // G4ThreeVector pos2 = G4ThreeVector(0, -1*cm, 7*cm);

  // Trapezoid shape       
 // G4double shape2_dxa = 12*cm, shape2_dxb = 12*cm;
 // G4double shape2_dya = 10*cm, shape2_dyb = 16*cm;
 // G4double shape2_dz  = 6*cm;      
 // G4Trd* solidShape2 =    
   // new G4Trd("Shape2",                      //its name
     //         0.5*shape2_dxa, 0.5*shape2_dxb, 
       //       0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size
                
 // G4LogicalVolume* logicShape2 =                         
   // new G4LogicalVolume(solidShape2,         //its solid
     //                   shape2_mat,          //its material
       //                 "Shape2");           //its name
               
//  new G4PVPlacement(0,                       //no rotation
  //                  pos2,                    //at position
    //                logicShape2,             //its logical volume
      //              "Shape2",                //its name
        //            logicEnv,                //its mother  volume
          //          false,                   //no boolean operation
            //        0,                       //copy number
              //      checkOverlaps);          //overlaps checking
              
  

// Set Shape2 as scoring volume
  //

//Adding second slab of material (Al)
//
G4Material* G4_Al = nist->FindOrBuildMaterial("G4_Al");
G4ThreeVector posTrack1m = G4ThreeVector(0, 0, -2*mm);
G4ThreeVector posTrack2m = G4ThreeVector(0, 0, 2*mm);
G4double Al_Len = 30*mm;
G4double Al_Wid = 30*mm;
G4double Al_Dep = 30*um;

G4Box*matTracker = 
	new G4Box("matTracker",        //its name     
                0.5*Al_Len, 0.5*Al_Wid, 0.5*Al_Dep); //its size


G4LogicalVolume* trackerLogical2 = 
	new G4LogicalVolume(matTracker, //its solid
	                    G4_Al, //its material
			    "matTracker"); //its name



new G4PVPlacement (0,
	 posTrack1m,
	 trackerLogical2,
	 "Al Tracker1",
	 logicWorld, //may need to change mother volume	
	 false, 
	0,	
	 checkOverlaps);

new G4PVPlacement (0,
	 posTrack2m,
	 trackerLogical2,
	 "AlTracker2",
	 logicWorld,
	 false,
	 0,
	 checkOverlaps);




 // fScoringVolume = trackerLogical;

 //G4VisAttributes * visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.9)); 
 //fScoringVolume->SetVisAttributes(visAttributes);
 //fVisAttributes.push_back(visAttributes);

  //
  //always return the physical World
  //



  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
