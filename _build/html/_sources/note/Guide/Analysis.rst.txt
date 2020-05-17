Analysis
=========

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

(q refers to the theta coordinate and p to the phi coordinate.)

.. digraph:: foo

   "ADMAnalysis" -> "ADMBase";
   "ADMAnalysis" -> "StaticConformal";
   "ADMAnalysis" -> "Grid";
   "ADMAnalysis" -> "ADMMacros";

Parameter
^^^^^^^^^^
* Project angular components onto :math:`r*dtheta` and :math:`r*sin(theta)*dphi`

    >>> ADMAnalysis::normalize_dtheta_dphi = "yes"

Warning
^^^^^^^^^
* Cannot output variable because it has no storage

Output
^^^^^^^
* The Ricci scalar

    >>> IOHDF5::out2D_vars = "ADMAnalysis::ricci_scalar"


ADMMass
-------
Thorn ADMMass can compute the ADM mass from quantities in ADMBase.

.. note::

    ADMMass uses the ADMMacros for derivatives. Thus, converegence of results is limited to the order of these derivatives (ADMMacros::spatial_order).

.. digraph:: foo

   "ADMMass" -> "ADMBase";
   "ADMMass" -> "ADMMacros";
   "ADMMass" -> "StaticConformal";
   "ADMMass" -> "SpaceMask";

Parameter
^^^^^^^^^^
* Number of measurements

    >>> ADMMass::ADMMass_number = 1

.. note::

    Multiple measurements can be done for both volume and surface integral, but the limit for both is 100 (change param.ccl if you need more).

* ADMMass provides several possibilities to specify the (ﬁnite) integration domain for surface integral

    >>> ADMMass::ADMMass_surface_distance[0] = 12

* ADMMass provides several possibilities to specify the (ﬁnite) integration domain for volume integral

    >>> ADMMass::ADMMass_use_all_volume_as_volume_radius = "yes"
    Use the whole grid for volume integration
    >>> ADMMass::ADMMass_use_surface_distance_as_volume_radius = "yes"
    ADMMass_surface_distance is used to specify the integration radius.
    >>> ADMMass::ADMMass_volume_radius[0] =12
    ADMMass_volume_radius speciﬁes this radius.

* Should we exclude the region inside the AH to the volume integral?

    >>> ADMMass::ADMMass_Excise_Horizons = "yes"

Warning
^^^^^^^^
* WARNING[L2,P0] (ADMMass): radius < 0 / not set, not calculating the volume integral to get the ADM mass.

    >>> ADMMass::ADMMass_surface_distance[0] = 12

Output
^^^^^^^
* The results for the volume integral, the usual surface integral and the sorface integral including the lapse

    >>> IOASCII::out0D_vars  = "ADMMass::ADMMass_Masses"

VolumeIntegrals_GRMHD
----------------------
Thorn for integration of spacetime quantities.

.. digraph:: foo

    "VolumeIntegrals_GRMHD" -> "grid";
    "VolumeIntegrals_GRMHD" -> "HydroBase";
    "VolumeIntegrals_GRMHD" -> "ADMBase";
    "VolumeIntegrals_GRMHD" -> "CarpetRegrid2";

smallbPoynET
-------------
Using HydroBase velocity and magnetic field variables, as well as ADMBase spacetime metric variables, smallbPoynET computes :matb:`b^i`, and three spatial components of Poynting flux. It also computes :math:`-1 - u_{0}`, which is useful for tracking unbound matter.

.. digraph:: foo

    "smallbPoynET" -> "grid";
    "smallbPoynET" -> "HydroBase";
    "smallbPoynET" -> "ADMBase";

Parameter
^^^^^^^^^^
* How often to compute smallbPoyn?

    >>> smallbPoynET::smallbPoynET_compute_every = 0

Output
^^^^^^^^
* Poynting flux

    >>> 

* :matb:`b^i`

    >>> CarpetIOHDF5::out2D_vars = "smallbPoynET::smallb2
                                     smallbPoynET::smallbx
                                     smallbPoynET::smallby
                                     smallbPoynET::smallbz"
                             
* 

    >>> CarpetIOHDF5::out2D_vars = "smallbPoynET::minus_one_minus_u_0"
                                     
particle_tracerET
------------------
This thorn provides essential functionality for self-consistent visualizations of the dynamics of magnetic field lines over time in a GRMHD simulation.

.. digraph:: foo

    "particle_tracerET" -> "grid";
    "particle_tracerET" -> "HydroBase";
    "particle_tracerET" -> "ADMBase";
