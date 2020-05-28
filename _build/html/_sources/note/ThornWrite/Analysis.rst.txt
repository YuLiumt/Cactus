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
                        int index = CCTK_GFINDEX3D(cctkGH,i,j,k);

                        double gxxL = gxx[index];
                        double gxyL = gxy[index];
                        double gxzL = gxz[index];
                        double gyyL = gyy[index];
                        double gyzL = gyz[index];
                        double gzzL = gzz[index];

                        double det = -gxzL*gxzL*gyyL + 2*gxyL*gxzL*gyzL - gxxL*gyzL*gyzL - gxyL*gxyL*gzzL + gxxL*gyyL*gzzL;
                        double invdet = 1.0 / det;
                        double gupxxL=(-gyzL*gyzL + gyyL*gzzL)*invdet;
                        double gupxyL=( gxzL*gyzL - gxyL*gzzL)*invdet;
                        double gupyyL=(-gxzL*gxzL + gxxL*gzzL)*invdet;
                        double gupxzL=(-gxzL*gyyL + gxyL*gyzL)*invdet;
                        double gupyzL=( gxyL*gxzL - gxxL*gyzL)*invdet;
                        double gupzzL=(-gxyL*gxyL + gxxL*gyyL)*invdet;
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