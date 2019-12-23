EinsteinEvolve
===============
GRHydro
--------
GRHydro uses the hydro variables deﬁned in HydroBase and provides own "conserved" hydro variables and methods to evolve them. It does not provide any information about initial data or equations of state. For these, other thorns are required.

Parameter
^^^^^^^^^^
    >>> ode_method
    >>> mol_timesteps
    >>> recon_method = "ppm"
    >>> riemann_solver = "HLLE"

NewRad
-------
This thorn implements the radiative boundary condition.

.. math::

    \partial_{t} X=-\frac{v_{0} x^{i}}{r} \partial_{i} X-v_{o} \frac{X-X_{0}}{r}

To account also for those parts in the solution which does not behave like a pure outgoing wave, the time derivative term :math:`\partial_{t} X` is modified with:

.. math::

    \left(\partial_{i} X\right)^{*}=\partial_{t} X+\left(\frac{r}{r-n^{i} \partial_{i} r}\right)^{p} n^{i} \partial_{i}\left(\partial_{t} X\right)

where :math:`n^{i}` is the unit normal vector of the considered boundary face, and this correction decays with a power :math:`p = 2` of the radius in our simulations.