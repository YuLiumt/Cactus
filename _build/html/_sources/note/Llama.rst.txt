Llama
======

.. figure:: ./picture/Llama.png

An interior Cartesian grid, and six outer patches.

Coordinates
------------


.. digraph:: foo

   "Coordinates" -> "CartGrid3D";
   "Coordinates" -> "Carpet";

Parameter
^^^^^^^^^^
* Inner radius for the spherical grids.

    >>> Coordinates::sphere_inner_radius     = 1.8

* Location of the physical outer boundary.
    
    >>> Coordinates::sphere_outer_radius     = 20.0

Coordinates::coordinate_system       = "Thornburg04nc"
Coordinates::h_radial                = 0.1
Coordinates::n_angular               = 20
Coordinates::outer_boundary_size     = 1
Coordinates::patch_boundary_size     = 2
Coordinates::additional_overlap_size = 2

CoordinatesSymmetry
--------------------

Parameter
^^^^^^^^^^
* Reflection symmetry at the lower z boundary

    >>> CoordinatesSymmetry::reflection_z = "yes"