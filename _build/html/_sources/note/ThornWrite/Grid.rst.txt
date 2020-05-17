Coordinate
===========

Global coordinates
-------------------
Compute the global Cactus xyz coordinates of the current grid point.

.. code-block:: c

    #include "cctk.h"

    void MyThorn_MyFunction(CCTK_ARGUMENTS) 
    {
        int i, j, k;
        for (k = 0; k < cctk_lsh[2]; ++k) {
            for (j = 0; j < cctk_lsh[1]; ++j) {
                for (i = 0; i < cctk_lsh[0]; ++i) {
                    // variables declared with 'const' added become constants and cannot be altered by the program.
                    const int ind3d = CCTK_GFINDEX3D(cctkGH,i,j,k);

                    const CCTK_REAL xL = x[ind3d];
                    const CCTK_REAL yL = y[ind3d];
                    const CCTK_REAL zL = z[ind3d];
                    const CCTK_REAL rL = r[ind3d];
                }
            }
        }
    }


.. code-block:: c

    #include "cctk.h"

    void MyThorn_MyFunction(CCTK_ARGUMENTS) 
    {
        int i, j, k;
        /* Do not compute in ghost zones */
        for(i=ghost; i<cctk_lsh[0]-ghost; i++) {
            for(j=ghost; j<cctk_lsh[1]-ghost; j++) {
                for(k=ghost; k<cctk_lsh[2]-ghost; k++) {
                    const int ind3d = CCTK_GFINDEX3D(cctkGH,i,j,k);

                    const CCTK_REAL xL = x[ind3d];
                    const CCTK_REAL yL = y[ind3d];
                    const CCTK_REAL zL = z[ind3d];
                    const CCTK_REAL rL = r[ind3d];
                }
            }
        }
    }


CartGrid3D
-----------
`CartGrid3D` allows you to enforce even or odd parity for any grid function at (across) each coordinate axis. For a function :math:`\phi(x, y, z)`, even parity symmetry on the x-axis means

.. math::

    \phi(-x, y, z)=\phi(x, y, z)

while odd parity symmetry means

.. math::

    \phi(-x, y, z)=- \phi(x, y, z)

You first need to get access to the include ﬁle by putting the line in your `interface.ccl` file. 

.. code-block:: interface.ccl

    uses include: Symmetry.h

Symmetries should obviously be registered before they are used, but since they can be diﬀerent for diﬀerent grids, they must be registered after the ``CCTK_STARTUP`` timebin. The usual place to register symmetries is in the ``CCTK_BASEGRID`` timebin.

.. code-block:: schedule.ccl

    SCHEDULE MyCRoutine_RegisterSymmetry AT CCTK_BASEGRID 
    {
        LANG: C
        OPTIONS: global
    } "Register symmetry"

.. code-block:: c

    #include "cctk.h"
    #include "cctk_Arguments.h"
    #include "Symmetry.h"

    void MyCRoutine_RegisterSymmetry(CCTK_ARGUMENTS) 
    {
        DECLARE_CCTK_ARGUMENTS;

        int sym[3];
        int ierr;

        sym[0] = 1; 
        sym[1] = 1; 
        sym[2] = 1;

        /* Applies symmetry boundary conditions from variable name */
        ierr = SetCartSymVN(cctkGH, sym, "ADMAnalysis::Ricci23");
        /* error information */
        if(ierr) {
            CCTK_VWarn(0, __LINE__, __FILE__, "Thorn_Name", "Error returned from function SetCartSymVN");
        }
    }

Boundary
---------
The implementation `Boundary` provides a number of aliased functions, which allow application thorns to register routines which provide a particular physical boundary condition, and also to select variables or groups of variables to have boundary conditions applied to whenever the `ApplyBCs` schedule group is scheduled.

.. code-block:: c

    SCHEDULE MyCRoutine_Boundaries
    {
        LANG: C
    }  "Select boundary conditions"

    SCHEDULE GROUP ApplyBCs as MyCRoutine_Boundaries
    {
    } "Apply boundary conditions"

To select a grid variable to have a boundary condition applied to it, use one of the following aliased functions:

.. code-block:: c

    #include "cctk.h"
    #include "cctk_Arguments.h"

    void MyCRoutine_Boundaries(CCTK_ARGUMENTS)
    {
        DECLARE_CCTK_ARGUMENTS;

        int ierr;

        /* Select an entire variable group, using its name. */
        err = Boundary_SelectGroupForBC(
            cctkGH, // Grid hierarchy pointer
            CCTK_ALL_FACES, // CCTK_ALL_FACES corresponds to the set of all faces of the domain.
            1, 
            -1, // use default values
            "ADMAnalysis::ricci_scalar", // group name: (<implementation>::<group_name>) 
            "Flat" // The boundary conditions available are Scalar, Flat, Radiation, Copy, Robin, Static, and None.
        );
        if (err < 0) {
            CCTK_WARN(2, "Error in applying flat boundary condition");
        }
    }

Each of these functions takes a faces speciﬁcation, a boundary width, and a table handle as additional arguments. The faces specification is a single integer which identifies a set of faces to which to apply the boundary condition. The boundary width is the thickness, in grid points, of the boundaries. The table handle identifies a table which holds extra arguments for the particular boundary condition that is requested.