Initial Data
=============
InitBase
----------
Thorn InitBase specifies how initial data are to be set up.

Parameter
^^^^^^^^^^^
* Procedure for setting up initial data ["init_some_levels", "init_single_level", "init_two_levels", "init_all_levels"]:

    >>> InitBase::initial_data_setup_method = "init_all_levels"


ADMBase
--------
This thorn provides the basic variables used to communicate between thorns doing General Relativity in the 3+1 formalism.

* alp
* betax betay betaz
* dtalp
* dtbetax dtbetay dtbetaz
* gxx gyy gzz gxy gxz gyz
* kxx kyy kzz kxy kxz kyz

.. digraph:: foo

    "ADMBase" -> "CartGrid3D";

Parameter
^^^^^^^^^^
* Initial data value

    >>> ADMBase::initial_data    = "Meudon_Bin_NS"
    >>> ADMBase::initial_lapse   = "Meudon_Bin_NS"
    >>> ADMBase::initial_shift   = "zero"
    >>> ADMBase::initial_dtlapse = "Meudon_Bin_NS"
    >>> ADMBase::initial_dtshift = "zero"

* evolution method

    >>> ADMBase::evolution_method         = "ML_BSSN"
    >>> ADMBase::lapse_evolution_method   = "ML_BSSN"
    >>> ADMBase::shift_evolution_method   = "ML_BSSN"
    >>> ADMBase::dtlapse_evolution_method = "ML_BSSN"
    >>> ADMBase::dtshift_evolution_method = "ML_BSSN"

* Number of time levels

    >>> ADMBase::lapse_timelevels  = 3
    >>> ADMBase::shift_timelevels  = 3
    >>> ADMBase::metric_timelevels = 3

Output
^^^^^^^
* ADM

    >>> CarpetIOHDF5::out2D_vars = "ADMBase::curv
    >>>                             ADMBase::lapse
    >>>                             ADMBase::metric
    >>>                             ADMBase::shift"

Warning
^^^^^^^^
* The variable "ADMBASE::alp" has only 1 active time levels, which is not enough for boundary prolongation of order 1

    >>> ADMBase::lapse_timelevels = 3
    >>> ADMBase::shift_timelevels = 3
    >>> ADMBase::metric_timelevels = 3


StaticConformal
----------------
StaticConformal provides aliased functions to convert between physical and conformal 3-metric values.

* psi: Conformal factor

.. digraph:: foo

    "StaticConformal" -> "CartGrid3D";

Parameter
^^^^^^^^^^
* Metric is conformal with static conformal factor, extrinsic curvature is physical

    >>> ADMBase::metric_type = "static conformal"


HydroBase
----------
HydroBase defines the primitive variables

* rho: rest mass density :math:`\rho`
* press: pressure :math:`P`
* eps: internal energy density :math:`\epsilon`
* vel[3]: contravariant fluid three velocity :math:`v^{i}`
* w_lorentz: Lorentz Factor :math:`W`
* Y_e: electron fraction :math:`Y_e`
* Abar: Average atomic mass
* temperature: temperature :math:`T`
* entropy: specific entropy per particle :math:`s`
* Bvec[3]: contravariant magnetic field vector defined as
* Avec[3]: Vector potential
* Aphi: Electric potential for Lorentz Gauge

.. digraph:: foo

    "HydroBase" -> "InitBase";
    "HydroBase" -> "IOUtil";

Parameter
^^^^^^^^^^
* Number of time levels in evolution scheme

    >>> InitBase::initial_data_setup_method = "init_all_levels" 
    >>> HydroBase::timelevels = 3
    rho[i] = 0.0;
    rho_p[i] = 0.0;
    rho_p_p[i] = 0.0;

* The hydro initial value and evolution method (rho, vel, w_lorentz, eps)

    >>> HydroBase::initial_hydro = "zero"
    >>> HydroBase::evolution_method = "none"

* Other initial value and Evolution method

    >>> HydroBase::initial_Avec = "none"
    >>> HydroBase::initial_Aphi = "none"

    >>> HydroBase::initial_Bvec = "none"
    >>> HydroBase::Bvec_evolution_method = "none"

    >>> HydroBase::initial_temperature = "none"
    >>> HydroBase::temperature_evolution_method = "none"

    >>> HydroBase::initial_entropy = "none"
    >>> HydroBase::entropy_evolution_method = "none"

    >>> HydroBase::initial_Abar = "none"
    >>> HydroBase::Abar_evolution_method = "none"

    >>> HydroBase::initial_Y_e = "none"
    >>> HydroBase::Y_e_evolution_method = "none"


