// Simulation of collision events - Luca Morelli 2021

// COMPILING INSTRUCTION:
// 1) Open Root in this directory
//
// 2) (Only the first time or in order to modify ParticleType, ResonanceType or
// Particle)
//   Compile ParticleType.cpp, ResonanceType.cpp or Particle.cpp using :
//   for example       .L Particle.cpp+
//   (These files must be compiled in order: ParticleType.cpp,
//   ResonanceType.cpp, Particle.cpp)
//
// 3) Compile Simulation.cpp using:
//                     .L Simulation.cpp+
//
// 4) Run the Macro using:
//                      simulation()
//
// Results are saved in Output.root

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

#include <iomanip>
#include <iostream>
#include <vector>
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TStyle.h"

// Instruction to auto link precompiled libraries for Root
R__LOAD_LIBRARY(ParticleType_cpp.so)
R__LOAD_LIBRARY(ResonanceType_cpp.so)
R__LOAD_LIBRARY(Particle_cpp.so)

// ProgressBar function - prints a progress bar during execution
void progressBar(double status, double max) {
  std::cout << "\033[34m" << std::fixed << std::setprecision(0)
            << status / max * 100 << "%\033[0m|";
  for (double i{0}; i != 30; ++i) {
    if (status / max < i / 30.)
      std::cout << " ";
    else
      std::cout << "\033[7;32m \033[0m";
  }
  if (status != max - 1)
    std::cout << "|\r";
  else
    std::cout << "|\n";
}

/* Simulation */

