Adaptive Mesh Refinement
=========================
Carpet is a mesh refinement driver for Cactus. It knows about a hierarchy of refinement levels, where each level is decomposed into a set of cuboid grid patches. The grid patch is the smallest unit of grid points that Carpet deals with. Carpet parallelises by assigning sets of grid patches to processors.

Carpet uses vertex-centered refinement. That is, each coarse grid point coincides with a fine grid point. To regrid means to select a new set of grid patches for each refinement level. To recompose the grid hierarchy means to move data around. Regridding is only about bookkeeping, while recomposing is about data munging.

Each grid patch can be divided in up to four zones: the interior, the outer boundary, and the ghost zone, and the refinement boundary. The interior is where the actual compuations go on. The outer boundary is where the users’ outer boundary condition is applied; from Carpet’s point of view, these two are the same. The ghost zones are boundaries to other grid patches on the same refinement level (that might live on a different processor). The refinement boundary is the boundary of the refined region in a level, and it is filled by prolongation (interpolation) from the next coarser level.

Grid patches that are on the same refinement level never overlap except with their ghost zones. Conversly, all ghost zones must overlap with a non-ghost zone of another grid patch of the same level.

Carpet
-------
This thorn provides a parallel AMR (adaptive mesh refinement) driver with MPI.

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

* Each coarse grid point coincides with a fine grid point.

    >>> Carpet::refinement_centering = "vertex"

* Print detailed statistics periodically

    >>> Carpet::output_timers_every = 512
    >>> Carpet::schedule_barriers = "yes" # Insert barriers between scheduled items, so that timer statistics become more reliable (slows down execution)
    >>> Carpet::sync_barriers = "yes" # Insert barriers before and after syncs, so that the sync timer is more reliable (slows down execution)

* Explicitely check for the poison value after every time step

    >>> Carpet::check_for_poison = "no"

* Enable storage for all grid functions

    >>> Carpet::enable_all_storage = "no"

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
This thorn contains the backend library that provides mesh refinement.

.. digraph:: foo

   "CarpetLib" -> "Vectors";
   "CarpetLib" -> "CycleClock";
   "CarpetLib" -> "Timers";

Parameter
^^^^^^^^^^
* Provide one extra ghost point during restriction for staggered operators

    >>> CarpetLib::support_staggered_operators = "yes"

CarpetRegrid2
--------------
Set up refined regions by specifying a set of centres and radii about them.

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

    "VolumeIntegrals_GRMHD" -> "grid";
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

CarpetMask
-----------
Remove unwanted regions from Carpet's reduction operations.  This can
be used e.g. to excise the interior of horizons.

.. digraph:: foo

   "CarpetMask" -> "grid";
   "CarpetMask" -> "SphericalSurface";

Parameter
^^^^^^^^^^
* Exclude spherical surfaces

    >>> CarpetMask::excluded_surface[0]        = 0 # index of excluded surface
    >>> CarpetMask::excluded_surface_factor[0] = 1

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