TmunuBase
----------
Provide grid functions for the stress-energy tensor

.. math::

    T_{a b} = \left(\begin{array}{llll}eTtt & eTtx & eTty & eTtz \\  & eTxx & eTxy & eTxz \\ & & eTyy & eTyz \\ &&& eTzz \end{array}\right)


.. digraph:: foo

    "TmunuBase" -> "ADMBase";
    "TmunuBase" -> "StaticConformal";
    "TmunuBase" -> "ADMCoupling";

Parameter
^^^^^^^^^^
* Should the stress-energy tensor have storage?

    >>> TmunuBase::stress_energy_storage = yes

* Should the stress-energy tensor be calculated for the RHS evaluation?

    >>> TmunuBase::stress_energy_at_RHS = yes

* Number of time levels

    >>> TmunuBase::timelevels = 3

Meudon_Bin_NS
--------------
Import LORENE Bin_NS binary neutron star initial data.

Parameter
^^^^^^^^^^
* Input file name containing LORENE data

    >>> Meudon_Bin_NS::filename = "resu.d"

* Initial data EOS identifyer

    >>> Meudon_Bin_NS::filename = 
    >>> Meudon_Bin_NS::eos_table = 


Seed_Magnetic_Fields
---------------------
Since the LORENE code cannot yet compute magnetized BNS models.

The following sets up a vector potential of the form

.. math::
    
    A_\phi = \varpi^2 A_b max[(X-X_{cut}), 0],

where :math:`\varpi` is the cylindrical radius: :math:`\sqrt{x^2+y^2}`, and :math:`X \in \{\rho, P\}` is the variable P or :math:`\rho` specifying whether the vector potential is proportional to P or :math:`\rho` in the region greater than the cutoff. 

This formulation assumes that :math:`A_r` and :math:`A_\theta = 0`; only :math:`A_\phi` can be nonzero. Thus the coordinate transformations are as follows:

.. math::

    \begin{aligned}
    A_x &= - \frac{y}{\varpi^2} A_\phi \\
    A_y &= \frac{x}{\varpi^2} A_\phi
    \end{aligned}

.. digraph:: foo

    "seed_magnetic_fields" -> "CartGrid3D"
    "seed_magnetic_fields" -> "ADMBase";
    "seed_magnetic_fields" -> "HydroBase";

Parameter
^^^^^^^^^^
* A-field prescription ["Pressure_prescription", "Density_prescription"]:

    >>> Seed_Magnetic_Fields::Afield_type = "Pressure_prescription"

* Multiply :math:`A_\phi` by :math:`\varpi^2`?

    >>> Seed_Magnetic_Fields::enable_varpi_squared_multiplication = "yes"

* Magnetic field strength parameter.

    >>> Seed_Magnetic_Fields::A_b = 1e-3

* Cutoff pressure, below which vector potential is set to zero. Typically set to 4% of the maximum initial pressure.

    >>> Seed_Magnetic_Fields::P_cut = 1e-5

* Magnetic field strength pressure exponent :math:`A_\phi = \varpi^2 A_b max[(P - P_{cut})^{n_s}, 0]`.

    >>> Seed_Magnetic_Fields::n_s = 1

* Cutoff density, below which vector potential is set to zero. Typically set to 20% of the maximum initial density.

    >>> Seed_Magnetic_Fields::rho_cut = 0.2 # If max density = 1.0

* Define A fields on an IllinoisGRMHD staggered grid?

    >>> Seed_Magnetic_Fields::enable_IllinoisGRMHD_staggered_A_fields = "yes"


Seed_Magnetic_Fields_BNS
-------------------------
Thorn `Seed_Magnetic_Fields` set seeds magnetic fields within a single star. This thorn simply extends the capability to two stars, centered at :math:`(x_{1},0,0)` and :math:`(x_{2},0,0)` (LORENE sets up the neutron stars along the x-axis by default).

.. math::
    
    A_\phi = \varpi^2 A_b max[(P-P_{cut})^{n_s}, 0],

