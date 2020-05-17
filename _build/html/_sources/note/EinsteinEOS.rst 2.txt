EinsteinEOS
============
Equation of state (EoS) which relates the pressure to some thermodynamically independent quantities, e.g. :math:`P = P(\rho, \epsilon)` are crucial for hydrodynamics and hydro codes.

EOS_Polytrope
---------------
Here the pressure is just a function of the density.

.. math::

    P=K \rho^{\Gamma}

Parameter
^^^^^^^^^^
* Adiabatic Index for Ideal Fluid

    >>> EOS_2d_Polytrope::eos_gamma = 2.0

* Polytropic constant

    >>> EOS_2d_Polytrope::eos_k = 80.0

EOS_Hybrid
-----------
This equation provides a hybrid ideal gas EoS, which consists of a polytropic pressure contribution and a thermal pressure contribution, :math:`P=P_{\mathrm{p}}+P_{\mathrm{th}}`. This EoS, which despite its simplicity is particularly suitable for stellar core collapse simulations, is intended to model the degeneracy pressure of the electrons and (at supranuclear densities) the pressure due to nuclear forces in the polytropic part, and the heating of the matter by shock waves in the thermal part.

To approximate the stiffening of the EoS for densities larger than nuclear matter density :math:`\rho_{\mathrm{nuc}}`, we assume that the adiabatic index :math:`\gamma` jumps from :math:`\gamma_{1}` to :math:`\gamma_{2}` at :math:`\rho = \rho_{\mathrm{nuc}}`.

.. math::

    P= \frac{\gamma-\gamma_{\text {th }}}{\gamma-1} K \rho_{\text {nuc }}^{\gamma_{1}-\gamma} \rho^{\gamma}-\frac{\left(\gamma_{\text {th }}-1\right)\left(\gamma-\gamma_{1}\right)}{\left(\gamma_{1}-1\right)\left(\gamma_{2}-1\right)} K \rho_{\text {nuc }}^{\gamma_{1}-1} \rho +\left(\gamma_{\text {th }}-1\right) \rho \epsilon 

Parameter
^^^^^^^^^^
* :math:`\gamma_{th}` for EOS

    >>> EOS_Hybrid::eos_gamma_th = 1.5

* :math:`\gamma_2` for EOS

    >>> EOS_Hybrid::eos_gamma_supernuclear = 1.66666666666666

* Nuclear matter density

    >>> EOS_Hybrid::rho_nuc = 1.e-10

EOS_Omni
---------
This thorn provides a unified EOS (Equation Of State) interface and implements multiple analytic EOS, and also provides table reader and interpolation routines for finite-temperature microphysical EOS available from `Microphysics: Equation of State <https://stellarcollapse.org/microphysics>`_.

* Polytropic

  This polytropic EOS is used as fall-back when other EOS fail.

  .. math::

    P=K \rho^{\Gamma}

* Gamma-Law

  .. math::

    p=(\gamma-1) \rho \epsilon

  At the initial data stage, it may be necessary to set up initial values for :math:`\epsilon`

  .. math::

    \epsilon=\frac{K}{\gamma-1} \rho^{\gamma-1}

  the parameters poly_gamma_ini and gl_k must be set for this.

* Hybrid

  .. math::

    P= \frac{\gamma-\gamma_{\text {th }}}{\gamma-1} K \rho_{\text {nuc }}^{\gamma_{1}-\gamma} \rho^{\gamma}-\frac{\left(\gamma_{\text {th }}-1\right)\left(\gamma-\gamma_{1}\right)}{\left(\gamma_{1}-1\right)\left(\gamma_{2}-1\right)} K \rho_{\text {nuc }}^{\gamma_{1}-1} \rho +\left(\gamma_{\text {th }}-1\right) \rho \epsilon 

* Finite-Temperature Nuclear EOS
  
  Complex microphysical finite-temperature equations of state come usually in tabulated form.

* Cold Tabulated Nuclear EOS with Gamma Law

  Many equations of state for neutron stars are generated under the assumption of zero temperature. This is perfectly appropriate for cold old neutron stars. In simulations of binary mergers, however, shocks will drive the temperature up, adding a thermal pressure component, which can be accounted for approximately with a Gamma-Law: :math:`P_\mathrm{th} = (\Gamma_\mathrm{th} - 1)\rho\epsilon_\mathrm{th}`

  EOS_Omni implements such an equation of state. It reads in an ASCII EOS table.

Parameter
^^^^^^^^^^
* Polytropic EOS: K the polytropic constant set via poly_k, and :math:`\gamma` is the adiabatic index set via poly_gamma.

    >>> EOS_Omni::poly_gamma = 2.0
    >>> EOS_Omni::poly_k = 100.0

* Gamma-Law: :math:`\gamma` is the adiabatic index set via gl_gamma

    >>> EOS_Omni::poly_gamma_initial = 2.0
    >>> EOS_Omni::gl_gamma = 2.0
    >>> EOS_Omni::gl_k = 100.0

* Hybrid

    >>> EOS_Omni::hybrid_gamma_th = 1.5
    >>> EOS_Omni::hybrid_gamma1 = 1.325
    >>> EOS_Omni::hybrid_gamma2 = 2.5
    >>> EOS_Omni::hybrid_k1 = 0.4640517
    >>> EOS_Omni::hybrid_rho_nuc = 3.238607e-4

* Finite-Temperature Nuclear EOS

    >>> EOS_Omni::nuceos_read_table = "yes"
    >>> EOS_Omni::do_energy_shift = "yes"
    >>> EOS_Omni::nuceos_table_name = "blah.h5"

* Cold Tabulated Nuclear EOS with Gamma Law

    >>> EOS_Omni::coldeos_read_table = "yes"
    >>> EOS_Omni::coldeos_use_thermal_gamma_law = "yes"
    >>> EOS_Omni::coldeos_table_name = "blah.asc"