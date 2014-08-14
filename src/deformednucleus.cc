/*
 *    Copyright (c) 2014
 *      SMASH Team
 *
 *    GNU General Public License (GPLv3 or later)
 */
#include "include/deformednucleus.h"

#include "include/angles.h"
#include "include/configuration.h"
#include "include/constants.h"
#include "include/fourvector.h"
#include "include/particledata.h"
#include "include/random.h"
#include "include/threevector.h"

#include <cmath>
#include <stdexcept>

namespace Smash {

DeformedNucleus::DeformedNucleus() {}

double DeformedNucleus::deformed_woods_saxon(double r, double cosx) const {
  // Return the deformed woods-saxon calculation
  // at the given location for the current system.
  return Nucleus::get_saturation_density() / (1 + std::exp(r - Nucleus::get_nuclear_radius() *
         (1 + beta2_ * y_l_0(2, cosx) + beta4_ * y_l_0(4, cosx)) / Nucleus::get_diffusiveness()));
}

ThreeVector DeformedNucleus::distribute_nucleon() const {
  double a_radius;
  Angles a_direction;
  // Set a sensible max bound for radial sampling.
  double radius_max = Nucleus::get_nuclear_radius() / Nucleus::get_diffusiveness() +
                      Nucleus::get_nuclear_radius() * Nucleus::get_diffusiveness();

  // Sample the distribution.
  do {
    a_direction.distribute_isotropically();
    a_radius = Random::uniform(0.0, radius_max);

  } while (Random::canonical() > deformed_woods_saxon(a_radius,
           a_direction.costheta()));

  // Update (x, y, z).
  return a_direction.threevec() * a_radius;
}

void DeformedNucleus::set_parameters_automatic() {
  // Initialize the inherited attributes.
  Nucleus::set_parameters_automatic();

  // Set the deformation parameters.
  switch (Nucleus::number_of_particles()) {
    case 238:  // Uranium
      // Moeller et. al. - Default.
      set_beta_2(0.215);
      set_beta_4(0.093);
      // Kuhlman, Heinz - Correction.
      // set_beta_2(0.28);
      // set_beta_4(0.093);
      break;
    case 208:  // Lead
      set_beta_2(0.0);
      set_beta_4(0.0);
      break;
    case 197:  // Gold
      set_beta_2(-0.131);
      set_beta_4(-0.031);
      break;
    case 63:  // Copper
      set_beta_2(0.162);
      set_beta_4(-0.006);
      break;
    default:
      throw std::domain_error("Mass number not listed in DeformedNucleus::set_parameters_automatic.");
  }

  // Set a random nuclear rotation.
  nuclear_orientation_.distribute_isotropically();
}

void DeformedNucleus::set_parameters_from_config(bool is_projectile, Configuration &config) {
  // Inherited nucleus parameters.
  Nucleus::set_parameters_from_config(is_projectile, config);
  const char * nucleus_type = is_projectile ? "Projectile" : "Target";

  // Deformation parameters.
  if (config.has_value({nucleus_type, "BETA_2"})) {
    set_beta_2(static_cast<double>(config.take({nucleus_type, "BETA_2"})));
  }
  if (config.has_value({nucleus_type, "BETA_4"})) {
    set_beta_4(static_cast<double>(config.take({nucleus_type, "BETA_4"})));
  }

  // Saturation density (normalization for accept/reject sampling)
  if (config.has_value({nucleus_type, "SATURATION_DENSITY"})) {
    Nucleus::set_saturation_density(static_cast<double>(config.take({nucleus_type, "SATURATION_DENSITY"})));
  }

  // Polar angle
  if (config.has_value({nucleus_type, "THETA"})) {
    set_polar_angle(static_cast<double>(config.take({nucleus_type, "THETA"})));
  }
  // Azimuth
  if (config.has_value({nucleus_type, "PHI"})) {
    set_azimuthal_angle(static_cast<double>(config.take({nucleus_type, "PHI"})));
  }
}

void DeformedNucleus::rotate() {
  for (auto i = begin(); i != end(); i++) {
    // Rotate every vector by the nuclear azimuth phi and polar angle
    // theta (the Euler angles). This means applying the matrix for a
    // rotation of phi about z, followed by the matrix for a rotation
    // theta about the rotated x axis. The third angle psi is 0 by symmetry.
    ThreeVector three_pos = i->position().threevec();
    three_pos.rotate(nuclear_orientation_.phi(), nuclear_orientation_.theta(), 0.0);
    i->set_3position(three_pos);
  }
}

double DeformedNucleus::y_l_0(int l, double cosx) const {
  if (l == 2) {
    return (1./4) * std::sqrt(5/M_PI) * (3. * (cosx * cosx) - 1);
  } else if (l == 4) {
    return (3./16) * std::sqrt(1/M_PI) * (35. * (cosx * cosx) * (cosx * cosx) - 30. * (cosx * cosx) + 3);
  } else {
    throw std::domain_error("Not a valid angular momentum quantum number in DeformedNucleus::y_l_0.");
  }
}

} // namespace Smash