.. digraph:: foo

    "Seed_Magnetic_Fields_BNS" -> "CartGrid3D"
    "Seed_Magnetic_Fields_BNS" -> "ADMBase";
    "Seed_Magnetic_Fields_BNS" -> "HydroBase";

Parameter
^^^^^^^^^^
* Magnetic field strength parameter.

    >>> Seed_Magnetic_Fields_BNS::A_b = 1e-3

* Cutoff pressure, below which vector potential is set to zero. Typically set to 4% of the maximum initial pressure.

    >>> Seed_Magnetic_Fields_BNS::P_cut = 1e-5

* Magnetic field strength pressure exponent.

    >>> Seed_Magnetic_Fields_BNS::n_s = 1

* Define A fields on an IllinoisGRMHD staggered grid?

    >>> Seed_Magnetic_Fields_BNS::enable_IllinoisGRMHD_staggered_A_fields = "no"

* Which field structure to use ["poloidal_A_interior", "dipolar_A_everywhere"]:

    >>> Seed_Magnetic_Fields_BNS::enable_IllinoisGRMHD_staggered_A_fields = "yes" # This requires a staggered grid
    >>> Seed_Magnetic_Fields_BNS::A_field_type = "poloidal_A_interior" # interior to the star
    >>> Seed_Magnetic_Fields_BNS::x_c1 = -15.2 # x coordinate of NS1 center
    >>> Seed_Magnetic_Fields_BNS::x_c2 = 15.2 # x coordinate of NS2 center
    >>> Seed_Magnetic_Fields_BNS::r_NS1 = 13.5 # Radius of NS1. Does not have to be perfect, but must not overlap other star.
    >>> Seed_Magnetic_Fields_BNS::r_NS2 = 13.5 # Radius of NS2

    .. math::

        A_\phi = \varpi^2 A_b max[(P-P_{cut})^{n_s}, 0]

    >>> Seed_Magnetic_Fields_BNS::enable_IllinoisGRMHD_staggered_A_fields = "yes" # This requires a staggered grid
    >>> Seed_Magnetic_Fields_BNS::A_field_type = "dipolar_A_everywhere"
    >>> Seed_Magnetic_Fields_BNS::x_c1 = -15.2 # x coordinate of NS1 center
    >>> Seed_Magnetic_Fields_BNS::x_c2 = 15.2 # x coordinate of NS2 center
    >>> Seed_Magnetic_Fields_BNS::r_NS1 = 13.5 # Radius of NS1. Does not have to be perfect, but must not overlap other star.
    >>> Seed_Magnetic_Fields_BNS::r_NS2 = 13.5 # Radius of NS2
    >>> Seed_Magnetic_Fields_BNS::r_zero_NS1 = 1.0 # Current loop radius
    >>> Seed_Magnetic_Fields_BNS::r_zero_NS2 = 1.0
    >>> Seed_Magnetic_Fields_BNS::I_zero_NS1 = 0.0 # Magnetic field loop current of NS1
    >>> Seed_Magnetic_Fields_BNS::I_zero_NS2 = 0.0

    .. math::
    
        A_{\phi}=\frac{\pi r_{0}^{2} I_{0}}{\left(r_{0}^{2}+r^{2}\right)^{3 / 2}}\left(1+\frac{15 r_{0}^{2}\left(r_{0}^{2}+\varpi^{2}\right)}{8\left(r_{0}^{2}+r^{2}\right)^{2}}\right)
    
TwoPunctures
-------------
Create initial for two puncture black holes using a single domain spectral method.

Following York’s conformal-transverse-traceless decomposition method, we make the following assumptions for the metric and the extrinsic curvature

.. math::

    \begin{aligned} \gamma_{i j} &=\psi^{4} \delta_{i j} \\ K_{i j} &=\psi^{-2}\left(V_{j, i}+V_{i, j}-\frac{2}{3} \delta_{i j} \operatorname{div} \boldsymbol{V}\right) \end{aligned}

The initial data described by this method are conformally flat and maximally sliced, :math:`K = 0`. With this ansatz the Hamiltonian constraint yields an equation for the conformal factor :math:`\psi`

.. math::

    \triangle \psi+\frac{1}{8} \psi^{5} K_{i j} K^{i j}=0

while the momentum constraint yields an equation for the vector potential :math:`\boldsymbol{V}`

.. math::

    \triangle \boldsymbol{V}+\frac{1}{3} \operatorname{grad}(\operatorname{div} \boldsymbol{V})=0

