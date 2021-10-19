#include "ParticleType.hpp"
#include <iostream>
#include <string>

void ParticleType::print() const {
  std::cout << '|' << name_ << "|Mass:" << mass_ << "Kg|Charge:" << charge_
            << "C|";
}

std::string const &ParticleType::getName() const { return name_; }

double const &ParticleType::getMass() const { return mass_; }

int const &ParticleType::getCharge() const { return charge_; }

std::ostream& operator<<(std::ostream& os,ParticleType const& particleType){
  particleType.print();
  return os;
}