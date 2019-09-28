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

    .. figure:: ./picture/reflection_z.png

Warning
^^^^^^^^^^
* The lower z face is a symmetry boundary.  The symmetry condition and the corresponding CoordBase boundary must either be both staggered or both not staggered.

# TODO:

* The lower z face is a symmetry boundary.  If the symmetry condition is staggered, then the corresponding CoordBase shiftout must be 0; otherwise it must be 1.

    >>> CoordBase::boundary_shiftout_z_lower = 1

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

* controls the number of intermediate steps for the ODE solver. For the generic Runge-Kutta solvers it controls the order of accuracy of the method.

    >>> MoL::MoL_Intermediate_Steps = 4

* controls the amount of scratch space used.

    >>> MoL::MoL_Num_Scratch_Levels = 1

Warning
^^^^^^^^^^
* When using the efficient RK4 evolver the number of intermediate steps must be 4, and the number of scratch levels at least 1.

    >>> MoL::MoL_Intermediate_Steps = 4
    >>> MoL::MoL_Num_Scratch_Levels = 1


Slab
-------
Slab can be used to apply symmetry or periodicity boundary conditions, or to collect data onto a single processor to process it more easily.


SphericalSurface
------------------
Many thorns work on manifolds that are two-dimensional, closed surfaces. Examples are apparent and event horizons, or the surfaces on which gravitational waves are extracted. There is a need to have a common representation for such surfaces, so that the surface-finding thorns and the thorns working with these surfaces can be independent. A common representation will also facilitate visualisation. This thorn SphericalSurface provides just such a common representation.

This thorn provides storage for several independent surfaces, identified by an index. It is up to the user to specify, probably in the parameter ﬁle, which thorns use what surfaces for what purpose.

TODO: Parameter