.. note::
    TwoPunctures Thorn is restricted to problems involving two punctures.

One can proceed by choosing a non-trivial analytic solution of the Bowen-York type for the momentum constraint,

.. math::

    \boldsymbol{V}=\sum_{n=1}^{2}\left(-\frac{7}{4\left|\boldsymbol{x}_{n}\right|} \boldsymbol{P}_{n}-\frac{\boldsymbol{x}_{n} \cdot \boldsymbol{P}_{n}}{4\left|\boldsymbol{x}_{n}\right|^{3}} \boldsymbol{x}_{n}+\frac{1}{\left|\boldsymbol{x}_{n}\right|^{3}} \boldsymbol{x}_{n} \times \boldsymbol{S}_{n}\right)

Hamiltonian constraint is obtained by writing the conformal factor :math:`\psi` as a sum of a singular term and a finite correction :math:`u`

.. math::

    \psi=1+\sum_{n=1}^{2} \frac{m_{n}}{2\left|\boldsymbol{x}_{n}\right|}+u

It is impossible to unambiguously define local black hole masses in general. In the following we choose the ADM mass

.. math::

    M_{\pm}^{A D M}=\left(1+u_{\pm}\right) m_{\pm}+\frac{m_{+} m_{-}}{2 D}

Here :math:`m_{+}` and :math:`m_{-}` are the values of :math:`u` at each puncture.

.. digraph:: foo

   "TwoPunctures" -> "ADMBase";
   "TwoPunctures" -> "StaticConformal";

Parameter
^^^^^^^^^^
* initial_data

    >>> ADMBase::initial_data  = "twopunctures"
    >>> ADMBase::initial_lapse = "twopunctures-averaged"
    >>> ADMBase::initial_shift   = "zero"
    >>> ADMBase::initial_dtlapse = "zero"
    >>> ADMBase::initial_dtshift = "zero"

* Coordinate of the puncture

    >>> TwoPunctures::par_b            = 5.0
    >>> TwoPunctures::center_offset[0] = -0.538461538462

* ADM mass of Black holes

    >>> TwoPunctures::target_M_plus  = 0.553846153846
    >>> TwoPunctures::target_M_minus = 0.446153846154
    >>> TwoPunctures::adm_tol = 1.0e-10
    INFO (TwoPunctures): Attempting to find bare masses.
    INFO (TwoPunctures): Target ADM masses: M_p=0.553846 and M_m=0.446154
    INFO (TwoPunctures): ADM mass tolerance: 1e-10
    INFO (TwoPunctures): Bare masses: mp=1, mm=1
    INFO (TwoPunctures): ADM mass error: M_p_err=0.500426421474965, M_m_err=0.607857653302066
    . . .
    INFO (TwoPunctures): Bare masses: mp=0.518419372531011, mm=0.391923877275946
    INFO (TwoPunctures): ADM mass error: M_p_err=2.35933494963092e-12, M_m_err=8.5276896655273e-11
    INFO (TwoPunctures): Found bare masses.
    >>> TwoPunctures::target_M_plus  = 0.553846153846
    >>> TwoPunctures::target_M_minus = 0.446153846154
    >>> TwoPunctures::par_m_plus  = 0.553846153846
    >>> TwoPunctures::par_m_minus = 0.446153846154
    >>> TwoPunctures::adm_tol = 1.0e-10
    INFO (TwoPunctures): Attempting to find bare masses.
    INFO (TwoPunctures): Target ADM masses: M_p=0.553846 and M_m=0.446154
    INFO (TwoPunctures): ADM mass tolerance: 1e-10
    INFO (TwoPunctures): Bare masses: mp=0.553846153846, mm=0.446153846154
    INFO (TwoPunctures): ADM mass error: M_p_err=0.0334459078036595, M_m_err=0.0445419016377125
    . . .
    INFO (TwoPunctures): Bare masses: mp=0.518419372531011, mm=0.391923877275946
    INFO (TwoPunctures): ADM mass error: M_p_err=2.35933494963092e-12, M_m_err=8.5276896655273e-11
    INFO (TwoPunctures): Found bare masses.

* momentum of the puncture

    >>> TwoPunctures::par_P_plus [1] = +0.3331917498
    >>> TwoPunctures::par_P_minus[1] = -0.3331917498

* spin of the puncture

    >>> TwoPunctures::par_S_plus [1] = 0.0
    >>> TwoPunctures::par_S_minus[1] = 0.0

