Initial Data
=============

Timelevel
----------
These are best introduced by an example using finite differencing. Consider the 1-D wave equation

.. math::

    \frac{\partial^{2} \phi}{\partial t^{2}}=\frac{\partial^{2} \phi}{\partial x^{2}}

To solve this by partial differences, one discretises the derivatives to get an equation relating the solution at different times. There are many ways to do this, one of which produces the following difference equation

.. math::

    \phi(t+\Delta t, x)-2 \phi(t, x)+\phi(t-\Delta t, x)=\frac{\Delta t^{2}}{\Delta x^{2}}\{\phi(t, x+\Delta x)-2 \phi(t, x)+\phi(t, x-\Delta x)\}

which relates the three timelevels :math:`t+\Delta t`, :math:`t`, :math:`t-\Delta t`.


All timelevels, except the current level, should be considered read-only during evolution, that is, their values should not be changed by thorns. The exception to this rule is for function initialisation, when the values at the previous timelevels do need to be explicitly filled out.

.. code-block::

    if (timelevels == 1) {
        STORAGE: rho[1]
    }
    else if (timelevels == 2) {
        STORAGE: rho[2]
    }
    else if (timelevels == 3) {
        STORAGE: rho[3]
    }

.. code-block::

    #include <cctk.h>
    #include <cctk_Arguments.h>
    #include <cctk_Parameters.h>

    void MyCRoutine_Zero(CCTK_ARGUMENTS) 
    {
        const int np = cctk_ash[0] * cctk_ash[1] * cctk_ash[2];

        if (CCTK_ActiveTimeLevels(cctkGH, "HydroBase::rho") >= 1) {
    #pragma omp parallel for
            for (int i = 0; i < np; ++i) {
                rho[i] = 0.0; \* Set rho to 0 *\
            }
        }

        if (CCTK_ActiveTimeLevels(cctkGH, "HydroBase::rho") >= 2) {
    #pragma omp parallel for
            for (int i = 0; i < np; ++i) {
                rho_p[i] = 0.0;
            }
        }
        
        if (CCTK_ActiveTimeLevels(cctkGH, "HydroBase::rho") >= 3) {
    #pragma omp parallel for
            for (int i = 0; i < np; ++i) {
                rho_p_p[i] = 0.0;
            }
        }
    }