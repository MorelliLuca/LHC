#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"

#include<iostream>

void analyze(){
gStyle->SetOptStat("emr");
gStyle->SetOptFit(1);
gStyle->SetHistFillColor(kCyan);
gStyle->SetHistLineColor(kAzure+10);

TFile* results = new TFile("Output.root","READ");

TH1F* hPType = (TH1F*)results->Get("hPType");
TH1F* hPhi =(TH1F*)results->Get("hPhi");
TH1F* hTheta=(TH1F*)results->Get("hTheta");
TH1F* hP =(TH1F*)results->Get("hP");
TH1F* hInvMass=(TH1F*)results->Get("hInvMass");
TH1F* hInvMOpp=(TH1F*)results->Get("hInvMOpp");
TH1F* hInvMSame=(TH1F*)results->Get("hInvMSame");
TH1F* hInvMPKSame=(TH1F*)results->Get("hInvMPKSame");
TH1F* hInvMPKOpp=(TH1F*)results->Get("hInvMPKOpp");
TH1F* hInvMDec=(TH1F*)results->Get("hInvMDec");


TCanvas* cFitPhi = new TCanvas("cFitPhi","Fit Phi distribution");
TCanvas* cFitTheta = new TCanvas("cFitTheta","Fit Theta distribution");
TCanvas* cFitP = new TCanvas("cFitP","Fit P distribution");
TCanvas* cSubPK = new TCanvas("cSubPK","Subtraction of invariant mass of Kaons and Pions Same and Opposite charge");
TCanvas* cSub = new TCanvas("cSub","Subtraction of invariant mass of particles of Same and Opposite charge");
TCanvas* cComp = new TCanvas("cComp","Comparison");

std::cout<<"Pions+:"<<hPType->GetBinContent(1)/hPType->GetEntries()*100<<"%\n"
         <<"Pions-:"<<hPType->GetBinContent(2)/hPType->GetEntries()*100<<"%\n"
         <<"Kaone+:"<<hPType->GetBinContent(3)/hPType->GetEntries()*100<<"%\n"
         <<"Kaons-:"<<hPType->GetBinContent(4)/hPType->GetEntries()*100<<"%\n"
         <<"Protons+:"<<hPType->GetBinContent(5)/hPType->GetEntries()*100<<"%\n"
         <<"Protons-:"<<hPType->GetBinContent(6)/hPType->GetEntries()*100<<"%\n"
         <<"K*"<<hPType->GetBinContent(7)/hPType->GetEntries()*100<<"%\n";

hPhi->Fit("pol0");
hTheta->Fit("pol0");
hP->Fit("expo");

TH1F* hSubPK{new TH1F(
      "hSubPK", "Subtraction of invariant mass of Kaons and Pions Same and Opposite charge", 1000,
      0, 5)};

hSubPK->Add(hInvMPKOpp,hInvMPKSame,1,-1);  
hSubPK->Fit("gaus","","",0.5,1.5);
hSubPK->SetXTitle("Mass [GeV/C^2]");
hSubPK->SetYTitle("Occurrences");
hSubPK->SetAxisRange(0.65,1.4);

TH1F* hSub{new TH1F(
      "hSub", "Subtraction of invariant mass of particles of Same and Opposite charge", 1000,
      0, 5)};

hSub->Add(hInvMOpp,hInvMSame,1,-1);  
hSub->Fit("gaus","","",0.5,1.5);
hSub->SetXTitle("Mass [GeV/C^2]");
hSub->SetYTitle("Occurrences");
hSub->SetAxisRange(0.65,1.4);

cFitPhi->cd();
hPhi->DrawCopy();
cFitTheta->cd();
hTheta->DrawCopy();
cFitP->cd();
hP->DrawCopy();
cSubPK->cd();
hSubPK->DrawCopy();
cSub->cd();
hSub->DrawCopy();
cComp->cd();

hSubPK->DrawCopy();
hSub->DrawCopy("SAME");
hInvMDec->DrawCopy("SAME HISTO");


results->Close();
}