* A small number to smooth out singularities at the puncture locations

    >>> TwoPunctures::TP_epsilon = 1e-6

* Tiny number to avoid nans near or at the pucture locations

    >>> TwoPunctures::TP_Tiny    = 1.0e-2

* Print screen output while solving

    >>> TwoPunctures::verbose = yes
    INFO (TwoPunctures): Bare masses: mp=0.553846153846, mm=0.446153846154
    Newton: it=0 	 |F|=7.738745e-02
    bare mass: mp=0.553846 	 mm=0.446154
    bicgstab:  itmax 100, tol 7.738745e-05
    bicgstab:     0   6.428e-01
    bicgstab:     1   1.010e+00   1.021e+00   0.000e+00   6.116e-01
    bicgstab:     2   7.551e-02   1.622e+00   1.531e-02   4.085e-01
    bicgstab:     3   1.561e-02   2.836e-01   2.396e-02   8.846e-01
    bicgstab:     4   7.358e-03   2.473e-01  -1.079e-01   9.778e-01
    bicgstab:     5   3.429e-04   9.104e+00  -7.954e-01   4.003e-01
    bicgstab:     6   6.564e-05   3.724e-01  -4.164e-01   1.293e+00
    Newton: it=1 	 |F|=1.149396e-03 
    INFO (TwoPunctures): ADM mass error: M_p_err=0.0334459078036595, M_m_err=0.0445419016377125
    >>> TwoPunctures::verbose = no
    INFO (TwoPunctures): Bare masses: mp=0.553846153846, mm=0.446153846154
    INFO (TwoPunctures): ADM mass error: M_p_err=0.0334459078036595, M_m_err=0.0445419016377125



TOVSolver
---------
This thorn provides initial data for TOV star(s) in isotropic coordinates. The Tolman-Oppenheimer-Volkoff solution is a static perfect fluid “star”.

.. digraph:: foo

   "TOVSolver" -> "ADMBase";
   "TOVSolver" -> "HydroBase";
   "TOVSolver" -> "Constants";
   "TOVSolver" -> "StaticConformal";

Parameter
^^^^^^^^^^
* TOV star initial data

    >>> ADMBase::initial_data            = "tov"
    >>> ADMBase::initial_lapse           = "tov"
    >>> ADMBase::initial_shift           = "tov"
    >>> ADMBase::initial_dtlapse         = "zero"
    >>> ADMBase::initial_dtshift         = "zero"

* Set up a TOV star described by a polytropic equation of state :math:`p=K \rho^{\mathrm{T}}`

    >>> TOVSolver::TOV_Rho_Central[0] = 1.28e-3
    >>> TOVSolver::TOV_Gamma          = 2.0
    >>> TOVSolver::TOV_K              = 100.0

    .. figure:: ../picture/TOV_single.png

* Velocity of neutron star

    >>> TOVSolver::TOV_Velocity_x[0]  = 0.1
    >>> TOVSolver::TOV_Velocity_y[0]  = 0.2
    >>> TOVSolver::TOV_Velocity_z[0]  = 0.3

* Two or more of TOVs

    >>> Tovsolver::TOV_Num_TOVs       = 2
    >>> Tovsolver::TOV_Num_Radial     = 200000
    >>> Tovsolver::TOV_Combine_Method = "average"
    >>> Tovsolver::TOV_Rho_Central[0] = 0.16e-3
    >>> Tovsolver::TOV_Position_x[0]  = -15.0
    >>> Tovsolver::TOV_Rho_Central[1] = 0.32e-3
    >>> Tovsolver::TOV_Position_x[1]  = 15.0

    .. figure:: ../picture/TOV_double.png
    
Exact
-----

All of these exact spacetimes have been found useful for testing different aspect of the code.

This thorn sets up the 3+1 ADM variables for any of a number of exact spacetimes/coordinates. Optionally, any 4-metric can be Lorentz-boosted in any direction. As another option, the ADM variables can be calculated on an arbitrary slice through the spacetime, using arbitrary coordinates on the slice.

Parameter
^^^^^^^^^^
* The exact solution/coordinates

* By default, this thorn sets up the ADM variables on an initial slice only. However, setting ADMBase::evolution_method so you get an exact spacetime, not just a single slice.

    >>> ADMBase::evolution_method = "exact"