void simulate() {
  // Global style settings for graph

  gStyle->SetOptStat("emr");
  gStyle->SetHistFillColor(kCyan);

  // Initialization of the types of particles
  Particle::addParticleType("Pione+", 0.13957, 1);
  Particle::addParticleType("Pione-", 0.13957, -1);
  Particle::addParticleType("Kaone+", 0.49367, 1);
  Particle::addParticleType("Kaone-", 0.49367, -1);
  Particle::addParticleType("Protone+", 0.93827, 1);
  Particle::addParticleType("Protone-", 0.93827, -1);
  Particle::addParticleType("K*", 0.89166, 0, 0.050);

  // Initialization of vectors to contain particles
  std::vector<Particle> genParticles;  // Particles generated from the event
  std::vector<Particle> decParticles;  // Particles generated by decay
  genParticles.reserve(100);
  decParticles.reserve(20);

  // Histograms initialization and style
  TH1F* hPType{new TH1F("hPType", "Types of particles generated", 7, 0, 7)};
  TH1F* hTheta{new TH1F("hTheta", "Theta distriubtion", 100, 0, M_PI)};
  TH1F* hPhi{new TH1F("hPhi", "Phi distribution", 100, 0, 2 * M_PI)};
  TH1F* hP{new TH1F("hP", "Momentum distribution", 100, 0, 5)};
  TH1F* hPTras{
      new TH1F("hPtras", "Trasversal Momentum distribution", 1000, 0, 5)};
  TH1F* hEnergy{new TH1F("hTEnergy", "Energy Distribution", 1000, 0, 5)};
  TH1F* hInvMass{new TH1F("hInvMass", "Invariant mass", 1000, 0, 5)};
  TH1F* hInvMSame{new TH1F(
      "hInvMSame", "Invariant mass calculated with same charge particles", 1000,
      0, 5)};
  TH1F* hInvMOpp{new TH1F(
      "hInvMOpp", "Invariant mass calculated with opposite charge particles",
      1000, 0, 5)};
  TH1F* hInvMPKSame{
      new TH1F("hInvMPKSame",
               "Invariant mass calculated with same charge Kaons and Pions",
               1000, 0, 5)};
  TH1F* hInvMPKOpp{
      new TH1F("hInvMPKOpp",
               "Invariant mass calculated with opposite charge Kaons and Pions",
               1000, 0, 5)};
  TH1F* hInvMDec{new TH1F(
      "hInvMDec", "Invariant mass calculated with particles from decayment",
      1000, .5, 1.5)};

  hPType->GetXaxis()->SetBinLabel(1, "Pions +");
  hPType->GetXaxis()->SetBinLabel(2, "Pions -");
  hPType->GetXaxis()->SetBinLabel(3, "Kaons +");
  hPType->GetXaxis()->SetBinLabel(4, "Kaons -");
  hPType->GetXaxis()->SetBinLabel(5, "Protons +");
  hPType->GetXaxis()->SetBinLabel(6, "Protons -");
  hPType->GetXaxis()->SetBinLabel(7, "K*");

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

  hInvMass->Sumw2();
  hInvMOpp->Sumw2();
  hInvMSame->Sumw2();
  hInvMPKSame->Sumw2();
  hInvMPKOpp->Sumw2();
  hInvMDec->Sumw2();

  gRandom->SetSeed();

  // Start of the 10^5 Events, 100 particles per Event
  for (int eventCount{0}; eventCount != 1E5; ++eventCount) {
    // Event
    for (int partcilesCount{0}; partcilesCount != 100; ++partcilesCount) {
      // Generation of a new Particle
      Particle newParticle{};

      // Random generation of momentum
      double phi{gRandom->Uniform(0, 2 * M_PI)};
      double theta{gRandom->Uniform(0, M_PI)};
      double modP{gRandom->Exp(1)};

      // Filling momentum Histos
      hPhi->Fill(phi);
      hTheta->Fill(theta);
      hP->Fill(modP);

      // Converting in cartesian coordinates and setting momentum
      newParticle.setP(modP * sin(theta) * cos(phi),
                       modP * sin(theta) * sin(phi), modP * cos(theta));

      // Random generation of the type of the new Particle
      double rand{gRandom->Uniform(0, 100)};

      if (rand <= 1) {
        newParticle.setParticle("K*");
        // Decayment of K*
        Particle decP1, decP2;  // Decayment results
        // Random generation of the type of decay
        if (gRandom->Integer(2) == 0) {
          decP1.setParticle("Pione+");
          decP2.setParticle("Kaone-");
        } else {
          decP1.setParticle("Pione-");
          decP2.setParticle("Kaone+");
        }
        // Decay calculation, if decay can happen the resulting particles are
        // added to decParticles
        if (newParticle.decay2body(decP1, decP2) == 0) {
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
      // Adding the new particle to genParticles
      genParticles.push_back(newParticle);

      // Adding data to histos
      hPType->Fill(newParticle.getIndex());
      hPTras->Fill(sqrt(newParticle.getPx() * newParticle.getPx() +
                        newParticle.getPy() * newParticle.getPy()));
      hEnergy->Fill(newParticle.getEnergy());
    }

    // Adding decayment results at the end of genParticles
    genParticles.insert(genParticles.end(), decParticles.begin(),
                        decParticles.end());

    // Filling invarant mass histos with data
    for (auto p1{genParticles.begin()}; p1 != genParticles.end(); ++p1) {
      if (p1->getIndex() != 6) {
        for (auto p2{p1 + 1}; p2 != genParticles.end(); ++p2) {
          double invMass{p1->invMass(*p2)};
          if (p2->getIndex() != 6) {
            hInvMass->Fill(invMass);
            if (p1->getCharge() * p2->getCharge() > 0) {
              hInvMSame->Fill(invMass);
              if (p1->getMass() + p2->getMass() == 0.63324)
                hInvMPKSame->Fill(invMass);
            }
            if (p1->getCharge() * p2->getCharge() < 0) {
              hInvMOpp->Fill(invMass);
              if (p1->getMass() + p2->getMass() == 0.63324)
                hInvMPKOpp->Fill(invMass);
            }
          }
        }
      }
    }

    for (auto p{decParticles.begin()}; p != decParticles.end(); ++p) {
      hInvMDec->Fill(p->invMass(*(++p)));
    }

    // Clearing used vector for new Events
    genParticles.clear();
    decParticles.clear();

    progressBar(eventCount, 1E5);
  }

  // Creating a root file and writing aquired data
  TFile* output{new TFile("Output.root", "RECREATE")};
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
}