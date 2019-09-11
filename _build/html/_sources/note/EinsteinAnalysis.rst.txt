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



ADMMass
-------
Thorn ADMMass can compute the ADM mass from quantities in ADMBase.

