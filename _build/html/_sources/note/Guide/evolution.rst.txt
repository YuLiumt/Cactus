Evolution
==========

Time
-------
Calculates the timestep used for an evolution by either

* setting the timestep directly from a parameter value
* using a Courant-type condition to set the timestep based on the grid-spacing used.

Parameter
^^^^^^^^^^
* The standard timestep condition dt = dtfac*max(delta_space)

    >>> grid::dxyz = 0.3
    >>> time::dtfac = 0.1
    ----------------------------------
       it  |          | WAVETOY::phi |
           |    t     | norm2        |
    ----------------------------------
         0 |    0.000 |   0.10894195 |
         1 |    0.030 |   0.10892065 |
         2 |    0.060 |   0.10885663 |
         3 |    0.090 |   0.10874996 |

* Absolute value for timestep

    >>> time::timestep_method = "given"
    >>> time::timestep = 0.1
    ----------------------------------
       it  |          | WAVETOY::phi |
           |    t     | norm2        |
    ----------------------------------
         0 |    0.000 |   0.10894195 |
         1 |    0.100 |   0.10870525 |
         2 |    0.200 |   0.10799700 |
         3 |    0.300 |   0.10682694 |
    >>> time::timestep_method = "given"
    >>> time::timestep = 0.2
    ----------------------------------
       it  |          | WAVETOY::phi |
           |    t     | norm2        |
    ----------------------------------
         0 |    0.000 |   0.10894195 |
         1 |    0.200 |   0.10799478 |
         2 |    0.400 |   0.10520355 |
         3 |    0.600 |   0.10072358 |

MoL
-----
The Method of Lines (MoL) converts a (system of) partial differential equation(s) into an ordinary differential equation containing some spatial differential operator. As an example, consider writing the hyperbolic system of PDE’s

.. math::

    \partial_{t} q+A^{i}(q) \partial_{i} B(q)=s(q)

in the alternative form

.. math::

    \partial_{t} q=L(q)

Given this separation of the time and space discretizations, well known stable ODE integrators such as Runge-Kutta can be used to do the time integration.

Parameter
^^^^^^^^^^
* chooses between the diﬀerent methods.

    >>> MoL::ODE_Method = "RK4"
    INFO (MoL): Using Runge-Kutta 4 as the time integrator.

* controls the number of intermediate steps for the ODE solver. For the generic Runge-Kutta solvers it controls the order of accuracy of the method.

    >>> MoL::MoL_Intermediate_Steps = 4

* controls the amount of scratch space used.

    >>> MoL::MoL_Num_Scratch_Levels = 1

Warning
^^^^^^^^^^
* When using the efficient RK4 evolver the number of intermediate steps must be 4, and the number of scratch levels at least 1.

    >>> MoL::MoL_Intermediate_Steps = 4
    >>> MoL::MoL_Num_Scratch_Levels = 1

Dissipation
------------
Add fourth order Kreiss-Oliger dissipation to the right hand side of
evolution equations.

The additional dissipation terms appear as follows

.. math::

    \partial_{t} \boldsymbol{U}=\partial_{t} \boldsymbol{U}+(-1)^{(p+3) / 2} \epsilon \frac{1}{2^{p+1}}\left(h_{x}^{p} \frac{\partial^{(p+1)}}{\partial x^{(p+1)}}+h_{y}^{p} \frac{\partial^{(p+1)}}{\partial y^{(p+1)}}+h_{z}^{p} \frac{\partial^{(p+1)}}{\partial z^{(p+1)}}\right) \boldsymbol{U}

where :math:`h_{x}`, :math:`h_{y}`, and :math:`h_{z}` are the local grid spacings in each Cartesian direction. :math:`\epsilon` is a positive, adjustable parameter controlling the amount of dissipation added, and must be less that 1 for stability.

Parameter
^^^^^^^^^^
* Dissipation order and strength

    >>> Dissipation::order = 5
    >>> Dissipation::epsdis = 0.1

.. note::

    Currently available values of order are :math:`p \in\{1,3,5,7,9\}`. To apply dissipation at order p requires that we have at least :math:`(p + 1) / 2` ghostzones respectively.

