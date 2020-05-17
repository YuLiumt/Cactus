Include
========

cctk.h
-------

Any source file using Cactus infrastructure should include the header file cctk.h using the line

.. code-block:: c

    #include "cctk.h"

cctk_Arguments.h
-----------------
Any routine using Cactus argument lists should include at the top of the file the header

.. code-block:: c

    #include "cctk_Arguments.h"

A Cactus macro CCTK\_ARGUMENTS is defined for each thorn to contain:

* General information about the grid hierarchy.
* All the grid variables defined in the thorn’s *interface.ccl*.

These variables must be declared at the start of the routine using the macro ``DECLARE_CCTK_ARGUMENTS``.

.. c:var:: cGH

    :param cctkGH: A C pointer identifying the grid hierarchy.
    :param cctk\_dim: An integer with the number of dimensions used for this grid hierarchy.
    :param cctk\_lsh: An array of cctk\_dim integers with the local grid size on this processor.
    :param cctk\_ash: An array of cctk\_dim integers with the allocated size of the array. 
    :param cctk\_gsh: An array of cctk\_dim integers with the global grid size.
    :param cctk\_iteration: The current iteration number.
    :param cctk\_delta\_time: A CCTK\_REAL with the timestep.
    :param cctk\_time: A CCTK\_REAL with the current time.
    :param cctk\_delta\_space: An array of cctk\_dim CCTK\_REALs with the grid spacing in each direction.
    :param cctk\_nghostzones: An array of cctk\_dim integers with the number of ghostzones used in each direction.
    :param cctk\_origin\_space: An array of cctk\_dim CCTK\_REALs with the spatial coordinates of the global origin of the grid.
    :param cctk\_lbnd: An array of cctk_dim integers containing the lowest index (in each direction) of the local grid, as seen on the global grid.
    :param cctk\_ubnd: An array of cctk_dim integers containing the largest index (in each direction) of the local grid, as seen on the global grid.
    :param cctk\_bbox: An array of 2*cctk_dim integers which indicate whether the boundaries are internal boundaries (e.g. between processors), or physical boundaries. A value of 1 indicates a physical (outer) boundary at the edge of the computational grid, and 0 indicates an internal boundary.
    :param cctk\_levfac: An array of cctk_dim integer factors by which the local grid is refined in the corresponding direction with respect to the base grid.
    :param cctk\_levoff: Two arrays of cctk dim integers describing the distance by which the local grid is offset with respect to the base grid, measured in local grid spacings.
    :param cctk\_timefac: The integer factor by which the time step size is reduced with respect to the base grid.
    :param cctk\_convlevel: The convergence level of this grid hierarchy. The base level is 0, and every level above that is coarsened by a factor of cctk_convfac.
    :param cctk\_convfac: The factor between convergence levels. The relation between the resolutions of different convergence levels is :math:`\Delta x_{L}=\Delta x_{0} \cdot F^{L}`, where L is the convergence level and F is the convergence factor. The convergence factor defaults to 2.


cctk_Parameters.h
------------------

Any routine using Cactus parameters should include at the top of the file the header

.. code-block:: c

    #include "cctk_Parameters.h"

The parameters should be declared at the start of the routine using them with the macro ``DECLARE_CCTK_PARAMETERS``.

