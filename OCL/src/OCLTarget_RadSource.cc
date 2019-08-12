/*
  OCLTarget_RadSource module
*/

#include "OCLTarget_RadSource.hh"
#include "OCLMaterials.hh"

OCLTarget_RadSource::OCLTarget_RadSource()
{

  //----------------------------------------------------
  // Material definitions
  //----------------------------------------------------

  // Get materials
  OCLMaterials* fMat = OCLMaterials::GetInstance();
  pyrex = fMat->GetMaterial("G4_Pyrex_Glass");

  //
  // Create the solids.....
  //

  CreateSolids();
}


OCLTarget_RadSource::~OCLTarget_RadSource()
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void  OCLTarget_RadSource::CreateSolids() {

  //
  // Geometry
  //

  // Target
  pX2Target = 23./2.*mm;
  pY2Target = 11./2.*mm;
  pZ2Target = 2/2.*mm;

  solidTarget = new G4Box("Target",
                          pX2Target,
                          pY2Target,
                          pZ2Target);
  logTarget = new G4LogicalVolume(solidTarget, pyrex, "Target");
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void OCLTarget_RadSource::Placement(G4int copyNo, G4VPhysicalVolume* physiMother, G4bool checkOverlaps)
{
   double pmone = -1; // in principal one can adjust for forward/backward angles placement

   physTarget = new G4PVPlacement(0,
                                  G4ThreeVector(0,0,-pmone*pZ2Target),
                                  "Target",
                                  logTarget,
                                  physiMother,
                                  false,
                                  0,
                                  checkOverlaps);
}