* List of evolved grid functions that should have dissipation added

    >>> Dissipation::vars = "ML_BSSN::ML_log_confac
                             ML_BSSN::ML_metric
                             ML_BSSN::ML_trace_curv
                             ML_BSSN::ML_curv
                             ML_BSSN::ML_Gamma
                             ML_BSSN::ML_lapse
                             ML_BSSN::ML_shift
                             ML_BSSN::ML_dtlapse
                             ML_BSSN::ML_dtshift"

ML_BSSN
--------
The code is designed to handle arbitrary shift and lapse conditions. Gauges are the commonly used :math:`1 + log` and :math:`\tilde{\Gamma}`-driver conditions with advection terms.

The hyperbolic K-driver slicing conditions have the form

.. math::

    \left(\partial_{t}-\beta^{i} \partial_{i}\right) \alpha=-f(\alpha) \alpha^{2}\left(K-K_{0}\right)

The hyperbolic Gamma-driver condition have the form

.. math::

    \partial_{t}^{2} \beta^{i}=F \partial_{t} \tilde{\Gamma}^{i}-\eta \partial_{t} \beta^{i}.

where :math:`F` and :math:`\eta` are, in general, positive functions of space and time. We typically choose :math:`F = 3/4`. For some reason, a simple space-varying prescription for :math:`\eta` is implemented

