CactusNumerical
=================
Provides numerical infrastructure thorns for time integration, artificial dissipation, symmetry boundary conditions, setting up spherical surfaces, interpolation, Method of Lines (MoL) implementation.

ReflectionSymmetry
-------------------
Provide reflection symmetries, i.e., bitant, quadrant, and octant mode.

Parameter
^^^^^^^^^^
* Reflection symmetry at the lower z boundary

    >>> CoordBase::xmin       = -10.0
    >>> CoordBase::ymin       = -10.0
    >>> CoordBase::zmin       =  0.00
    >>> CoordBase::xmax       = +10.0
    >>> CoordBase::ymax       = +10.0
    >>> CoordBase::zmax       = +10.0
    >>> CoordBase::dx         =     1
    >>> CoordBase::dy         =     1
    >>> CoordBase::dz         =     1
    >>> ReflectionSymmetry::reflection_z = "yes"
    >>> ReflectionSymmetry::avoid_origin_z = "no"
    >>> CoordBase::boundary_size_x_lower = 3
    >>> CoordBase::boundary_size_y_lower = 3
    >>> CoordBase::boundary_size_z_lower = 3
    >>> CoordBase::boundary_size_x_upper = 3
    >>> CoordBase::boundary_size_y_upper = 3
    >>> CoordBase::boundary_size_z_upper = 3
    >>> CoordBase::boundary_shiftout_x_lower = 1
    >>> CoordBase::boundary_shiftout_y_lower = 1
    >>> CoordBase::boundary_shiftout_z_lower = 1
    INFO (SymBase): Symmetry on lower z-face: reflection_symmetry

    .. figure:: ./picture/reflection_z.png

Warning
^^^^^^^^^^
* The lower z face is a symmetry boundary.  The symmetry condition and the corresponding CoordBase boundary must either be both staggered or both not staggered.

# TODO:

* The lower z face is a symmetry boundary.  If the symmetry condition is staggered, then the corresponding CoordBase shiftout must be 0; otherwise it must be 1.

    >>> CoordBase::boundary_shiftout_z_lower = 1




SummationByParts
-----------------
Warning
^^^^^^^^
* You need ghostsize >= 4 to run with 8 order finite differences

    >>> SummationByParts::order = 4


Slab
-------
A slab is a sub-array of another array. The Slab thorn provides a routine to copy a slab from one array into a slab of another array. This can be used to change the processor distribution of some data, or to apply symmetry or periodicity boundary conditions, or to collect data onto a single processor to process it more easily.