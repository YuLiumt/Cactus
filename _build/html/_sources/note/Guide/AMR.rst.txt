Adaptive Mesh Refinement
=========================
It is often the case in simulations of physical systems that the most interesting phenomena may occur in only a subset of the computational domain. In the other regions of the domain it may be possible to use a less accurate approximation, thereby reducing the computational resources required, and still obtain results which are essentially similar to those obtained if no such reduction is made.

In particular, we may consider using a computational mesh which is non-uniform in space and time, using a finer mesh resolution in the “interesting” regions where we expect it to be necessary, and using a coarser resolution in other areas. This is what we mean by mesh refinement (MR).

Carpet
-------
Carpet is a mesh refinement driver for Cactus. It knows about a hierarchy of refinement levels, where each level is decomposed into a set of cuboid grid patches. The grid patch is the smallest unit of grid points that Carpet deals with. Carpet parallelises by assigning sets of grid patches to processors.

Each grid patch can be divided in up to four zones: the interior, the outer boundary, and the ghost zone, and the refinement boundary. The interior is where the actual compuations go on. The outer boundary is where the users’ outer boundary condition is applied; from Carpet’s point of view, these two are the same. The ghost zones are boundaries to other grid patches on the same refinement level (that might live on a different processor). The refinement boundary is the boundary of the refined region in a level, and it is filled by prolongation (interpolation) from the next coarser level.

.. note::

    Carpet does not handle staggered grids. Carpet does not provide cell-centered refinement. Carpet always enables all storage.

.. digraph:: foo

   "Carpet" -> "CarpetLib";
   "Carpet" -> "IOUtil";
   "Carpet" -> "MPI";
   "Carpet" -> "Timers";
   "Carpet" -> "LoopControl";

Parameter
^^^^^^^^^^
* Use the domain description from CoordBase to specify the global extent of the coarsest grid.

    >>> Carpet::domain_from_coordbase = yes

* Use the domain description from MultiPatch

    >>> Carpet::domain_from_multipatch = yes

* Maximum number of refinement levels, including the base level

    >>> Carpet::max_refinement_levels = 1

* Ghost zones in each spatial direction

    .. note::

        Grid patches that are on the same refinement level never overlap except with their ghost zones. Conversly, all ghost zones must overlap with a non-ghost zone of another grid patch of the same level.

    >>> Carpet::ghost_size = 3
    INFO (Carpet): Base grid specification for map 0:
        number of coarse grid ghost points: [[3,3,3],[3,3,3]]

* Fill past time levels from current time level after calling initial data routines.

    .. note::
    
        The boundary values of the finer grids have to be calculated from the coarser grids through interpolation. An because the time steps on the finer grids are smaller, there is not always a corresponding value on the coarser grids available. This makes it necessary to interpolate in time between time steps on the coarser grids. three time levels allow for a second order interpolation in time.

    >>> Carpet::init_fill_timelevels = "yes"
    >>> Carpet::init_3_timelevels = "no" # Set up 3 timelevels of initial data

* Carpet currently supports polynomial interpolation, up to quadratic interpolation in time, which requires keeping at least two previous time levels of data. It also supports up to quintic interpolation in space, which requires using at least three ghost zones.

    >>> Carpet::prolongation_order_space = 5
    >>> Carpet::prolongation_order_time  = 2

* Refinement factor

    >>> Carpet::refinement_factor = 2

* Temporal refinement factors over the coarsest level

    >>> grid::dxyz = 18
    >>> time::dtfac = 0.25
    >>> Carpet::max_refinement_levels    = 7
    >>> Carpet::time_refinement_factors  = "[1,1,2,4,8,16,32]"
    INFO (Time): Timestep set to 4.5 (courant_static)
    INFO (Time): Timestep set to 4.5 (courant_static)
    INFO (Time): Timestep set to 2.25 (courant_static)
    INFO (Time): Timestep set to 1.125 (courant_static)
    INFO (Time): Timestep set to 0.5625 (courant_static)
    INFO (Time): Timestep set to 0.28125 (courant_static)
    INFO (Time): Timestep set to 0.140625 (courant_static)

* Use buffer zones

    >>> Carpet::use_buffer_zones = "yes"
    INFO (Carpet): Buffer zone counts (excluding ghosts):
        [0]: [[0,0,0],[0,0,0]]
        [1]: [[9,9,9],[9,9,9]]
        [2]: [[9,9,9],[9,9,9]]
        [3]: [[9,9,9],[9,9,9]]
        [4]: [[9,9,9],[9,9,9]]
        [5]: [[9,9,9],[9,9,9]]
        [6]: [[9,9,9],[9,9,9]]

