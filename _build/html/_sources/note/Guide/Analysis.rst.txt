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

smallbPoynET
-------------
Using HydroBase velocity and magnetic field variables, as well as ADMBase spacetime metric variables, smallbPoynET computes :math:`b^i`, and three spatial components of Poynting flux. It also computes :math:`-1 - u_{0}`, which is useful for tracking unbound matter.

.. digraph:: foo

    "smallbPoynET" -> "CartGrid3D";
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

* :math:`b^i`

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

    "particle_tracerET" -> "CartGrid3D";
    "particle_tracerET" -> "HydroBase";
    "particle_tracerET" -> "ADMBase";

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

QuasiLocalMeasures
-------------------
Calculate quasi-local measures such as masses, momenta, or angular
momenta and related quantities on closed two-dimentional surfaces,
including on horizons.

Parameter
^^^^^^^^^^
* Input a surface that the user specifies and can calculate useful quantities

    >>> QuasiLocalMeasures::num_surfaces   = 1
    >>> QuasiLocalMeasures::spatial_order  = 4
    >>> QuasiLocalMeasures::interpolator = "Lagrange polynomial interpolation"
    >>> QuasiLocalMeasures::interpolator_options = "order=4"
    >>> QuasiLocalMeasures::surface_name[0] = "waveextract surface at 100"

Output
^^^^^^^^
* Scalar quantities on the surface

    >>> IOASCII::out0D_vars  = "QuasiLocalMeasures::qlm_scalars"




AHFinderDirect
---------------
In 3+1 numerical relativity, it's often useful to know the positions and shapes of any black holes in each slice. 

Finding Apparent Horizons in a numerical spacetime. It calulates various quantities like horizon area and its corresponding mass.

.. note::

    The main complication here is that AHFinderDirect needs an initial guess for an AH shape, and if this initial guess is inaccurate AHFinderDirect may fail to find the AH.

Parameter
^^^^^^^^^^^
* How often should we try to find apparent horizons?

    >>> AHFinderDirect::find_every = 128 # every course

* Number of apparent horizons to search for

    >>> AHFinderDirect::N_horizons = 2

* Move the origins with the horizons

    >>> AHFinderDirect::move_origins = yes

* Which surface should we store the info?

    >>> AHFinderDirect::origin_x [1] =
    >>> AHFinderDirect::initial_guess__coord_sphere__x_center[1] = 
    >>> AHFinderDirect::initial_guess__coord_sphere__radius [1] =
    >>> AHFinderDirect::which_surface_to_store_info [1] = 2
    >>> AHFinderDirect::track_origin_source_x        [1] = "PunctureTracker::pt_loc_x[0]"
    >>> AHFinderDirect::track_origin_source_y        [1] = "PunctureTracker::pt_loc_y[0]"
    >>> AHFinderDirect::track_origin_source_z        [1] = "PunctureTracker::pt_loc_z[0]"
    >>> AHFinderDirect::max_allowable_horizon_radius [1] = 3

Multipole
----------
Multipole thorn can decompose multiple grid functions with any spin-weight on multiple spheres. A set of radii for these spheres, as well as the number of angular points to use, can be speciﬁed.

The angular dependence of a field :math:`u(t, r, \theta, \varphi)` can be expanded in spin-weight s spherical harmonics

.. math::

    u(t, r, \theta, \varphi)=\sum_{l=0}^{\infty} \sum_{m=-l}^{l} C^{l m}(t, r)_{s} Y_{l m}(\theta, \varphi)

where the coefficients :math:`C^{l m}(t, r)` are given by

.. digraph:: foo

   "Multipole" -> "AEILocalInterp";

Parameter
^^^^^^^^^^
* Decide the number and radii of the coordinate spheres on which you want to decompose.

    >>> Multipole::nradii    = 3  
    >>> Multipole::radius[0] = 10  
    >>> Multipole::radius[1] = 20  
    >>> Multipole::radius[2] = 30  
    >>> Multipole::variables = "MyThorn::u"

* How many points in the theta and phi direction?

    >>> Multipole::ntheta = 120
    >>> Multipole::nphi   = 240

* The maximum l mode to extract

    >>> Multipole::l_max = 8

* Output an HDF5 file for each variable containing one dataset per mode at each radius

    >>> Multipole::output_hdf5  = yes

WeylScal4
----------
Calculate the Weyl Scalars for a given metric given the fiducial tetrad.

Parameter
^^^^^^^^^^
* Finite differencing order

    >>> WeylScal4::fdOrder = 8

* Which scalars to calculate

    >>> WeylScal4::calc_scalars = "psis"

* Compute invariants

    >>> WeylScal4::calc_invariants = "always"