#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <string>
#include <iostream>

class ParticleType {
  std::string const name_;
  double const mass_;
  int const charge_;

public:
  ParticleType(std::string name, double mass, int charge)
      : name_{name}, mass_{mass}, charge_{charge} {}
  virtual void print() const;
  std::string const &getName() const;
  double const &getMass() const;
  int const &getCharge() const;
};

std::ostream& operator<<(std::ostream& os,ParticleType const& particleType); 

#endif