EinsteinBase
===============
EinsteinBase thorns define and register basic variables within numerical relativity.

ADMBase
--------
This thorn provides the basic variables used to communicate between thorns doing General Relativity in the 3+1 formalism.

Parameter
^^^^^^^^^^
* Minkowski values in cartesian coordinates

    >>> ADMBase::initial_data = "Cartesian Minkowski"

TODO: Parameter

Warning
^^^^^^^^
* The variable "ADMBASE::alp" has only 1 active time levels, which is not enough for boundary prolongation of order 1

    >>> ADMBase::lapse_timelevels = 3
    >>> ADMBase::shift_timelevels = 3
    >>> ADMBase::metric_timelevels = 3

StaticConformal
----------------
StaticConformal provides aliased functions to convert between physical and conformal 3-metric values.

The transformation is

.. math::
    g_{ij}^{\mbox{physical}} = \psi^4 g_{ij}^{\mbox{conformal}}

The extrinsic curvature is not transformed.

Parameter
^^^^^^^^^^
* Metric is conformal with static conformal factor, extrinsic curvature is physical

    >>> ADMBase::metric_type = "static conformal"

HydroBase
----------
This thorn should be the interface between all hydro codes and the
spacetime codes.

HydroBase defines the primitive variables

* rho: rest mass density :math:`\rho`
* press: pressure :math:`P`
* eps: internal energy density :math:`\epsilon`
* vel[3]: contravariant fluid three velocity :math:`v^{i}` defined as

.. math::

    v^{i}=\frac{u^{i}}{\alpha u^{0}}+\frac{\beta^{i}}{\alpha}

* Y_e: electron fraction :math:`Y_e`
* temperature: temperature :math:`T`
* entropy: specific entropy per particle :math:`s`
* Bvec[3]: contravariant magnetic field vector defined as

.. math::

    B^{i}=\frac{1}{\sqrt{4 \pi}} n_{\nu} F^{* \nu i}

.. digraph:: foo

    "HydroBase" -> "InitBase";

Parameter
^^^^^^^^^^
* The hydro evolution method

    >>> HydroBase::evolution_method
    

TmunuBase
----------
Provide grid functions for the stress-energy tensor :math:`T_{\mu v}`

.. digraph:: foo

    "TmunuBase" -> "ADMBase";
    "TmunuBase" -> "StaticConformal";
    "TmunuBase" -> "ADMCoupling";

ADMMacros
----------
This thorn provides various macros which can be used to calculate quantities, such as the Christoffel Symbol or Riemann Tensor components, using the basic variables of thorn ADMBase.

ADMCoupling
-------------
This avoids explicit dependencies between the spacetime and matter evolution thorns. 