.. math::

    \eta(r):=\frac{2}{M_{T O T}}\left\{\begin{array}{ll}{1} & {\text { for }} {r \leq R} {\text { (near the origin) }} \\ {\frac{R}{r}} & {\text { for }} {r \geq R} {\text { (far away) }}\end{array}\right.

This is a generalization of many well known slicing and shift conditions.

Parameter
^^^^^^^^^^
* Evolution method

    >>> ADMBase::evolution_method         = "ML_BSSN"
    >>> ADMBase::lapse_evolution_method   = "ML_BSSN"
    >>> ADMBase::shift_evolution_method   = "ML_BSSN"
    >>> ADMBase::dtlapse_evolution_method = "ML_BSSN"
    >>> ADMBase::dtshift_evolution_method = "ML_BSSN"

* K-driver slicing conditions: :math:`\frac{d \alpha}{dt} = - f \alpha^{n} K`

    >>> ML_BSSN::harmonicN = 1
    >>> ML_BSSN::harmonicF = 2.0
    [1+log slicing condition]

* Gamma-driver condition: :math:`F`

    >>> ML_BSSN::useSpatialShiftGammaCoeff = 0
    >>> ML_BSSN::ShiftGammaCoeff = <F>

    .. math::
    
        F(r) = F

    >>> ML_BSSN::useSpatialShiftGammaCoeff = 1
    >>> ML_BSSN::ShiftGammaCoeff = <F>
    >>> ML_BSSN::spatialShiftGammaCoeffRadius = 50

    .. math::

        F(r) = Min[1, e^{1 - \frac{r}{R}}] \times F

* Gamma-driver condition: :math:`\eta`

    >>> ML_BSSN::useSpatialBetaDriver = 0
    >>> ML_BSSN::BetaDriver = <eta>

    .. math::

        \eta(r) = \eta

    >>> ML_BSSN::useSpatialBetaDriver = 1
    >>> ML_BSSN::BetaDriver = <eta>
    >>> ML_BSSN::spatialBetaDriverRadius = <R>

    .. math::

        \eta(r) = \frac{R}{Max[r, R]} \times \eta

* Enable spatially varying betaDriver

    >>> ML_BSSN::useSpatialBetaDriver = 1



* Advect Lapse and shift?

    >>> ML_BSSN::advectLapse = 1
    >>> ML_BSSN::advectShift = 1

* Boundary condition for BSSN RHS and some of the ADMBase variables.

    >>> ML_BSSN::rhs_boundary_condition = "scalar"

* Whether to apply dissipation to the RHSs

    >>> ML_BSSN::epsDiss = 0.0
    >>> 
    >>> Dissipation::epsdis = 0.1
    >>> Dissipation::order = 5
    >>> Dissipation::vars = "ML_BSSN::ML_log_confac
    >>>                      ML_BSSN::ML_metric
    >>>                      ML_BSSN::ML_trace_curv
    >>>                      ML_BSSN::ML_curv
    >>>                      ML_BSSN::ML_Gamma
    >>>                      ML_BSSN::ML_lapse
    >>>                      ML_BSSN::ML_shift
    >>>                      ML_BSSN::ML_dtlapse
    >>>                      ML_BSSN::ML_dtshift"

* Enforced minimum of the lapse function

    >>> ML_BSSN::MinimumLapse = 1.0e-8

* Finite differencing order

    >>> ML_BSSN::fdOrder = 4

Warning
^^^^^^^^
* Insufficient ghost or boundary points for ML_BSSN_InitialADMBase2Interior

    >>> ML_BSSN::fdOrder = 8
    >>> driver::ghost_size = 5
    >>> CoordBase::boundary_size_x_lower = 5
    >>> CoordBase::boundary_size_y_lower = 5
    >>> CoordBase::boundary_size_z_lower = 5
    >>> CoordBase::boundary_size_x_upper = 5
    >>> CoordBase::boundary_size_y_upper = 5
    >>> CoordBase::boundary_size_z_upper = 5

* Range error setting parameter 'ML_BSSN::initial_boundary_condition' to 'extrapolate-gammas'

    >>> ActiveThorns = "ML_BSSN_Helper CoordGauge"



ML_BSSN_Helper
---------------


Warning
^^^^^^^^
* The function ExtrapolateGammas has not been provided by any active thorn.

    >>> ActiveThorns = "NewRad"



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
* Determines how much evolution information is output

    >>> IllinoisGRMHD::verbose = "no"

    >>> IllinoisGRMHD::verbose = "essential"

    >>> IllinoisGRMHD::verbose = "essential+iteration output"

* Floor value on the energy variable tau and the baryonic rest mass density

    >>> IllinoisGRMHD::tau_atm 
    >>> IllinoisGRMHD::rho_b_atm

* Hybrid EOS

    >>> IllinoisGRMHD::gamma_th = 2.0
    >>> IllinoisGRMHD::K_poly =

* Chosen Matter and EM field boundary condition

    >>> IllinoisGRMHD::EM_BC = "outflow"
    >>> IllinoisGRMHD::Matter_BC = "copy"
    
    >>> IllinoisGRMHD::EM_BC = "frozen"
    >>> IllinoisGRMHD::Matter_BC = "frozen" #If Matter_BC or EM_BC is set to FROZEN, BOTH must be set to frozen!

* Debug. If the primitives solver fails, this will output all data needed to debug where and why the solver failed.

    >>> IllinoisGRMHD::conserv_to_prims_debug = 1


ID_conerter_ILGRMHD
-----------------------------------------
IllinoisGRMHD and HydroBase variables are incompatible. The former uses 3-velocity defined as :math:`v^i = u^i/u^0`, and the latter uses the Valencia formalism definition of :math:`v^i` as measured by normal observers, defined as:

.. math::

    v_{(n)}^{i}=\frac{u^{i}}{\alpha u^{0}}+\frac{\beta^{i}}{\alpha}

In addition, IllinoisGRMHD needs the A-fields to be defined on *staggered* grids, and HydroBase does not yet support this option.

.. figure:: ../picture/staggeredGird.png

.. digraph:: foo

    "ID_converter_ILGRMHD" -> "ADMBase";
    "ID_converter_ILGRMHD" -> "Boundary";
    "ID_converter_ILGRMHD" -> "SpaceMask";
    "ID_converter_ILGRMHD" -> "Tmunubase";
    "ID_converter_ILGRMHD" -> "HydroBase";
    "ID_converter_ILGRMHD" -> "CartGrid3D";
    "ID_converter_ILGRMHD" -> "IllinoisGRMHD";

Parameter
^^^^^^^^^^
* Single Gamma-law EOS:

    >>> ID_converter_ILGRMHD::Gamma_Initial = 2.0
    >>> ID_converter_ILGRMHD::K_Initial     = 123.64110496340211

convert_to_HydroBase
---------------------
Convert IllinoisGRMHD-compatible variables to HydroBase-compatible variables. Used for compatibility with HydroBase/ADMBase analysis thorns in the Einstein Toolkit. 

Parameter
^^^^^^^^^^
* How often to convert IllinoisGRMHD primitive variables to HydroBase primitive variables? This needed for particle tracer.

    >>> convert_to_HydroBase::convert_to_HydroBase_every = 0

.. digraph:: foo

    "convert_to_HydroBase" -> "CartGrid3D";
    "convert_to_HydroBase" -> "HydroBase";
    "convert_to_HydroBase" -> "ADMBase";
    "convert_to_HydroBase" -> "IllinoisGRMHD";
