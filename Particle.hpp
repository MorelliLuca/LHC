#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

#include <iostream>
#include <string>
#include <vector>

class Particle {
  static std::vector<ParticleType *> particleType_;
  static int NParticleType_;
  static constexpr int maxNumParticleType{10};
  int index_;
  double Px_, Py_, Pz_;

  static int findParticle(std::string pName);

public:
  Particle():index_{0}{}
  Particle(std::string name, double Px = 0, double Py = 0, double Pz = 0);
  int getIndex() const;
  static void addParticleType(std::string name, double mass, int charge,
                              double width = 0);
  void setParticle(int index);
  void setParticle(std::string name);
  static void printParticleTypes();
  void printDetails() const;
  double getPx() const;
  double getPy() const;
  double getPz() const;
  double getMass() const;
  double getEnergy() const;
  double invMass(Particle const &particle2) const;
  void setP(double Px, double Py, double Pz);
};

std::ostream& operator<<(std::ostream& os,Particle const& particle);
#endif