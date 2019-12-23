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

    >>> IOHDF5::out2D_vars = "ADMAnalysis::ricci_scalar"

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

Hydro_Analysis
---------------
This thorn provides basic hydro analysis routines.

Parameter
^^^^^^^^^^
* Look for the value and location of the maximum of rho

    >>> Hydro_Analysis::Hydro_Analysis_comp_rho_max = "true"
    >>> Hydro_Analysis::Hydro_Analysis_average_multiple_maxima_locations = "yes"


* Look for the proper distance between the maximum of the density and the origin (along a straight coordinate line)

    >>> Hydro_Analysis::Hydro_Analysis_comp_rho_max_origin_distance = "yes"

* Name of the interpolator

    >>> Hydro_Analysis::Hydro_Analysis_interpolator_name = "Lagrange polynomial interpolation (tensor product)"

Output
^^^^^^^
* Coordinate location of the maximum of rho

    >>> IOScalar::outScalar_vars = "Hydro_Analysis::Hydro_Analysis_rho_max_loc"

* proper distance between the maximum of the density and the origin (along a straight coordinate line)

    >>> IOScalar::outScalar_vars = "Hydro_Analysis::Hydro_Analysis_rho_max_origin_distance"

Warning
^^^^^^^^
* Cannot get handle for interpolation ! Forgot to activate an implementation providing interpolation operators (e.g. LocalInterp)?

    >>> ActiveThorns = "LocalInterp"

* No driver thorn activated to provide an interpolation routine for grid arrays

    >>> ActiveThorns = "CarpetInterp"

* No handle found for interpolation operator 'Lagrange polynomial interpolation (tensor product)'

    >>> ActiveThorns = "AEILocalInterp"

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

PunctureTracker
-----------------
PunctureTracker track BH positions evolved with moving puncture techniques. The BH position is stored as the centroid of a spherical surface (even though there is no surface) provided by SphericalSurface.

.. digraph:: foo

   "PunctureTracker" -> "SphericalSurface";

Parameter
^^^^^^^^^^
* A spherical surface index where we can store the puncture location

    >>> PunctureTracker::which_surface_to_store_info[0] = 0
    >>> PunctureTracker::track                      [0] = yes
    >>> PunctureTracker::initial_x                  [0] = 
    >>> PunctureTracker::which_surface_to_store_info[1] = 1
    >>> PunctureTracker::track                      [1] = yes
    >>> PunctureTracker::initial_x                  [1] = 

Warning
^^^^^^^^
* No handle found for interpolation operator 'Lagrange polynomial interpolation'

    >>> ActiveThorns = "AEILocalInterp"

* Error

    >>> ActiveThorns = "SphericalSurface"
    >>> SphericalSurface::nsurfaces = 2
    >>> SphericalSurface::maxntheta = 66
    >>> SphericalSurface::maxnphi   = 124
    >>> SphericalSurface::verbose   = yes

Output
^^^^^^^
* Location of punctures

    >>> IOASCII::out0D_vars = "PunctureTracker::pt_loc"

NSTracker
----------
This thorn can track the location of a neutron star, e.g. to
guide mesh refinement.

Parameter
^^^^^^^^^^^
* A spherical surface index where we can store the puncture location

    >>> NSTracker::NSTracker_SF_Name          = "Righthand NS"
    >>> NSTracker::NSTracker_SF_Name_Opposite = "Lefthand NS"
    >>> NSTracker::NSTracker_max_distance = 3
    >>> NSTracker::NSTracker_verbose = "yes"
    >>> NSTracker::NSTracker_tracked_location = "Hydro_Analysis::Hydro_Analysis_rho_max_loc"

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