/*
	OCLTarget module
*/

#include "OCLMaterials.hh"
#include "OCLTarget.hh"

OCLTarget::OCLTarget()
{

  //----------------------------------------------------
  // Material definitions
  //----------------------------------------------------

  // Get materials
  OCLMaterials* fMat = OCLMaterials::GetInstance();

  silicon = fMat->GetMaterial("G4_Si");
  aluminum = fMat->GetMaterial("G4_Al");
  vacuum = fMat->GetMaterial("Vacuum");


  //
  // Create the solids.....
  //

  CreateSolids();
}


OCLTarget::~OCLTarget()
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
// Dummy class -- doesn't compile otherwise
// G4VPhysicalVolume* OCLTarget::Construct(){
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// void OCLTarget::SetPosition(G4ThreeVector thisPos) {
//   translatePos = thisPos*mm;
//   G4cout << " ----> OCLTarget will be placed at distance: " << translatePos/mm << " mm" << G4endl;
// }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void  OCLTarget::CreateSolids() {

  //
  // Geometry
  //

  // Target
  pX2Target = 16./2.*mm;
  pY2Target = 16./2.*mm;
  pZ2Target = 0.017/2.*mm; // approximation! with a 4mg/cm^2 Si target / density of silicon

  pX2TargetHole = 16./2.*mm;
  pY2TargetHole = 16./2.*mm;
  pZ2TargetHole = 2./2.*mm;

  pX2TargetHolder = 90./2.*mm;
  pY2TargetHolder = 23./2.*mm;
  pZ2TargetHolder = 2./2.*mm;

  solidTarget = new G4Box("Target",
                          pX2Target,
                          pY2Target,
                          pZ2Target);
  solidTargetHole = new G4Box("TargetHole",
                          pX2TargetHole,
                          pY2TargetHole,
                          pZ2TargetHole);
  solidTargetHolder = new G4Box("TargetHolder",
                            pX2TargetHolder,
                            pY2TargetHolder,
                            pZ2TargetHolder);
  logTarget = new G4LogicalVolume(solidTarget, silicon, "Target");
  logTargetHole = new G4LogicalVolume(solidTargetHole, vacuum, "TargetHole");
  logTargetHolder = new G4LogicalVolume(solidTargetHolder, aluminum, "TargetHolder");

}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void OCLTarget::Placement(G4int copyNo, G4VPhysicalVolume* physiMother, G4bool checkOverlaps)
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

   physTargetHole = new G4PVPlacement(0,
                                      G4ThreeVector(0,0,0),
                                      logTargetHole,
                                      "TargetHole",
                                      logTargetHolder,
                                      false,
                                      0,
                                      checkOverlaps);

   physTargetHolder = new G4PVPlacement(0,
                                        G4ThreeVector(0,0,pmone*pZ2TargetHolder),
                                        "TargetHolder",
                                        logTargetHolder,
                                        physiMother,
                                        false,
                                        0,
                                        checkOverlaps);

}



