Grid
======

CoordBase
------------
The CoordBase thorn provides a method of registering coordinate systems and their properties.

CoordBase provides a way for specifying the extent of the simulation domain that is independent of the actual coordinate and symmetry thorns. This is necessary because the size of the physical domain is not necessarily the same as the size of the computational grid, which is usually enlarged by symmetry zones and/or boundary zones.

.. note::

    The black hole "source” region has a length scale of :math:`G M / c^{2}`, where G is Newton’s constant, M is the total mass of the two black holes, and c is the speed of light. The gravitational waves produced by the source have a length scale up to :math:`\sim 100 G M / c^{2}`. The source region requires grid zones of size :math:`\lesssim 0.01 G M / c^{2}` to accurately capture the details of the black holes’ interaction, while the extent of the grid needs to be several hundred :math:`G M / c^{2}` to accurately capture the details of the gravitational wave signal.

Parameter
^^^^^^^^^^
* Specifying the extent of the physical domain.

    >>> CoordBase::domainsize = "minmax" # lower and upper boundary locations
    >>> CoordBase::xmin = -540.00
    >>> CoordBase::ymin = -540.00
    >>> CoordBase::zmin = -540.00
    >>> CoordBase::xmax =  540.00
    >>> CoordBase::ymax =  540.00
    >>> CoordBase::zmax =  540.00
    >>> CoordBase::spacing = "gridspacing" # grid spacing
    >>> CoordBase::dx   = 1
    >>> CoordBase::dx   = 18.0
    >>> CoordBase::dy   = 18.0
    >>> CoordBase::dz   = 18.0
    INFO (Carpet): CoordBase domain specification for map 0:
        physical extent: [-540,-540,-540] : [540,540,540]   ([1080,1080,1080])
        base_spacing   : [18,18,18]

* Boundary description.

    >>> CoordBase::boundary_size_x_lower = 3
    >>> CoordBase::boundary_size_y_lower = 3
    >>> CoordBase::boundary_size_z_lower = 3
    >>> CoordBase::boundary_size_x_upper = 3
    >>> CoordBase::boundary_size_y_upper = 3
    >>> CoordBase::boundary_size_z_upper = 3
    >>> CoordBase::boundary_internal_x_lower = "no"
    >>> CoordBase::boundary_internal_y_lower = "no"
    >>> CoordBase::boundary_internal_z_lower = "no"
    >>> CoordBase::boundary_internal_x_upper = "no"
    >>> CoordBase::boundary_internal_y_upper = "no"
    >>> CoordBase::boundary_internal_z_upper = "no"
    >>> CoordBase::boundary_staggered_x_lower = "no"
    >>> CoordBase::boundary_staggered_y_lower = "no"
    >>> CoordBase::boundary_staggered_z_lower = "no"
    >>> CoordBase::boundary_staggered_x_upper = "no"
    >>> CoordBase::boundary_staggered_y_upper = "no"
    >>> CoordBase::boundary_staggered_z_upper = "no"
    >>> CoordBase::boundary_shiftout_x_lower = 0
    >>> CoordBase::boundary_shiftout_y_lower = 0
    >>> CoordBase::boundary_shiftout_z_lower = 0
    >>> CoordBase::boundary_shiftout_x_upper = 0
    >>> CoordBase::boundary_shiftout_y_upper = 0
    >>> CoordBase::boundary_shiftout_z_upper = 0
    INFO (Carpet): Boundary specification for map 0:
        nboundaryzones: [[3,3,3],[3,3,3]]
        is_internal   : [[0,0,0],[0,0,0]]
        is_staggered  : [[0,0,0],[0,0,0]]
        shiftout      : [[0,0,0],[0,0,0]]
    INFO (Carpet): CoordBase domain specification for map 0:
        interior extent: [-522,-522,-522] : [522,522,522]   ([1044,1044,1044])
        exterior extent: [-576,-576,-576] : [576,576,576]   ([1152,1152,1152])


Warning
^^^^^^^
* The boundary must be contained in the active part of the domain boundaries <= domain_active

    >>> CoordBase::xmin = -200.0
    >>> CoordBase::xmax = +200.0

CartGrid3D
-------------
CartGrid3D allows you to set up coordinates on a 3D Cartesian grid in a flexible manner.

.. digraph:: foo

   "CartGrid3D" -> "Coordinate";

Parameter
^^^^^^^^^^
* Get specification from CoordBase

    >>> CartGrid3D::type = "coordbase"

* Get specification from MultiPatch

    >>> CartGrid3D::type = "multipatch"
    >>> CartGrid3D::set_coordinate_ranges_on = "all maps"

Output
^^^^^^^
* 3D Cartesian grid coordinates

    >>> CarpetIOHDF5::out2D_vars = "grid::coordinates"

SymBase
----------
Thorn SymBase provides a mechanism by which symmetry conditions can register routines that handle this mapping when a global interpolator is called.