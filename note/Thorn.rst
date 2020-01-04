===========
Thorn Guide
===========
Parameter File Syntax
=======================
A parameter file is used to control the behaviour of a Cactus executable.
It specifies initial values for parameters as defined in the various thorns’ param.ccl files.
The name of a parameter file is often given the suffix .par, but this is not mandatory.

A parameter file is a text file whose lines are either comments or parameter statements.
Comments are begin with either '#' or '!'.
A parameter statement consists of one or more parameter names, followed by an ‘=’, followed by the value for this parameter.

The first parameter statement in any parameter file should set ActiveThorns, which is a special parameter that tells the program which thorns are to be activated. 
Only parameters from active thorns can be set (and only those routines scheduled by active thorns are run).
By default, all thorns are inactive.

.. include:: flesh.rst

.. include:: CactusBase.rst

.. include:: Llama.rst

.. include:: CactusNumerical.rst

.. include:: CactusPUGH.rst

.. include:: Carpet.rst

.. include:: EinsteinBase.rst

.. include:: EinsteinInitialData.rst

.. include:: EinsteinEOS.rst

.. include:: EinsteinEvolve.rst

.. include:: McLachlan.rst

.. include:: WVUThorns.rst

.. include:: EinsteinAnalysis.rst

.. include:: CTThorns.rst

.. include:: CactusUtils.rst

.. include:: CactusConnect.rst