* Carpet uses vertex-centered refinement. That is, each coarse grid point coincides with a fine grid point.

    >>> Carpet::refinement_centering = "vertex"

* Print detailed statistics periodically

    >>> Carpet::output_timers_every = 512
    >>> Carpet::schedule_barriers = "yes" # Insert barriers between scheduled items, so that timer statistics become more reliable (slows down execution)
    >>> Carpet::sync_barriers = "yes" # Insert barriers before and after syncs, so that the sync timer is more reliable (slows down execution)

* Try to catch uninitialised grid elements or changed timelevels.

    .. note::

        Checksumming and poisoning are means to find thorns that alter grid variables that should not be altered, or that fail to fill in grid variables that they should fill in.

    >>> Carpet::check_for_poison = "no"
    >>> Carpet::poison_new_timelevels = "yes"
    >>> CarpetLib::poison_new_memory = "yes"
    >>> CarpetLib::poison_value      = 114

* Base Multigrid level and factor

    >>> Carpet::convergence_level = 0
    >>> Carpet::convergence_factor = 2
    INFO (Carpet): Adapted domain specification for map 0:
        convergence factor: 2
        convergence level : 0

Output
^^^^^^^
* File name to output grid coordinates.

    >>> Carpet::grid_coordinates_filename = "carpet-grid.asc"

Warning
^^^^^^^^
* INFO (Carpet): There are not enough time levels for the desired temporal prolongation order in the grid function group "ADMBASE::METRIC".  With Carpet::prolongation_order_time=2, you need at least 3 time levels.


CarpetLib
-----------
This thorn contains the backend library that provides mesh refinement. CarpetLib contains of three major parts: 

* a set of generic useful helpers

    A class ``vect<T,D>`` provides small D-dimensional vectors of the type T. A vect corresponds to a grid point location. The class ``bbox<T,D>`` provides D-dimensional bounding boxes using type T as indices. A bbox defines the location and shape of a grid patch. Finally, ``bboxset<T,D>`` is a collection of bboxes.

* the grid hierarchy and data handling

    The grid hierarchy is described by a set of classes. Except for the actual data, all structures and all information is replicated on all processors.

* interpolation operators.

    The interpolators used for restriction and prolongation are different from those used for the generic interpolation interface in Cactus. The reason is that interpolation is expensive, and hence the interpolation operators used for restriction and prolongation have to be streamlined and optimised. As one knows the location of the sampling points for the interpolation, one can calculate the coefficients in advance, saving much time compared to calling a generic interpolation interface.

.. digraph:: foo

   "CarpetLib" -> "Vectors";
   "CarpetLib" -> "CycleClock";
   "CarpetLib" -> "Timers";
   "CarpetLib" -> "LoopControl";

Parameter
^^^^^^^^^^
* Provide one extra ghost point during restriction for staggered operators.

    >>> CarpetLib::support_staggered_operators = "yes"

CarpetRegrid2
--------------
Set up refined regions by specifying a set of centres and radii about them. All it does is take a regridding specification from the user and translate that into a ``gh``.


* ``gh`` is a grid hierarchy. It describes, for each refinement level, the location of the grid patches. This ``gh`` does not contain ghost zones or prolongation boundaries. There exists only one common ``gh`` for all grid functions.
* ``dh`` is a data hierarchy. It extends the notion of a ``gh`` by ghost zones and prolongation boundaries. The ``dh`` does most of the bookkeeping work, deciding which grid patches interact with what other grid patches through synchronisation, prolongation, restriction, and boundary prolongation. As all grid functions have the same number of ghost zones, there exists also only one ``dh`` for all grid functions.



.. note::

    To regrid means to select a new set of grid patches for each refinement level. To recompose the grid hierarchy means to move data around. Regridding is only about bookkeeping, while recomposing is about data munging.

.. digraph:: foo

   "CarpetRegrid2" -> "Carpet";
   "CarpetRegrid2" -> "Timers";

