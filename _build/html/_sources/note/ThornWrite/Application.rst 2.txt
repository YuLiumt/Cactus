Cactus Application
===================
global coordinates
-------------------

Two different ways to calculate the global xyz coordinates of the (i, j, k) grid point

.. code-block:: c

    #include <stddef.h> 
    #include "cctk.h"

    void MyThorn_MyFunction(CCTK_ARGUMENTS)
    {
        int i, j, k;
        for (k = 0; k < cctk_lsh[2]; ++k)
        {
            for (j = 0; j < cctk_lsh[1]; ++j)
            {
                for (i = 0; i < cctk_lsh[0]; ++i)
                {

                const posn = CCTK_GFINDEX3D(cctkGH, i, j, k);

                /* requires that this thorn inherit from Grid */
                const CCTK_REAL xcoord = CCTK_ORIGIN_SPACE(0) + (cctk_lbnd[0] + i) * CCTK_DELTA_SPACE(0); 
                const CCTK_REAL ycoord = CCTK_ORIGIN_SPACE(1) + (cctk_lbnd[1] + j) * CCTK_DELTA_SPACE(1); 
                const CCTK_REAL zcoord = CCTK_ORIGIN_SPACE(2) + (cctk_lbnd[2] + k) * CCTK_DELTA_SPACE(2);
                }
            }
        }
    }

.. code-block:: c

    #include <stddef.h> 
    #include "cctk.h"

    void MyThorn_MyFunction(CCTK_ARGUMENTS)
    {
        int i, j, k;
        for (k = 0; k < cctk_lsh[2]; ++k)
        {
            for (j = 0; j < cctk_lsh[1]; ++j)
            {
                for (i = 0; i < cctk_lsh[0]; ++i)
                {

                const posn = CCTK_GFINDEX3D(cctkGH, i, j, k);

                const CCTK_REAL xcoord = x[posn];
                const CCTK_REAL ycoord = y[posn];
                const CCTK_REAL zcoord = z[posn];
                }
            }
        }
    }

Iterating Over Grid Points
---------------------------
A grid function consists of a multi-dimensional array of grid points. These grid points fall into several types:

* **interior**: regular grid point, presumably evolved in time
* **ghost**: inter-process boundary, containing copies of values owned by another process
* **physical boundary**: outer boundary, presumably defined via a boundary condition
* **symmetry boundary**: defined via a symmetry, e.g. a reflection symmetry or periodicity

.. note::

    Grid points in the edges and corners may combine several types. For example, a point in a corner may be a ghost point in the x direction, a physical boundary point in the y direction, and a symmetry point in the z direction.

The size of the physical boundary depends on the application. The number of ghost points is defined by the driver; the number of symmetry points is in principle defined by the thorn implementing the respective symmetry condition, but will in general be the same as the number of ghost points to avoid inconsistencies.

The flesh provides a set of macros to iterate over particular types of grid points.

Loop over all grid points
^^^^^^^^^^^^^^^^^^^^^^^^^^
.. code-block:: c

    CCTK_LOOP3_ALL(name, cctkGH, i,j,k) 
    { 
        body of the loop
    } CCTK_ENDLOOP3_ALL(name);

Loop over all interior grid points
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. code-block:: c

    CCTK_LOOP3_INT(name, cctkGH, i,j,k) 
    {
        body of the loop
    } CCTK_ENDLOOP3_INT(name);

Loop over all physical boundary points
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``LOOP_BND`` loops over all points that are physical boundaries (independent of whether they also are symmetry or ghost boundaries).

.. code-block:: c

    CCTK_LOOP3_BND(name, cctkGH, i,j,k, ni,nj,nk) 
    { 
        body of the loop
    } CCTK_ENDLOOP3_BND(name);

Loop over all "interior" physical boundary point
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``LOOP_INTBND`` loops over those points that are only physical boundaries (and excludes any points that belongs to a symmetry or ghost boundary).

.. code-block:: c

    CCTK_LOOP3_INTBND(name, cctkGH, i,j,k, ni,nj,nk) 
    {
        body of the loop
    } CCTK_ENDLOOP3_INTBND(name);

Reduction Operators
--------------------
A reduction operation can be defined as an operation on variables distributed across multiple processor resulting in a single number. Typical reduction operations are: sum, minimum/maximum value, and boolean operations. A typical application is, for example, finding the maximum reduction from processor local error estimates, therefore, making the previous processor local error known to all processors.

The exchange of information across processors needs the functionality of a communication layer. For this reason, the reduction operation itself is not part of the flesh, instead, Cactus provides a registration mechanism for thorns to register routines they provide as reduction operators. The different operators are identified by their name and/or a unique number, called a handle.

In Cactus, reduction operators can be applied to grid functions, arrays and scalars, as well as to local arrays.

Each local reduction operator is registered under a character string name; at registration, the name is mapped to a unique integer handle, which may be used to refer to the operator. ``CCTK_LocalArrayReductionHandle()`` is used to get the handle corresponding to a given character string name.