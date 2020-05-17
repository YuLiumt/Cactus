Analysis
=========

Calculation
------------
* determinant

    .. code-block:: c

        #include <stddef.h> 
        #include "cctk.h"

        void MyThorn_MyFunction(CCTK_ARGUMENTS)
        {
            int i, j, k;
            for (k = 0; k < cctk_lsh[2]; ++k) {
                for (j = 0; j < cctk_lsh[1]; ++j) {
                    for (i = 0; i < cctk_lsh[0]; ++i) {
                        int const ind3d = CCTK_GFINDEX3D(cctkGH,i,j,k);

                        det[ind3d]=-(g13p*g13p*g22p)+2.*g12p*g13p*g23p-g11p*g23p* g23p-g12p*g12p*g33p+g11p*g22p*g33p;
                    }
                }
            }
        }
        

Volume integral
----------------
.. code-block:: c

    #include "cctk.h"
    #include "cctk_Arguments.h"

    void MyCRoutine(CCTK_ARGUMENTS) 
    {
        DECLARE_CCTK_ARGUMENTS;

        CCTK_INT reduction_handle;

        reduction_handle = CCTK_ReductionHandle("sum");
        if (reduction_handle < 0) {
            CCTK_WARN(0, "Unable to get reduction handle.");
        }
        CCTK_Reduce(
            cctkGH, 
            -1, 
            reduction_handle, 
            1,
            CCTK_VARIABLE_REAL,
            &ADMMass_VolumeMass[*ADMMass_LoopCounter], 
            1,
            CCTK_VarIndex("ADMMass::ADMMass_VolumeMass_GF")
        )
        // TODO ADMMass
    }

Surface integral
----------------
.. code-block:: c

    #include "cctk.h"
    #include "cctk_Arguments.h"

    void MyCRoutine(CCTK_ARGUMENTS) 
    {
        DECLARE_CCTK_ARGUMENTS;

        // TODO ADMMass
    }