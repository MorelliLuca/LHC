// Header file ResonanceType.hpp - Luca Morelli 2021
#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include <string>

#include "ParticleType.hpp"

// ResonanceType class inherits from ParticleType
class ResonanceType : public ParticleType {
  // Data member
  double const width_;

 public:
  //  Constructor
  ResonanceType(std::string name, double mass, int charge, double width)
      : ParticleType(name, mass, charge), width_{width} {}
  // Member function
  void print() const;
  double getWidth() const;
};

// Operator overload
std::ostream& operator<<(std::ostream& os, ResonanceType const& resonanceType);

#endif