Parameter
^^^^^^^^^^
* Set up refined regions by specifying a set of centres and radii about them.

    >>> Carpet::max_refinement_levels = 7
    >>> CarpetRegrid2::num_centres    = 2
    >>> CarpetRegrid2::num_levels_1   = 7
    >>> CarpetRegrid2::num_levels_2   = 7
    >>> CarpetRegrid2::position_x_1   = -15.2
    >>> CarpetRegrid2::position_x_2   =  15.2
    >>> 
    >>> CarpetRegrid2::radius_1[1]    =  270.0
    >>> CarpetRegrid2::radius_1[2]    =  162.0
    >>> CarpetRegrid2::radius_1[3]    =   94.5
    >>> CarpetRegrid2::radius_1[4]    =   40.5
    >>> CarpetRegrid2::radius_1[5]    =   27.0
    >>> CarpetRegrid2::radius_1[6]    =   13.5
    >>> 
    >>> CarpetRegrid2::radius_2[1]    =  270.0
    >>> CarpetRegrid2::radius_2[2]    =  162.0
    >>> CarpetRegrid2::radius_2[3]    =   94.5
    >>> CarpetRegrid2::radius_2[4]    =   40.5
    >>> CarpetRegrid2::radius_2[5]    =   27.0
    >>> CarpetRegrid2::radius_2[6]    =   13.5
    >>> 
    >>> Carpet::refinement_factor = 2
    INFO (CarpetRegrid2): Centre 1 is at position [-15.2,0,0] with 7 levels
    INFO (CarpetRegrid2): Centre 2 is at position [15.2,0,0] with 7 levels
    INFO (Carpet): Grid structure (superregions, coordinates):
        [0][0][0]   exterior: [-576.000000000000000,-576.000000000000000,-576.000000000000000] : [576.000000000000000,576.000000000000000,576.000000000000000] : [18.000000000000000,18.000000000000000,18.000000000000000]
        [1][0][0]   exterior: [-369.000000000000000,-351.000000000000000,-351.000000000000000] : [369.000000000000000,351.000000000000000,351.000000000000000] : [9.000000000000000,9.000000000000000,9.000000000000000]
        [2][0][0]   exterior: [-216.000000000000000,-202.500000000000000,-202.500000000000000] : [216.000000000000000,202.500000000000000,202.500000000000000] : [4.500000000000000,4.500000000000000,4.500000000000000]
        [3][0][0]   exterior: [-130.500000000000000,-114.750000000000000,-114.750000000000000] : [130.500000000000000,114.750000000000000,114.750000000000000] : [2.250000000000000,2.250000000000000,2.250000000000000]
        [4][0][0]   exterior: [-66.375000000000000,-50.625000000000000,-50.625000000000000] : [66.375000000000000,50.625000000000000,50.625000000000000] : [1.125000000000000,1.125000000000000,1.125000000000000]
        [5][0][0]   exterior: [-47.250000000000000,-32.062500000000000,-32.062500000000000] : [47.250000000000000,32.062500000000000,32.062500000000000] : [0.562500000000000,0.562500000000000,0.562500000000000]
        [6][0][0]   exterior: [-31.218750000000000,-16.031250000000000,-16.031250000000000] : [31.218750000000000,16.031250000000000,16.031250000000000] : [0.281250000000000,0.281250000000000,0.281250000000000]

* Regrid every n time steps

    >>> CarpetRegrid2::regrid_every = 32 # 2**(max_refinement_levels - 2)

* Minimum movement to trigger a regridding

    >>> CarpetRegrid2::movement_threshold_1 = 0.10 # Regrid only if the regions have changed sufficiently
    INFO (CarpetRegrid2): Refined regions have not changed sufficiently; skipping regridding

Warning
^^^^^^^^
* PARAMETER ERROR (CarpetRegrid2): The number of requested refinement levels is larger than the maximum number of levels specified by Carpet::max_refinement_levels

    >>> Carpet::max_refinement_levels = <number>

VolumeIntegrals_GRMHD
----------------------
Thorn for integration of spacetime quantities. The center of mass (CoM) can be used to set the AMR center.

.. math::

    \rho_{*} = \alpha u^{0} \sqrt{det(g)} \rho_{0} = \Gamma \sqrt{det(g)} \rho_{0} \\
    CoM^{i} = \frac{\int \rho_{*} x^{i} dV}{\int \rho_{*} dV}

.. note::

    In a binary neutron star simulation, the maximum density is :math:`\sim 1`, with atmosphere values surrounding the stars of at most :math:`\sim` 1e-6. The concern is that a bad conservatives-to-primitives inversion called before this diagnostic might cause Gamma to be extremely large. Capping Gamma at 1e4 should prevent the CoM integral from being thrown off significantly, which would throw off the NS tracking.

.. digraph:: foo

    "VolumeIntegrals_GRMHD" -> "CartGrid3D";
    "VolumeIntegrals_GRMHD" -> "HydroBase";
    "VolumeIntegrals_GRMHD" -> "ADMBase";
    "VolumeIntegrals_GRMHD" -> "CarpetRegrid2";

