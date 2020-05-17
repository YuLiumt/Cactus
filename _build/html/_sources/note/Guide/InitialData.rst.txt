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

    "ADMBase" -> "grid";

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

    "StaticConformal" -> "grid";

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

    "seed_magnetic_fields" -> "grid"
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

    "Seed_Magnetic_Fields_BNS" -> "grid"
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
    
