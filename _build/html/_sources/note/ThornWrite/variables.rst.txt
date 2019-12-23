Cactus Variables
=================

Cactus variables are used instead of local variables for a number of reasons:

* Cactus variables can be made visible to other thorns, allowing thorns to communicate and share data.
* Cactus variables can be distributed and communicated among processors, allowing parallel computation.
* A database of Cactus variables, and their attributes, is held by the flesh, and this information is used by thorns, for example, for obtaining a list of variables for checkpointing.

Cactus variables are collected into groups. All variables in a group are of the same data type, and have the same attributes. Most Cactus operations act on a group as a whole. A group must be declared in its thorn’s ``interface.ccl`` file.

.. code-block:: bash

    <data_type> <group_name> [TYPE=<group_type>] [DIM=<dim>] [TIMELEVELS=<num>] [SIZE=<size in each direction>] [DISTRIB=<distribution_type>] [GHOSTSIZE=<ghostsize>]
    [{
    [<variable_name>, <variable_name>, <variable_name> ]
    } ["<group_description>"]]

Currently, the names of groups and variables must be distinct.

Timelevels
-----------

These are best introduced by an example using finite differencing. Consider the 1-D wave equation

.. math::

    \frac{\partial^{2} \phi}{\partial t^{2}}=\frac{\partial^{2} \phi}{\partial x^{2}}

To solve this by partial differences, one discretises the derivatives to get an equation relating the solution at different times. There are many ways to do this, one of which produces the following difference equation

.. math::

    \phi(t+\Delta t, x)-2 \phi(t, x)+\phi(t-\Delta t, x)=\frac{\Delta t^{2}}{\Delta x^{2}}\{\phi(t, x+\Delta x)-2 \phi(t, x)+\phi(t, x-\Delta x)\}

which relates the three timelevels :math:`t+\Delta t`, :math:`t`, :math:`t-\Delta t`.


All timelevels, except the current level, should be considered read-only during evolution, that is, their values should not be changed by thorns. The exception to this rule is for function initialisation, when the values at the previous timelevels do need to be explicitly filled out.

