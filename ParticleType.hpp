//Header file ParticleType.hpp - Luca Morelli 2021

#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <string>
#include <iostream>

class ParticleType {
  //Data Members
  std::string const name_; 
  double const mass_;
  int const charge_;

public:
  //Constructor declaration
  ParticleType(std::string name, double mass, int charge)
      : name_{name}, mass_{mass}, charge_{charge} {}
  
  //Member function declaration
  virtual void print() const;
  std::string const &getName() const;
  double const &getMass() const;
  int const &getCharge() const;
};

//Operator overload
std::ostream& operator<<(std::ostream& os,ParticleType const& particleType); 

#endif
