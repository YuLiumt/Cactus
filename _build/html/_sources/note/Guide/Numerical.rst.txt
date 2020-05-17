Numerical
==========
Provides numerical infrastructure thorns.

SpaceMask
----------
The mask is a grid function which can be used to assign a state to each point on the grid. It is used as a bit ﬁeld, with different bits, or combinations of bits, assigned to represent various states.

For instance, a programmer wants to record whether each point of the grid has state "interior", "excised" or "boundary". 2-bits of the mask (enough to represent the three possible states of the type) are allocated to hold this information.  If a new type is required, bits are allocated to it from the remaining free bits in the mask.

.. figure:: ../picture/Spacemask.png

Parameter
^^^^^^^^^^^
* Turn on storage for mask

    >>> SpaceMask::use_mask = "yes"


SphericalSurface
------------------
SphericalSurface defines two-dimensional surfaces with spherical topology. The thorn itself only acts as a repository for other thorns to set and retrieve such surfaces, making it a pure infrastructure thorn. One thorn can update a given spherical surface with information, and another thorn can read that information without having to know about the first thorn.

Parameter
^^^^^^^^^^^
* Number of surfaces

    >>> SphericalSurface::nsurfaces = 2

* Surface Definition: Maximum number of grid points in the theta amd phi direction

    >>> SphericalSurface::maxntheta = 39
    >>> SphericalSurface::maxnphi   = 76

* Surface Definition and set resolution according to given parameters. Some of spherical surface index may be used by PunctureTracker.

    >>> SphericalSurface::name        [0] = "Righthand NS"
    >>> SphericalSurface::ntheta      [0] = 39 # must be at least 3*nghoststheta
    >>> SphericalSurface::nphi        [0] = 76 # must be at least 3*nghostsphi
    >>> SphericalSurface::nghoststheta[0] = 2
    >>> SphericalSurface::nghostsphi  [0] = 2

* Place surface at a certain radius

    >>> SphericalSurface::set_spherical[0] = yes
    >>> SphericalSurface::radius       [0] = 250