Parameter
^^^^^^^^^^
* Set verbosity level: 1=useful info; 2=moderately annoying (though useful for debugging)

    >>> VolumeIntegrals_GRMHD::verbose = 1

* How often to compute volume integrals?

    >>> VolumeIntegrals_GRMHD::VolIntegral_out_every = 32 # 2**(max_refinement_levels - 2)

* Number of volume integrals to perform

    >>> VolumeIntegrals_GRMHD::NumIntegrals = 6
    >>> 
    >>> # Integrate the entire volume with an integrand of 1. (used for testing/validation purposes only).
    >>> VolumeIntegrals_GRMHD::Integration_quantity_keyword[1] = "one"
    >>> 
    >>> # To compute the center of mass in an integration volume originally centered at (x,y,z) = (-15.2,0,0) with a coordinate radius of 13.5. Also use the center of mass integral result to set the ZEROTH AMR center.
    >>> VolumeIntegrals_GRMHD::Integration_quantity_keyword[2] = "centerofmass"
    >>> VolumeIntegrals_GRMHD::volintegral_sphere__center_x_initial         [2] = -15.2
    >>> VolumeIntegrals_GRMHD::volintegral_inside_sphere__radius            [2] =  13.5
    >>> VolumeIntegrals_GRMHD::amr_centre__tracks__volintegral_inside_sphere[2] =  0
    >>> 
    >>> # Same as above, except use the integrand=1 (for validation purposes, to ensure the integration volume is approximately 4/3*pi*13.5^3).
    >>> VolumeIntegrals_GRMHD::Integration_quantity_keyword[3] = "one"
    >>> VolumeIntegrals_GRMHD::volintegral_sphere__center_x_initial         [3] = -15.2
    >>> VolumeIntegrals_GRMHD::volintegral_inside_sphere__radius            [3] =  13.5
    >>> 
    >>> # The neutron star originally centered at (x,y,z) = (+15.2,0,0). Also use the center of mass integral result to set the ONETH AMR center.
    >>> VolumeIntegrals_GRMHD::Integration_quantity_keyword[4] = "centerofmass"
    >>> VolumeIntegrals_GRMHD::volintegral_sphere__center_x_initial         [4] =  15.2
    >>> VolumeIntegrals_GRMHD::volintegral_inside_sphere__radius            [4] =  13.5
    >>> VolumeIntegrals_GRMHD::amr_centre__tracks__volintegral_inside_sphere[4] =  1
    >>>
    >>> # Same as above, except use the integrand=1 (for validation purposes, to ensure the integration volume is approximately 4/3*pi*13.5^3).
    >>> VolumeIntegrals_GRMHD::Integration_quantity_keyword[5] = "one"
    >>> VolumeIntegrals_GRMHD::volintegral_sphere__center_x_initial         [5] =  15.2
    >>> VolumeIntegrals_GRMHD::volintegral_inside_sphere__radius            [5] =  13.5
    >>>
    >>> # Perform rest-mass integrals over entire volume.
    >>> VolumeIntegrals_GRMHD::Integration_quantity_keyword[6] = "restmass"

* Enable output file

    >>> VolumeIntegrals_GRMHD::enable_file_output = 1
    >>> VolumeIntegrals_GRMHD::outVolIntegral_dir = "volume_integration"

* Gamma speed limit

    >>> VolumeIntegrals_GRMHD::CoM_integrand_GAMMA_SPEED_LIMIT = 1e4

CarpetTracker
--------------
Object coordinates are updated by CarpetTracker, which provides a simple interface to the object trackers PunctureTracker and NSTracker in order to have the refined region follow the moving objects.

.. digraph:: foo

   "CarpetTracker" -> "SphericalSurface";
   "CarpetTracker" -> "CarpetRegrid2";

Parameter
^^^^^^^^^^
* Spherical surface index or name which is the source for the location of the refine regions. (Maximum number of tracked surfaces less than 10)

    >>> CarpetTracker::surface[0] = 0
    <surface index>
    >>> CarpetTracker::surface_name[0] = "Righthand NS"
    <surface name>

NSTracker
----------
This thorn can track the location of a neutron star, e.g. to
guide mesh refinement.

.. digraph:: foo

   "NSTracker" -> "SphericalSurface";
   "NSTracker" -> "Hydro_Analysis";

Parameter
^^^^^^^^^^^
* Index or Name of the sperical surface which should be moved around

    >>> NSTracker::NSTracker_SF_Name          = "Righthand NS"
    >>> NSTracker::NSTracker_SF_Name_Opposite = "Lefthand NS"
    <surface name>
    >>> NSTracker::NSTracker_SF_Index          = 0
    >>> NSTracker::NSTracker_SF_Index_Opposite = 1
    <surface index>

