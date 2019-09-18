CactusNumerical
=================
Provides numerical infrastructure thorns for time integration, artificial dissipation, symmetry boundary conditions, setting up spherical surfaces, interpolation, Method of Lines (MoL) implementation.

MoL
-----
The Method of Lines (MoL) converts a (system of) partial differential equation(s) into an ordinary differential equation containing some spatial differential operator. As an example, consider writing the hyperbolic system of PDE’s

.. math::

    \partial_{t} q+A^{i}(q) \partial_{i} B(q)=s(q)

in the alternative form

.. math::

    \partial_{t} q=L(q)

Given this separation of the time and space discretizations, well known stable ODE integrators such as Runge-Kutta can be used to do the time integration.

Parameter
^^^^^^^^^^
* chooses between the diﬀerent methods.

    >>> MoL::ODE_Method = "RK4"

* controls the number of intermediate steps for the ODE solver. For the generic Runge-Kutta solvers it controls the order of accuracy of the method.

    >>> MoL::MoL_Intermediate_Steps = 4

* controls the amount of scratch space used.

    >>> MoL::MoL_Num_Scratch_Levels = 1

Warning
^^^^^^^^^^
* When using the efficient RK4 evolver the number of intermediate steps must be 4, and the number of scratch levels at least 1.

    >>> MoL::MoL_Intermediate_Steps = 4
    >>> MoL::MoL_Num_Scratch_Levels = 1