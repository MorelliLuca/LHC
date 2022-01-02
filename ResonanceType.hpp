// Header file ResonanceType.hpp - Luca Morelli 2021

#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP
#include "ParticleType.hpp"

#include <string>

// ResonanceType class inherits from ParticleType
class ResonanceType : public ParticleType {
  // Data member
  double const width_;

 public:
  //  Constructor
  ResonanceType(std::string name, double mass, int charge, double width)
      : ParticleType(name, mass, charge), width_{width} {}
  // Member functions
  void print() const;
  double getWidth() const;
};

// Operator overload
std::ostream& operator<<(std::ostream& os, ResonanceType const& resonanceType);

#endif
