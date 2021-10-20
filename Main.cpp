#include <vector>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "TRandom.h"

int main() {
  Particle::addParticleType("Pione+", 0.13957, 1);
  Particle::addParticleType("Pione-", 0.13957, -1);
  Particle::addParticleType("Kaone+", 0.49367, 1);
  Particle::addParticleType("Kaone-", 0.49367, -1);
  Particle::addParticleType("Protone+", 0.93827, 1);
  Particle::addParticleType("Protone-", 0.93827, -1);
  Particle::addParticleType("K*", 0.89166, 0, 0.050);

  std::vector<Particle> genParticles(120, Particle());

  gRandom->SetSeed();

  for (int eventCount{0}; eventCount = !1E5; ++eventCount) {
    for (int partcilesCount{0}; partcilesCount != 100; ++partcilesCount) {
      double phi{gRandom->Uniform(0, 2 * M_PI)};
      double theta{gRandom->Uniform(0, M_PI)};
      double modP{gRandom->Exp(1)};

      genParticles[partcilesCount].setP(modP * sin(theta) * cos(phi),
                                        modP * sin(theta) * sin(phi),
                                        modP * cos(theta));

      double rand{gRandom->Uniform(0, 100)};

      if (rand <= 1) {
        genParticles[partcilesCount].setParticle("K*");
      } else if (rand <= 11) {
        if (gRandom->Integer(2) == 0)
          genParticles[partcilesCount].setParticle("Kaone+");
        else
          genParticles[partcilesCount].setParticle("Kaone-");
      } else if (rand <= 20) {
        if (gRandom->Integer(2) == 0)
          genParticles[partcilesCount].setParticle("Protone+");
        else
          genParticles[partcilesCount].setParticle("Protone-");
      } else {
        if (gRandom->Integer(2) == 0)
          genParticles[partcilesCount].setParticle("Pione+");
        else
          genParticles[partcilesCount].setParticle("Pione-");
      }
    }
  }
  return 0;
}