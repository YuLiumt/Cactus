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

TmunuBase
----------
Provide grid functions for the stress-energy tensor 

.. math::
    T_{\mu v}

ADMMacros
----------
This thorn provides various macros which can be used to calculate quantities, such as the Christoffel Symbol or Riemann Tensor components, using the basic variables of thorn ADMBase.

ADMCoupling
-------------
This avoids explicit dependencies between the spacetime and matter evolution thorns. 