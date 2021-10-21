#include <vector>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "TRandom.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"

R__LOAD_LIBRARY(ParticleType_cpp.so)
R__LOAD_LIBRARY(ResonanceType_cpp.so)
R__LOAD_LIBRARY(Particle_cpp.so)


int Main() {
gStyle->SetOptStat("emr");
gStyle->SetHistFillColor(kCyan);

  Particle::addParticleType("Pione+", 0.13957, 1);
  Particle::addParticleType("Pione-", 0.13957, -1);
  Particle::addParticleType("Kaone+", 0.49367, 1);
  Particle::addParticleType("Kaone-", 0.49367, -1);
  Particle::addParticleType("Protone+", 0.93827, 1);
  Particle::addParticleType("Protone-", 0.93827, -1);
  Particle::addParticleType("K*", 0.89166, 0, 0.050);

  std::vector<Particle> genParticles;
  std::vector<Particle> decParticles;
  genParticles.reserve(100);
  decParticles.reserve(20);

  TH1F* hPType{new TH1F("hPType","Types of particles generated",7,0,7)};
  TH1F* hTheta{new TH1F("hTheta","Theta distriubtion",100,0,M_PI)};
  TH1F* hPhi{new TH1F("hPhi","Phi distribution",100,0,2*M_PI)};
  TH1F* hP{new TH1F("hP","Momentum distribution",100,0,5)};
  TH1F* hPTras{new TH1F("hPtras","Trasversal Momentum distribution",1000,0,5)};
  TH1F* hEnergy{new TH1F("hTEnergy","Energy Distribution",1000,0,5)};
  TH1F* hInvMass{new TH1F("hInvMass","Invariant mass",100,0,5)};
  TH1F* hInvMSame{new TH1F("hInvMSame","Invariant mass calculated with same charge particles",100,0,5)};
  TH1F* hInvMOpp{new TH1F("hInvMOpp","Invariant mass calculated with opposite charge particles",100,0,5)};
  TH1F* hInvMPKSame{new TH1F("hInvMPKSame","Invariant mass calculated with same charge Kaons and Pions",100,0,5)};
  TH1F* hInvMPKOpp{new TH1F("hInvMPKOpp","Invariant mass calculated with opposite charge Kaons and Pions",100,0,5)};
  TH1F* hInvMDec{new TH1F("hInvMDec","Invariant mass calculated with particles from decayment",100,0,5)};


  hPType->GetXaxis()->SetBinLabel(1,"Pions +");
  hPType->GetXaxis()->SetBinLabel(2,"Pions -");
  hPType->GetXaxis()->SetBinLabel(3,"Kaons +");
  hPType->GetXaxis()->SetBinLabel(4,"Kaons -");
  hPType->GetXaxis()->SetBinLabel(5,"Protons +");
  hPType->GetXaxis()->SetBinLabel(6,"Protons -");
  hPType->GetXaxis()->SetBinLabel(7,"K*");
  
  hPType->SetXTitle("Particle Type");
  hPType->SetYTitle("Occurrences");
  hTheta->SetXTitle("Theta [Rad]");
  hTheta->SetYTitle("Occurrences");
  hPhi->SetXTitle("Phi [Rad]");
  hPhi->SetYTitle("Occurrences");
  hP->SetXTitle("P [GeV]");
  hP->SetYTitle("Occurrences");
  hPTras->SetXTitle("Trasversal Momentum [GeV]");
  hPTras->SetYTitle("Occurrences");
  hEnergy->SetXTitle("Energy [GeV]");
  hEnergy->SetYTitle("Occurrences");
  hInvMass->SetXTitle("Mass [GeV/C^2]");
  hInvMass->SetYTitle("Occurrences");
  hInvMOpp->SetXTitle("Mass [GeV/C^2]");
  hInvMOpp->SetYTitle("Occurrences");
  hInvMSame->SetXTitle("Mass [GeV/C^2]");
  hInvMSame->SetYTitle("Occurrences");
  hInvMPKSame->SetXTitle("Mass [GeV/C^2]");
  hInvMPKSame->SetYTitle("Occurrences");
  hInvMPKOpp->SetXTitle("Mass [GeV/C^2]");
  hInvMPKOpp->SetYTitle("Occurrences");
  hInvMDec->SetXTitle("Mass [GeV/C^2]");
  hInvMDec->SetYTitle("Occurrences");

  gRandom->SetSeed();

  for (int eventCount{0}; eventCount !=1E5; ++eventCount) {
    for (int partcilesCount{0}; partcilesCount != 100; ++partcilesCount) {
      Particle newParticle{};
      
      double phi{gRandom->Uniform(0, 2 * M_PI)};
      double theta{gRandom->Uniform(0, M_PI)};
      double modP{gRandom->Exp(1)};

      hPhi->Fill(phi);
      hTheta->Fill(theta);
      hP->Fill(modP);

      newParticle.setP(modP * sin(theta) * cos(phi),
                                        modP * sin(theta) * sin(phi),
                                        modP * cos(theta));

      double rand{gRandom->Uniform(0, 100)};

      if (rand <= 1) {
        newParticle.setParticle("K*");
        Particle decP1, decP2;
        if(gRandom->Integer(2)==0){
          decP1.setParticle("Pione+");
          decP2.setParticle("Kaone-");
        }else{
          decP1.setParticle("Pione-");
          decP2.setParticle("Kaone+");
        }
        if(newParticle.decay2body(decP1,decP2)==0){
        decParticles.push_back(decP1);
        decParticles.push_back(decP2);
        }
      } else if (rand <= 11) {
        if (gRandom->Integer(2) == 0)
          newParticle.setParticle("Kaone+");
        else
          newParticle.setParticle("Kaone-");
      } else if (rand <= 20) {
        if (gRandom->Integer(2) == 0)
          newParticle.setParticle("Protone+");
        else
          newParticle.setParticle("Protone-");
      } else {
        if (gRandom->Integer(2) == 0)
          newParticle.setParticle("Pione+");
        else
          newParticle.setParticle("Pione-");
      }
      genParticles.push_back(newParticle);
    }
    for(auto& it : genParticles){
      hPType->Fill(it.getIndex());
      hPTras->Fill(sqrt(it.getPx()*it.getPx()+it.getPy()*it.getPy()));
      hEnergy->Fill(it.getEnergy());

    }
    genParticles.insert(genParticles.end(),decParticles.begin(),decParticles.end());
    
    for(auto p1{genParticles.begin()};p1!=genParticles.end();++p1){
      for(auto p2{++p1};p2!=genParticles.end();++p2)
      {
        hInvMass->Fill(p1->invMass(*p2));
        if(p1->getCharge()*p2->getCharge()>0){
          hInvMSame->Fill(p1->invMass(*p2));
          if(p1->getMass()+p2->getMass()==0.63324) hInvMPKSame->Fill(p1->invMass(*p2));
        } 
        if(p1->getCharge()*p2->getCharge()<0) {
          hInvMOpp->Fill(p1->invMass(*p2));
          if(p1->getMass()+p2->getMass()==0.63324) hInvMPKOpp->Fill(p1->invMass(*p2));
        }
      }
    }

    for(auto p{decParticles.begin()};p!=decParticles.end();++p)
    {
        hInvMDec->Fill(p->invMass(*(++p)));
    }

    genParticles.clear();
    decParticles.clear();


  }
  
  //TCanvas *genralCanvas{new TCanvas()};

  TFile* output{new TFile("Output.root","RECREATE")};
  output->cd();

  hPType->Write();
  hPhi->Write();
  hTheta->Write();
  hP->Write();
  hPTras->Write();
  hEnergy->Write();
  hInvMass->Write();
  hInvMOpp->Write();
  hInvMSame->Write();
  hInvMPKSame->Write();
  hInvMPKOpp->Write();
  hInvMDec->Write();
  
  output->ls();

  output->Close();
  
  return 0;
}