* Allowed to move if new location is not too far from old.

    >>> NSTracker::NSTracker_max_distance = 3

* grid scalar group containing coordinates of center of star

    >>> NSTracker::NSTracker_tracked_location = "Hydro_Analysis::Hydro_Analysis_rho_max_loc" # location of maximum
    position_x[NSTracker_SF_Index] = Hydro_Analysis_rho_max_loc
    position_x[NSTracker_SF_Index_Opposite] = - Hydro_Analysis_rho_max_loc
    >>> NSTracker::NSTracker_tracked_location = "Hydro_Analysis::Hydro_Analysis_rho_core_center_volume_weighted" # center of mass

* Time after which to stop updating the SF

    >>> NSTracker::NSTracker_stop_time = -1

Hydro_Analysis
---------------
This thorn provides basic hydro analysis routines.

.. digraph:: foo

   "Hydro_Analysis" -> "HydroBase";
   "Hydro_Analysis" -> "ADMBase";
   "Hydro_Analysis" -> "CartGrid3D";

Parameter
^^^^^^^^^^
* Look for the value and location of the maximum of rho

    >>> Hydro_Analysis::Hydro_Analysis_comp_rho_max = "true"
    >>> Hydro_Analysis::Hydro_Analysis_average_multiple_maxima_locations = "yes" # when finding more than one global maximum location, average position
    >>> Hydro_Analysis::Hydro_Analysis_comp_rho_max_every = 32 # 2**(max_refinement_levels - 2)

* Look for the location of the volume-weighted center of mass

    >>> Hydro_Analysis::Hydro_Analysis_comp_vol_weighted_center_of_mass = "yes"

* Look for the proper distance between the maximum of the density and the origin (along a straight coordinate line, not a geodesic)

    >>> Hydro_Analysis::Hydro_Analysis_comp_rho_max_origin_distance = "yes"
    >>> ActiveThorns = "AEILocalInterp"
    >>> Hydro_Analysis::Hydro_Analysis_interpolator_name = "Lagrange polynomial interpolation (tensor product)"

Output
^^^^^^^
* Coordinate location of the maximum of rho

    >>> IOScalar::outScalar_vars = "Hydro_Analysis_rho_max"
    >>> IOScalar::outScalar_vars = "Hydro_Analysis::Hydro_Analysis_rho_max_loc"

* coordinate location of the volume weightes center of mass

    >>> IOScalar::outScalar_vars = "Hydro_Analysis_rho_center_volume_weighted"

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

* No handle: '-2' found for reduction operator 'sum'

    >>> ActiveThorns = "LocalReduce"

PunctureTracker
-----------------
PunctureTracker track BH positions evolved with moving puncture techniques. The BH position is stored as the centroid of a spherical surface (even though there is no surface) provided by SphericalSurface.

.. math::

    pt\_loc = pt\_loc\_p - dt \times pt\_beta

.. digraph:: foo

   "PunctureTracker" -> "SphericalSurface";
   "PunctureTracker" -> "CarpetRegrid2";
   "PunctureTracker" -> "ADMBase";

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


CarpetInterp/CarpetInterp2
---------------------------
This thorn provides a parallel interpolator for Carpet.

.. digraph:: foo

   "CarpetInterp2" -> "Carpet";
   "CarpetInterp2" -> "Timers";

CarpetReduce
-------------
This thorn provides parallel reduction operators for Carpet. This thorn now uses a weight function. The weight is 1 for all "normal" grid points.

.. note::

    The weight is set to 0 on symmetry and possible the outer boundary, and it might be set to :math:`1/2` on the edge of the boundary. The weight is also reduced or set to 0 on coarser grids that are overlaid by finer grid.

.. digraph:: foo

   "CarpetReduce" -> "Carpet";
   "CarpetReduce" -> "LoopControl";

CarpetMask
-----------
Remove unwanted regions from Carpet's reduction operations. This can be used to excise the interior of horizons.

.. digraph:: foo

   "CarpetMask" -> "CartGrid3D";
   "CarpetMask" -> "SphericalSurface";

Parameter
^^^^^^^^^^
* Exclude spherical surfaces with shrink factor

    .. note::

        iweight = 0 if dr <= radius_{sf} * excluded_surface_factor

    >>> CarpetMask::excluded_surface[0] = 0 # index of excluded surface
    >>> CarpetMask::excluded_surface_factor[0] = 1


