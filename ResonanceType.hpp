#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "ParticleType.hpp"
#include <string>

class ResonanceType : public ParticleType {
  double const width_;

public:
  //  ParticleType() {}
  ResonanceType(std::string name, double mass, int charge, double width)
      : ParticleType(name, mass, charge), width_{width} {}   
  void print() const;
  double const &getWidth() const;
};

std::ostream& operator<<(std::ostream& os,ResonanceType const& resonanceType); 

#endif