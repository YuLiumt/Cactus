WVUThorns
==========

illinoisGRMHD
--------------
IllinoisGRMHD solves the equations of General Relativistic MagnetoHydroDynamics (GRMHD) using a high-resolution shock capturing scheme and the Piecewise Parabolic Method (PPM) for reconstruction.

IllinoisGRMHD evolves the vector potential :math:`A_{\mu}` (on staggered grids) instead of the magnetic fields (:math:`B^i`) directly, to guarantee that the magnetic fields will remain divergenceless even at AMR boundaries. 

IllinoisGRMHD currently implements a hybrid EOS of the form

.. math::

    P\left(\rho_{0}, \epsilon\right)=P_{\text {cold }}\left(\rho_{0}\right)+\left(\Gamma_{\text {th }}-1\right) \rho_{0}\left[\epsilon-\epsilon_{\text {cold }}\left(\rho_{0}\right)\right]

where :math:`P_{\text {cold}}` and :math:`\epsilon_{\text {cold}}` denote the cold component of :math:`P` amd :math:`\epsilon` respectively, and :math:`\Gamma_{\text {th}}` is a constant parameter which determines the conversion efficiency of kinetic to thermal energy at shocks. The function :math:`\epsilon_{\text {cold }}(\rho_{0})` is related to :math:`P_{\text {cold }}\left(\rho_{0}\right)` by the first law of thermodynamics,

.. math::

    \epsilon_{\mathrm{cold}}\left(\rho_{0}\right)=\int \frac{P_{\mathrm{cold}}\left(\rho_{0}\right)}{\rho_{0}^{2}} d \rho_{0}

The :math:`\Gamma`-law EOS :math:`P=(\Gamma-1) \rho_{0} \epsilon` is adopted. This corresponds to setting :math:`P_{\text {cold }}=(\Gamma-1) \rho_{0} \epsilon_{\text {cold }}`, which is equivalent to :math:`P_{\text {cold }}=\kappa \rho_{0}^{\Gamma}` (with constant :math:`\kappa`), and :math:`\Gamma_{\mathrm{th}}=\Gamma`. In the absence of shocks and in the initial data :math:`\epsilon=\epsilon_{\mathrm{cold}}` and  :math:`P=P_{\mathrm{cold}}`

.. digraph:: foo

    "IllinoisGRMHD" -> "ADMBase";
    "IllinoisGRMHD" -> "Boundary";
    "IllinoisGRMHD" -> "SpaceMask";
    "IllinoisGRMHD" -> "Tmunubase";
    "IllinoisGRMHD" -> "HydroBase";

Parameter
^^^^^^^^^^
* Floor value

    >>> IllinoisGRMHD::tau_atm 
    >>> IllinoisGRMHD::rho_b_atm

* Hybrid EOS

    >>> IllinoisGRMHD::gamma_th = 2.0
    >>> IllinoisGRMHD::K_poly =

Seed_Magnetic_Fields
---------------------
This formulation assumes that :math:`A_r` and :math:`A_\theta = 0`; only :math:`A_\phi` can be nonzero. The following sets up a vector potential of the form

.. math::
    
    A_\phi = \varpi^2 A_b max[(EE-EE_{cut}),0],

where :math:`\varpi` is the cylindrical radius: :math:`\sqrt{x^2+y^2}`,and :math:`EE \in \{\rho, P\}` is the variable P or :math:`\rho` specifying whether the vector potential is proportional to P or :math:`\rho` in the region greater than the cutoff.

.. digraph:: foo

    "seed_magnetic_fields" -> "ADMBase";
    "seed_magnetic_fields" -> "HydroBase";

Parameter
^^^^^^^^^^
* A-field prescription

    >>> Seed_Magnetic_Fields::Afield_type = "Pressure_prescription"

* Multiply A_phi by varpi^2?

    >>> Seed_Magnetic_Fields::enable_varpi_squared_multiplication = yes

* Magnetic field strength parameter.

    >>> Seed_Magnetic_Fields::A_b = 1e-3

* Cutoff pressure, below which vector potential is set to zero. Typically set to 4% of the maximum initial pressure.

    >>> Seed_Magnetic_Fields::P_cut

* Cutoff density, below which vector potential is set to zero. Typically set to 20% of the maximum initial density.

    >>> Seed_Magnetic_Fields::rho_cut

ID_conerter_ILGRMHD/convert_to_HydroBase
-----------------------------------------
IllinoisGRMHD and HydroBase variables are incompatible. The former uses 3-velocity defined as :math:`v^i = u^i/u^0`, and the latter uses the Valencia formalism definition of :math:`v^i`. Then

.. math::

    W^i = \frac{v^i + \beta^i}{\alpha}

In addition, IllinoisGRMHD needs the A-fields to be defined on *staggered* grids, and HydroBase does not yet support this option.

.. figure:: ./picture/staggeredGird.png

.. digraph:: foo

    "ID_converter_ILGRMHD" -> "IllinoisGRMHD";
    "convert_to_HydroBase" -> "IllinoisGRMHD";
    "IllinoisGRMHD" -> "ADMBase";
    "IllinoisGRMHD" -> "Boundary";
    "IllinoisGRMHD" -> "SpaceMask";
    "IllinoisGRMHD" -> "Tmunubase";
    "IllinoisGRMHD" -> "HydroBase";

