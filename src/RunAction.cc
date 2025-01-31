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
/// \file B4/B4c/src/RunAction.cc
/// \brief Implementation of the B4::RunAction class

#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

namespace B4
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
  auto analysisManager = G4AnalysisManager::Instance();

  // Create directories
  // analysisManager->SetHistoDirectoryName("histograms");
  // analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple
  //

  // Creating ntuple
  analysisManager->CreateNtuple("B4", "Edep and TrackL");
  analysisManager->CreateNtupleIColumn("Particle");
  analysisManager->CreateNtupleDColumn("Energy(MeV)");
  analysisManager->CreateNtupleDColumn("Layer0 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer1 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer2 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer3 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer4 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer5 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer6 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer7 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer8 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer9 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer10 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer11 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer12 E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer13 E dep(MeV)");

  analysisManager->CreateNtupleDColumn("Total E dep(MeV)");
  analysisManager->CreateNtupleDColumn("Layer0 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer1 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer2 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer3 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer4 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer5 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer6 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer7 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer8 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer9 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer10 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer11 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer12 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Layer13 Track Length(mm)");
  analysisManager->CreateNtupleDColumn("Total Track Length(mm)");

  analysisManager->CreateNtupleDColumn("Interaction Depth(mm)");
  analysisManager->CreateNtupleIColumn("Interaction Layer");

  // analysisManager->CreateNtupleDColumn("Egap");
  // analysisManager->CreateNtupleDColumn("Lgap");
  // analysisManager->CreateNtupleIColumn("LNgap");

  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  // inform the runManager to save random number seed
  // G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "B4_deuteron_10GeV_100GeV.root";
  // Other supported output types:
  // G4String fileName = "B4.csv";
  // G4String fileName = "B4.hdf5";
  // G4String fileName = "B4.xml";
  analysisManager->OpenFile(fileName);
  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B4
