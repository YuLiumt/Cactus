Include
========

cctk.h
-------

Any source file using Cactus infrastructure should include the header file cctk.h using the line

.. code-block:: c

    #include "cctk.h"

cctk_Arguments.h
-----------------

A Cactus macro CCTK\_ARGUMENTS is defined for each thorn to contain:

* General information about the grid hierarchy.
* All the grid variables defined in the thorn’s *interface.ccl*.

These variables must be declared at the start of the routine using the macro ``DECLARE\_CCTK\_ARGUMENTS``.

cGH
^^^^^^^

* cctkGH: A C pointer identifying the grid hierarchy.
* cctk\_dim: An integer with the number of dimensions used for this grid hierarchy.
* cctk\_lsh: An array of cctk\_dim integers with the local grid size on this processor.
* cctk\_ash: An array of cctk\_dim integers with the allocated size of the array. 
* cctk\_gsh: An array of cctk\_dim integers with the global grid size.
* cctk\_iteration: The current iteration number.
* cctk\_delta\_time: A CCTK\_REAL with the timestep.
* cctk\_time: A CCTK\_REAL with the current time.
* cctk\_delta\_space: An array of cctk\_dim CCTK\_REALs with the grid spacing in each direction.
* cctk\_nghostzones: An array of cctk\_dim integers with the number of ghostzones used in each direction.
* cctk\_origin\_space: An array of cctk\_dim CCTK\_REALs with the spatial coordinates of the global origin of the grid.
* cctk\_lbnd
* cctk\_ubnd
* cctk\_bbox
* cctk\_levfac
* cctk\_levoff
* cctk\_timefac
* cctk\_convlevel
* cctk\_convfac


cctk_Parameters.h
------------------

Any routine using Cactus parameters should include at the top of the file the header

.. code-block:: c

    #include "cctk_Parameters.h"

The parameters should be declared at the start of the routine using them with the macro ``DECLARE\_CCTK\_PARAMETERS``.

