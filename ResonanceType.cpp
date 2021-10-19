#include "ResonanceType.hpp"
#include "ParticleType.hpp"

#include <iostream>

void ResonanceType::print() const {
  ParticleType::print();
  std::cout << "ResonanceWidth:" << width_<<'|';
}

double const &ResonanceType::getWidth() const { return width_; }

std::ostream& operator<<(std::ostream& os,ResonanceType const& resonanceType){
  resonanceType.print();
  return os;
}