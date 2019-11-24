McLachlan
===========

McLachlan is a state-of-the-art BSSN code for solving the Einstein equations.

Gauges are the commonly used :math:`1 + log` and :math:`\tilde{\Gamma}`-driver conditions with advection terms.

ML_BSSN
--------
The code is designed to handle arbitrary shift and lapse conditions.

The hyperbolic K-driver slicing conditions have the form

.. math::

    \left(\partial_{t}-\beta^{i} \partial_{i}\right) \alpha=-f(\alpha) \alpha^{2}\left(K-K_{0}\right)

The hyperbolic Gamma-driver condition have the form

.. math::

    \partial_{t}^{2} \beta^{i}=F \partial_{t} \tilde{\Gamma}^{i}-\eta \partial_{t} \beta^{i}.

where :math:`F` and :math:`\eta` are, in general, positive functions of space and time. For the hyperbolic Gamma-driver conditions it is crucial to add a dissipation term with coefficient :math:`\eta` to avoid strong oscillations in the shift. We typically choose $F = 3/4$ and $\eta =3$ and do not vary them in time.

This is a generalization of many well known slicing and shift conditions.

Parameter
^^^^^^^^^^
* Evolution method

    >>> ADMBase::evolution_method         = "ML_BSSN"
    >>> ADMBase::lapse_evolution_method   = "ML_BSSN"
    >>> ADMBase::shift_evolution_method   = "ML_BSSN"
    >>> ADMBase::dtlapse_evolution_method = "ML_BSSN"
    >>> ADMBase::dtshift_evolution_method = "ML_BSSN"

* :math:`\frac{d \alpha}{dt} = - f \alpha^{n} K`

    >>> ML_BSSN::harmonicN = 1
    >>> ML_BSSN::harmonicF = 2.0

* :math:`\frac{d \beta^{i}}{dt} = C Xt^{i}`

    >>> ML_BSSN::ShiftGammaCoeff = 0.75

* :math:`\frac{d \beta^{i}}{dt} = ... - betaDriver \alpha^{shiftAlphaPower} \beta^{i}`

    >>> ML_BSSN::BetaDriver = 1.0
    >>> ML_BSSN::shiftAlphaPower = 0.0

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

ML_ADMConstraints
------------------
ML_ADMConstraints calculates the ADM constraints violation, but directly using potentially higher-order derivatives, and is, in general, preferred over ADMConstraints.

.. digraph:: foo

   "ML_ADMConstraints" -> "GenericFD";
   "ML_ADMConstraints" -> "TmunuBase";
   "TmunuBase" -> "ADMCoupling";
   "TmunuBase" -> "ADMMacros";
   
Output
^^^^^^^
* Hamiltonian constraint

    >>> IOHDF5::out2D_vars = "ML_ADMConstraints::ML_Ham"

* Momentum constraints

    >>> IOHDF5::out2D_vars = "ML_ADMConstraints::ML_mom"