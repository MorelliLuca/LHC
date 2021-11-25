#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"

#include<iostream>

void analyze(){
gStyle->SetOptStat("e");
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



TCanvas* cDis = new TCanvas("cDis","Distributions measured",1500,1000);
cDis->Divide(2,2);
TCanvas* cDis2 = new TCanvas("cDis2","Distributions measured",3000 , 500);
cDis2->Divide(3,1);
TCanvas* cMass = new TCanvas("cMass","K* Masses");
cMass->Divide(2,2);


std::cout<<"Pions+:"<<hPType->GetBinContent(1)<<"+/-"<<hPType->GetBinError(1)<<"\n"
         <<"Pions-:"<<hPType->GetBinContent(2)<<"+/-"<<hPType->GetBinError(2)<<"\n"
         <<"Kaone+:"<<hPType->GetBinContent(3)<<"+/-"<<hPType->GetBinError(3)<<"\n"
         <<"Kaons-:"<<hPType->GetBinContent(4)<<"+/-"<<hPType->GetBinError(4)<<"\n"
         <<"Protons+:"<<hPType->GetBinContent(5)<<"+/-"<<hPType->GetBinError(5)<<"\n"
         <<"Protons-:"<<hPType->GetBinContent(6)<<"+/-"<<hPType->GetBinError(7)<<"\n"
         <<"K*"<<hPType->GetBinContent(7)<<"+/-"<<hPType->GetBinError(7)<<"\n";

hPhi->Fit("pol0");
hTheta->Fit("pol0");
hP->Fit("expo");

TH1F* hSubPK{new TH1F(
      "hSubPK", "Subtraction of invariant mass of Kaons and Pions of Same and Opposite charge", 1000,
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


hInvMDec->Fit("gaus");
hInvMDec->SetAxisRange(0.6,1.2);
hInvMDec->SetFillColor(kCyan);
hInvMDec->SetLineColor(kAzure+10);


cDis->cd(1);
hPType->DrawCopy();
cDis->cd(2);
hP->DrawCopy();
cDis->cd(3);
hPhi->DrawCopy();
cDis->cd(4);
hTheta->DrawCopy();

cDis2->cd(1);
hInvMDec->DrawCopy();
cDis2->cd(2);
hSub->DrawCopy();
cDis2->cd(3);
hSubPK->DrawCopy();



cDis2->Print("Comparison.png");
cDis->Print("Distributions.png");





results->Close();
}