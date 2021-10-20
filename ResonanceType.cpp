// Implementation of ResonanceType.hpp - Luca Morelli 2021
#include "ResonanceType.hpp"

#include <iostream>

#include "ParticleType.hpp"

// Member functions definitions
void ResonanceType::print() const {
  ParticleType::print();
  std::cout << "ResonanceWidth:" << width_ << '|';
}

double ResonanceType::getWidth() const { return width_; }

// Operator overload definition
std::ostream& operator<<(std::ostream& os, ResonanceType const& resonanceType) {
  resonanceType.print();
  return os;
}
