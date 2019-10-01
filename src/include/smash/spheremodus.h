/*
 *    Copyright (c) 2013-2019
 *      SMASH Team
 *
 *    GNU General Public License (GPLv3 or later)
 */
#ifndef SRC_INCLUDE_SMASH_SPHEREMODUS_H_
#define SRC_INCLUDE_SMASH_SPHEREMODUS_H_

#include <stdint.h>
#include <cmath>
#include <list>
#include <map>

#include "forwarddeclarations.h"
#include "modusdefault.h"

namespace smash {

/**
 * \ingroup modus
 * SphereModus: Provides a modus for expanding matter calculations
 *
 * Matter is put in a sphere of radius R with uniform density;
 * isotropic thermal momenta are typically used for initialization,
 * although other initial momentum states are also included,
 * see \iref{Bazow:2016oky} and \iref{Tindall:2016try}
 *
 * To use this modus, choose
 * \code
 * General:
 *      Modus: Sphere
 * \endcode
 * in the configuration file.
 *
 * Options for SphereModus go in the "Modi"→"Sphere" section of the
 * configuration:
 *
 * \code
 * Modi:
 *      Sphere:
 *              # definitions here
 * \endcode
 *
 * The following configuration options are understood: \ref input_modi_sphere_
 */
class SphereModus : public ModusDefault {
 public:
  /**
   * Constructor
   *
   * Takes all there is to take from the (truncated!) configuration
   * object (only contains configuration for this modus).
   *
   * \param[in] modus_config The configuration object that sets all
   *                         initial conditions of the experiment.
   * \param[in] parameters Unused, but necessary because of templated
   *                       initialization
   */
  explicit SphereModus(Configuration modus_config,
                       const ExperimentParameters &parameters);

  /**
   * Generates initial state of the particles in the system according to
   * specified parameters: number of particles of each species, momentum
   * and coordinate space distributions. Susbsequently makes the total
   * 3-momentum 0.
   *
   * \param[out] particles An empty list that gets filled up by this function
   * \param[in] parameters The initialization parameters of the box
   * \return The starting time of the simulation
   */
  double initial_conditions(Particles *particles,
                            const ExperimentParameters &parameters);

  /**
   * Convenience wrapper for sampling quantum momenta in the Sphere Modus.
   *
   * \param[in] particle_mass (pole) mass of the particle
   * \param[in] pdg_code the PDG code of the particle
   * \param[in] temperature temperature of the system in the box, in GeV
   * \param[in] effective_chemical_potentials a map which allows to calculate
   *                                          effective chemical potential only
   *                                          once per particle species
   * \param[in] distribution_function_maximums a map which allows to calculate
   *                                           distribution function maximum
   * only once per particle species \param[in] initial_multiplicities initial
   * multiplicities of the particles in the box
   */
  double sample_quantum_momenta(
      double particle_mass, PdgCode pdg_code, double temperature,
      std::map<PdgCode, double> *effective_chemical_potentials,
      std::map<PdgCode, double> *distribution_function_maximums,
      const std::map<PdgCode, int> initial_multiplicities);

 private:
  /// Sphere radius (in fm/c)
  double radius_;
  /// Temperature for momentum distribution (in GeV)
  double sphere_temperature_;
  /// Starting time for the Sphere
  const double start_time_ = 0.;
  /**
   *  Whether to use a thermal initialization for all particles
   *  instead of specific numbers
   */
  const bool use_thermal_ = false;
  /**
   *  Baryon chemical potential for thermal initialization;
   *  only used if use_thermal_ is true
   */
  const double mub_;
  /**
   * Strange chemical potential for thermal initialization;
   * only used if use_thermal_ is true
   */
  const double mus_;
  /**
   * In case of thermal initialization: true -- account for resonance
   * spectral functions, while computing multiplicities and sampling masses,
   * false -- simply use pole masses.
   */
  const bool account_for_resonance_widths_;
  /**
   * Particle multiplicities at initialization;
   * required if use_thermal_ is false
   */
  const std::map<PdgCode, int> init_multipl_;
  /**
   * Average multiplicities in case of thermal initialization.
   * Saved to avoid recalculating at every event
   */
  std::map<PdgCode, double> average_multipl_;
  /**
   * Initialization scheme for momenta in the sphere;
   * used for expanding metric setup
   */
  const SphereInitialCondition init_distr_;
  /**
   * Whether to insert a single high energy particle at the center of the
   * expanding sphere (0,0,0). This particle will initially be moving along the
   * x axis, outwards from the sphere.
   */
  const bool insert_jet_ = false;
  /**
   * Pdg of the particle to use as a jet; necessary if insert_jet_ is true,
   * unused otherwise
   */
  const PdgCode jet_pdg_;
  /**
   * Initial momentum of the jet particle; only used if insert_jet_ is true
   */
  const double jet_mom_;
  /**\ingroup logging
   * Writes the initial state for the Sphere to the output stream.
   *
   * \param[in] out The ostream into which to output
   * \param[in] m The SphereModus object to write into out
   */
  friend std::ostream &operator<<(std::ostream &, const SphereModus &);
};
}  // namespace smash
#endif  // SRC_INCLUDE_SMASH_SPHEREMODUS_H_
