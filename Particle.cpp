#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

#include <iostream>
#include <iterator>
#include <math.h>
#include <string>
#include <vector>

std::vector<ParticleType *> Particle::particleType_{};
int Particle::NParticleType_{0};

int Particle::findParticle(std::string pName) {

  if (NParticleType_ == 0) {
    return -1;
  }
  for (int i{0}; i < NParticleType_; ++i) {
    if (particleType_[i]->getName() == pName) {
      return i;
    }
  }

  return -1;
}

Particle::Particle(std::string name, double Px, double Py, double Pz)
    : Px_{Px}, Py_{Py}, Pz_{Pz} {
  index_ = findParticle(name);
  if (index_ == -1) {
    std::cout << "ERROR: Particle " << name << " has still not been defined"
              << '\n';
  }
}
int Particle::getIndex() const { return index_; }

void Particle::addParticleType(std::string name, double mass, int charge,
                               double width) {

  if (NParticleType_ == maxNumParticleType) {
    std::cerr << "ERROR: reached maximum type number, can't add a new one\n";
  } else {

    if (findParticle(name) == -1) {

      if (width == 0) {
        particleType_.push_back(new ParticleType{name, mass, charge});
      } else {
        particleType_.push_back(new ResonanceType{name, mass, charge, width});
      }
      ++NParticleType_;
    }
  }
}

void Particle::setParticle(int index) {
  if (index < NParticleType_ && index != -1) {
    index_ = index;
  } else {
    std::cerr << "ERROR: " << index
              << " is not a particle index alredy defined\n";
  }
}
void Particle::setParticle(std::string name) {
  setParticle(findParticle(name));
}

void Particle::printParticleTypes() {
  for (auto &it : particleType_) {
    it->print();
    std::cout << '\n';
  }
}

void Particle::printDetails() const {
  std::cout << "|Index:" << index_ << "|" << particleType_[index_]->getName()
            << "|Px:" << Px_ << "|Py:" << Py_ << "|Pz:" << Pz_<<'|';
}
double Particle::getPx() const { return Px_; }
double Particle::getPy() const { return Py_; }
double Particle::getPz() const { return Pz_; }
double Particle::getMass() const { return particleType_[index_]->getMass(); }
double Particle::getEnergy() const {
  return sqrt(getMass() * getMass() + Px_ * Px_ + Py_ * Py_ + Pz_ * Pz_);
}
double Particle::invMass(Particle const &p2) const {
  double PxTot{Px_ + p2.getPx()};
  double PyTot{Py_ + p2.getPy()};
  double PzTot{Pz_ + p2.getPz()};
  return sqrt(pow(getEnergy() + p2.getEnergy(), 2) - PxTot * PxTot -
              PyTot * PyTot - PzTot * PzTot);
}
void Particle::setP(double Px, double Py, double Pz) {
  Px_ = Px;
  Py_ = Py;
  Pz_ = Pz;
}

std::ostream& operator<<(std::ostream& os,Particle const& particle){
  particle.printDetails();
  return os;
}

