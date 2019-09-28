EinsteinAnalysis
===================

ADMAnalysis
--------------
This thorn does basic analysis of the metric and extrinsic curvature tensors.

It calculates

* the trace of the extrinsic curvature (trK)
* the determinant of the metric (detg)
* the components of the metric in spherical coordinates 
  (grr,grq,grp,gqq,gqp,gpp)
* the components of the extrinsic curvature in spherical coordinates (Krr,Krq,Krp,Kqq,Kqp,Kpp)
* components of the Ricci tensor
* the Ricci scalar

.. digraph:: foo

   "ADMAnalysis" -> "ADMMacros";
   "ADMAnalysis" -> "StaticConformal";

Warning
^^^^^^^^^
* Cannot output variable because it has no storage

Output
^^^^^^^
* The Ricci scalar

    >>> IOHDF5::out2D_vars = "ADMAnalysis::ricci_scalar"s

ADMMass
-------
Thorn ADMMass can compute the ADM mass from quantities in ADMBase.

The ADM mass can be deﬁned as a surface integral over a sphere with inﬁnite radius:

.. digraph:: foo

   "ADMMass" -> "ADMMacros";
   "ADMMass" -> "SpaceMask";
   "ADMMass" -> "StaticConformal";

Parameter
^^^^^^^^^^


Warning
^^^^^^^^
* WARNING[L2,P0] (ADMMass): radius < 0 / not set, not calculating the volume integral to get the ADM mass.

    >>> ADMMass::ADMMass_surface_distance[0] = 12

AHFinder
--------
Finding Apparent Horizons in a numerical spacetime. It calulates various quantities like horizon area and its corresponding mass.


