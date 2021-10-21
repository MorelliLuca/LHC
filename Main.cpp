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
  TH1F* hTheta{new TH1F("hTheta","Theta distrubtion",100,0,M_PI)};
  TH1F* hPhi{new TH1F("hPhi","Phi distribution",100,0,2*M_PI)};
  TH1F* hP{new TH1F("hP","Momentum distribution",100,0,5)};
  TH1F* hPTras{new TH1F("hPtras","Trasversal Momentium distribution",1000,0,5)};
  TH1F* hEnergy{new TH1F("hTEnergy","Energy Distribution",1000,0,5)};

  hPType->GetXaxis()->SetBinLabel(1,"Pione +");
  hPType->GetXaxis()->SetBinLabel(2,"Pione -");
  hPType->GetXaxis()->SetBinLabel(3,"Kaone +");
  hPType->GetXaxis()->SetBinLabel(4,"Kaone -");
  hPType->GetXaxis()->SetBinLabel(5,"Protone +");
  hPType->GetXaxis()->SetBinLabel(6,"Protone -");
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
    for(auto& it : genParticles){
      
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
  
  output->ls();

  output->Close();
  
  return 0;
}