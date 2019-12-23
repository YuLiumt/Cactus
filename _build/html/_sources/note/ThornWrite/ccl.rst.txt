Cactus Configuration Language
================================
Cactus Configuration Language (CCL) files are text files which tells the flesh all it needs to know about the thorns.

CCL files may contain comments introduced by the hash # character, which indicates that the rest of the line is a comment. If the last non-blank character of a line in a CCL file is a backslash \\, the following line is treated as a continuation of the current line.

The interface.ccl File
-----------------------
The *interface.ccl* file is used to declare

implementation name
^^^^^^^^^^^^^^^^^^^^

The implementation is declared by a single line at the top of the file

.. code-block:: c

    implements: <name>

Inheritance relationships between thorns
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There are three different access levels available for variables

* **Public**: Can be 'inherited' by other implementations.
* **Protected**: Can be shared with other implementations which declare themselves to be friends of this one.
* **Private**: Can only be seen by this thorn.

Corresponding to the first two access levels there are two relationship statements that can be used to get variables (actually groups of variables) from other implementations.

* Gets all **Public** variables from implementation <name>, and all variables that <name> has in turn inherited

    .. code-block:: c

        Inherits: <name>

* Gets all **Protected** variables from implementation <name>, but, unlike inherits, it defines a transitive relation by pushing its own implementation’s **Protected** variables onto implementation <name>.

    .. code-block:: c

        Friend: <name>

Thorn variables
^^^^^^^^^^^^^^^^
Cactus variables are placed in groups with homogeneous attributes, where the attributes describe properties such as the data type, group type, dimension, ghostsize, number of timelevels, and distribution.

.. code-block:: c

    CCTK_REAL <variables> type=GF TimeLevels=3 Dim=3 {
    <variable name>
    } "Example grid functions"

By default, all groups are **private**, to change this, an access specification of the form ``public:`` or ``protected:``

Global functions
^^^^^^^^^^^^^^^^^


The schedule.ccl File
-----------------------
The flesh knows about everything in *schedule.ccl* files, and handles sorting scheduled routines into an order which is consistent with the BEFORE and AFTER clauses in all the schedule groups. The flesh also handles repeatedly calling scheduled routines which are scheduled with a WHILE clause. In addition, the flesh determines when storage is turned on/off for grid scalars, functions, and arrays and when grid arrays and functions are synchronised, based on the STORAGE: and SYNC: statements in schedule blocks.

.. code-block:: c

    schedule <name> at <time bin> [other options] {
    LANG: <FORTRAN|C>
    OPTIONS: [list of options]
    TAGS: [list of keyword=value definitions]
    STORAGE:
    READS:
    WRITES:
    TRIGGERS:
    SYNC:
    } "A description"

where <name> is the name of the routine, and <time bin> is the name of a schedule bin. A list of the most useful schedule bins for application thorns is given here

.. figure:: ../picture/Schedule_Bin.png

The other options allow finer-grained control of the scheduling.

* **LANG**: C and Fortran linkage are possible here. C++ routines should be defined as extern "C" and registered as ``LANG: C``.
* **OPTIONS**: Often used schedule options are local (also the default), level, or global. Routines scheduled in local mode can access individual grid points, routines scheduled in level mode are used e.g. to select boundary conditions, and routines schedule in global mode are e.g. used to calculate reductions (norms).
* **STORAGE**: The format of the STORAGE statement includes specifying the number of timelevels of each group for which storage should be activated, ``STORAGE: <group>[timelevels]``. This number can range from one to the maximum number of timelevels for the group, as specified in the group definition in its interface.ccl file.
* **SYNC**: The keyword SYNC specifies groups of variables which should be synchronised (that is, their ghostzones should be exchanged between processors) on exit from the routine.

Besides schedule blocks, it’s possible to embed C style if/else statements in the schedule.ccl file. These can be used to schedule things based upon the value of a parameter.

The param.ccl File
--------------------
The flesh and thorns are controlled by a parameter file; parameters must be declared along with their allowed values. If a parameter is not assigned in a parameter file, it is given its default value.

There are three access levels available for parameters:

* **Global**: These parameters are seen by all thorns.
* **Restricted**: These parameters may be used by other implementations if they so desire.
* **Private**: These are only seen by this thorn.

parameter type
^^^^^^^^^^^^^^^

* CCTK\_REAL

    .. code-block:: c

        REAL <par> "A description of the parameter"
        {
        0:3.14 :: "Describing the allowed values of the parameter. Each range may have a description associated with it by placing a ``::`` on the line, and putting the description afterwards." 
        } <default value>

* CCTK\_INT
* CCTK\_KEYWORD: A distinct string with only a few known allowed values.

    .. code-block:: c

        KEYWORD <par> "A description of the parameter"
        {
        "KEYWORD\_1"   :: "A description of the parameter"
        "KEYWORD\_2"   :: "A description of the parameter"
        "KEYWORD\_3"   :: "A description of the parameter"
        } <default value>

* CCTK\_STRING: An arbitrary string, which must conform to a given regular expression.
* CCTK\_BOOLEAN: A boolean type which can take values 1, t, true, yes or 0, f, false, no.

    .. code-block:: c

        BOOLEAN <par> "A description of the parameter"
        {
        } <default value>

Inheritance relationships between thorns
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To access **restricted** parameters from another implementation, a line containing

.. code-block:: c

    shares: <name>

Each of these parameters must be qualified by the initial token **USES** or **EXTENDS**, where

* **USES**: indicates that the parameters range remains unchanged.
* **EXTENDS**: indicates that the parameters range is going to be extended.

For example, the following block adds possible values to the keyword <par> originally defined in the implementation <name>, and uses the REAL parameter <par>.

.. code-block:: c

    shares: <name>

    EXTENDS KEYWORD <par> {
    "KEYWORD"   :: "A description of the parameter"
    }

    USES CCTK_REAL <par>

Note that you must compile at least one thorn which implements <name>

The Source File
----------------

By default, the CCTK looks in the ``src`` directory of the thorn for source files.

The Cactus make system looks for a file called ``make.code.defn`` in that directory (if there is no file called ``Makefile`` in the ``src`` directory). At its simplest, this file contains two lines

.. code-block:: bash

    SRCS = <list of all source files in this directory>
    SUBDIRS = <list of all subdirectories, including subdirectories of subdirectories>

Each subdirectory listed should then have a ``make.code.defn`` file containing just a ``SRCS =`` line, a ``SUBDIRS =`` line will be ignored.