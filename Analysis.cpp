// Analysis of data from collision events - Luca Morelli 2021

#include <iostream>
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TStyle.h"

void analyze() {
  // Setting graphs style
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1);
  gStyle->SetFitFormat("7.6g");
  gStyle->SetHistFillColor(kCyan);
  gStyle->SetHistLineColor(kAzure + 10);

  // Opening file with generated data
  TFile* results = new TFile("Output.root", "READ");

  // Getting histos from file
  TH1F* hPType = (TH1F*)results->Get("hPType");
  TH1F* hPhi = (TH1F*)results->Get("hPhi");
  TH1F* hTheta = (TH1F*)results->Get("hTheta");
  TH1F* hP = (TH1F*)results->Get("hP");
  TH1F* hInvMass = (TH1F*)results->Get("hInvMass");
  TH1F* hInvMOpp = (TH1F*)results->Get("hInvMOpp");
  TH1F* hInvMSame = (TH1F*)results->Get("hInvMSame");
  TH1F* hInvMPKSame = (TH1F*)results->Get("hInvMPKSame");
  TH1F* hInvMPKOpp = (TH1F*)results->Get("hInvMPKOpp");
  TH1F* hInvMDec = (TH1F*)results->Get("hInvMDec");

  // Printing Particles types data and errors
  std::cout << "Pions+:" << hPType->GetBinContent(1) << "+/-"
            << hPType->GetBinError(1) << "\n"
            << "Pions-:" << hPType->GetBinContent(2) << "+/-"
            << hPType->GetBinError(2) << "\n"
            << "Kaone+:" << hPType->GetBinContent(3) << "+/-"
            << hPType->GetBinError(3) << "\n"
            << "Kaons-:" << hPType->GetBinContent(4) << "+/-"
            << hPType->GetBinError(4) << "\n"
            << "Protons+:" << hPType->GetBinContent(5) << "+/-"
            << hPType->GetBinError(5) << "\n"
            << "Protons-:" << hPType->GetBinContent(6) << "+/-"
            << hPType->GetBinError(6) << "\n"
            << "K*" << hPType->GetBinContent(7) << "+/-"
            << hPType->GetBinError(7) << "\n";

  // Canvas for distribution histos
  TCanvas* cDis = new TCanvas("cDis", "Distributions measured", 1500, 1000);
  cDis->Divide(2, 2);

  // Drawing histos and fits
  cDis->cd(1);
  hPType->DrawCopy();

  cDis->cd(3);
  hPhi->Fit("pol0");
  hPhi->DrawCopy();

  cDis->cd(4);
  hTheta->Fit("pol0");
  hTheta->DrawCopy();

  cDis->cd(2);
  hP->Fit("expo");
  hP->DrawCopy();

  // Canvas for K* masses histos
  TCanvas* cMass = new TCanvas("cMass", "K* Masses", 3000, 500);
  cMass->Divide(3, 1);

  // Analysis of invariant mass histos
  // Two new histos are created subtracting same and oppostie charge histos

  // Pions and Kaons histo
  TH1F* hSubPK{new TH1F("hSubPK",
                        "Subtraction of invariant mass of Kaons and Pions of "
                        "Same and Opposite charge",
                        1000, 0, 5)};

  // Fills, fits and draws histo
  cMass->cd(3);
  hSubPK->Add(hInvMPKOpp, hInvMPKSame, 1, -1);
  hSubPK->Fit("gaus", "", "", 0.5, 1.5);
  hSubPK->SetXTitle("Mass [GeV/C^2]");
  hSubPK->SetYTitle("Occurrences");
  hSubPK->SetAxisRange(0.65, 1.4);
  hSubPK->DrawCopy();

  // All particles histo
  TH1F* hSub{new TH1F(
      "hSub",
      "Subtraction of invariant mass of particles of Same and Opposite charge",
      1000, 0, 5)};

  // Fills, fits and draws histo
  cMass->cd(2);
  hSub->Add(hInvMOpp, hInvMSame, 1, -1);
  hSub->Fit("gaus", "", "", 0.5, 1.5);
  hSub->SetXTitle("Mass [GeV/C^2]");
  hSub->SetYTitle("Occurrences");
  hSub->SetAxisRange(0.65, 1.4);
  hSub->DrawCopy();

  // Fits and draws histo of invarant masses of particles created by decayment
  cMass->cd(1);
  hInvMDec->Fit("gaus");
  hInvMDec->SetAxisRange(0.6, 1.2);
  hInvMDec->SetFillColor(kCyan);
  hInvMDec->SetLineColor(kAzure + 10);
  hInvMDec->DrawCopy();

  // Print canvases onto png files
  cMass->Print("Comparison.png");
  cDis->Print("Distributions.png");

  // Close file
  results->Close();
}