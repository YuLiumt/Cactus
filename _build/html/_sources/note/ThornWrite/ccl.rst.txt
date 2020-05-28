Cactus Configuration Language
================================
Cactus Configuration Language (CCL) files are text files which tells the flesh all it needs to know about the thorns.

CCL files may contain comments introduced by the hash # character, which indicates that the rest of the line is a comment. If the last non-blank character of a line in a CCL file is a backslash \\, the following line is treated as a continuation of the current line.

The interface.ccl File
-----------------------
The interface configuration file consists of:

* A header block giving details of the thorn's relationship with other thorns.
* A block detailing which include files are used from other thorns, and which include files are provided by this thorn.
* Blocks detailing aliased functions provided or used by this thorn.
* A series of blocks listing the thorn's global variables.

implementation name
^^^^^^^^^^^^^^^^^^^^
The implementation name is declared by a single line at the top of the file

.. code-block:: c

    implements: <name>

The implementation name must be unique among all thorns.

Inheritance relationships between thorns
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
There are two relationship statements that can be used to get variables (actually groups of variables) from other implementations.

* Gets all **Public** variables from implementation <name>, and all variables that <name> has in turn inherited

    .. code-block:: c

        Inherits: <name>

    A thorn cannot inherit from itself. Inheritance is transitive (if A inherits from B, and B inherits from C, then A also implicitly inherits from C), but not commutative.

* Gets all **Protected** variables from implementation <name>, but, unlike inherits, it defines a transitive relation by pushing its own implementation’s **Protected** variables onto implementation <name>.

    .. code-block:: c

        Friend: <name>

    A thorn cannot be its own friend. Friendship is associative, commutative and transitive (if A is a friend of B, and B is a friend of C, then A is implicitly a friend of C).

Include Files
^^^^^^^^^^^^^^
Cactus provides a mechanism for thorns to add code to include files which can be used by any other thorn. Such include files can contain executable source code, or header/declaration information.

.. code-block:: c

    INCLUDE[S] [SOURCE|HEADER]: <file_to_include> in <file_name>

This indicates that this thorn adds the code in <file to include> to the include file <file name>.

Any thorn which uses the include file must declare this in its *interface.ccl* with the line

.. code-block:: c

    USES INCLUDE [SOURCE|HEADER]: <file_name>

If the optional ``[SOURCE|HEADER]`` is omitted, ``HEADER`` is assumed. Note that this can be dangerous, as included source code, which is incorrectly assumed to be header code, will be executed in another thorn even if the providing thorn is inactive. Thus, it is recommended to always include the optional ``[SOURCE|HEADER]`` specification.


Thorn variables
^^^^^^^^^^^^^^^^
Cactus variables are used instead of local variables for a number of reasons:

* Cactus variables can be made visible to other thorns, allowing thorns to communicate and share data.
* Cactus variables can be distributed and communicated among processors, allowing parallel computation.
* A database of Cactus variables, and their attributes, is held by the flesh, and this information is used by thorns, for example, for obtaining a list of variables for checkpointing.

Cactus variables are placed in groups with homogeneous attributes, where the attributes describe properties such as the data type, group type, dimension, ghostsize, number of timelevels, and distribution.

.. code-block:: c

    [<access>:]

    <data_type> <group_name>[[<number>]] [TYPE=<group_type>] [DIM=<dim>] [TIMELEVELS=<num>] [SIZE=<size in each direction>] [DISTRIB=<distribution_type>] [GHOSTSIZE=<ghostsize>] [TAGS=<string>]
    {
        <variable_name>,  <variable_name>,  <variable_name>
    } ["<group_description>"]

Currently, the names of groups and variables must be distinct. The options TYPE, DIM, etc., following <group name> must all appear on one line. 

Access
"""""""
There are three different access levels available for variables

* **Public**: Can be 'inherited' by other implementations.
* **Protected**: Can be shared with other implementations which declare themselves to be friends of this one.
* **Private**: Can only be seen by this thorn.

By default, all groups are **private**, to change this, an access specification of the form ``public:`` or ``protected:``

Data Type
""""""""""
Cactus supports integer, real, complex and character variable types, in various different sizes. Normally a thorn should use the default types (**CCTK\_INT**, **CCTK\_REAL**, **CCTK\_COMPLEX**) rather than explicitly setting the size, as this gives maximum portability.

Vector Group
"""""""""""""
If [number] present, indicates that this is a vector group.

Group Types
""""""""""""
Groups can be either scalars, grid functions (GFs), or grid arrays.

* **SCALAR**: This is just a single number.
* **GF**: This is the most common group type. A GF is an array with a specific size, set at run time in the parameter file, which is distributed across processors. All GFs have the same size, and the same number of ghostzones. Groups of GFs can also specify a dimension, and number of timelevels.
* **ARRAY**: This is a more general form of the GF. Each group of arrays can have a distinct size and number of ghostzones, in addition to dimension and number of timelevels. The drawback of using an array over a GF is that a lot of data about the array can only be determined by function calls, rather than the quicker methods available for GFs.

DIM
""""
DIM defines the spatial dimension of the ARRAY or GF. The default value is ``DIM=3``.

Timelevels
"""""""""""
TIMELEVELS defines the number of timelevels a group has if the group is of type ARRAY or GF, and can take any positive value. The default is one timelevel.

Size and Distrib
"""""""""""""""""
A Cactus grid function or array has a size set at runtime by parameters. This size can either be the global size of the array across all processors (``DISTRIB=DEFAULT``), or, if ``DISTRIB=CONSTANT``, the specified size on each processor. If the size is split across processors, the driver thorn is responsible for assigning the size on each processor.

Ghost Zones
""""""""""""
Cactus is based upon a distributed computing paradigm. That is, the problem domain is split into blocks, each of which is assigned to a processor. For hyperbolic and parabolic problems the blocks only need to communicate at the edges. It defaults to zero.

TAGS
"""""
TAGS defines an optional string which is used to create a set of key-value pairs associated with the group. The keys are case independent. The string (which must be deliminated by single or double quotes) is interpreted by the function ``Util_TableSetFromString()``.

Function
^^^^^^^^^
Cactus offers a mechanism for calling a function in a different thorn where you don't need to know which thorn is actually providing the function, nor what language the function is provided in. Function aliasing is also comparatively inefficient, and should not be used in a part of your code where efficiency is important.

If any aliased function is to be used or provided by the thorn, then the prototype must be declared with the form:

.. code-block:: c

    <return_type> FUNCTION <alias>(<arg1_type> <intent1>, ...)

* The ``<return_type>`` must be either void, CCTK\_INT, CCTK\_REAL, CCTK\_COMPLEX, CCTK\_POINTER, or CCTK\_POINTER\_TO\_CONST. Standard types such as int are not allowed. The keyword ``SUBROUTINE`` is equivalent to ``void FUNCTION``. 
* The name of the aliased function ``<alias>`` must contain at least one uppercase and one lowercase letter and follow the C standard for function names. 
* The type of an argument, ``<arg*_type>``, must be one of scalar types CCTK\_INT, CCTK\_REAL, CCTK\_COMPLEX, CCTK\_POINTER, CCTK\_POINTER\_TO\_CONST, or an array or pointer type CCTK\_INT ARRAY, CCTK\_REAL ARRAY, CCTK\_COMPLEX ARRAY, CCTK\_POINTER ARRAY. The scalar types are assumed to be not modifiable. If you wish to modify an argument, then it must have intent OUT or INOUT (and hence must be either a CCTK\_INT, a CCTK\_REAL, or a CCTK\_COMPLEX, or an array of one of these types). 
* The intent of each argument, ``<intent*>``, must be either IN, OUT, or INOUT. The C prototype will expect an argument with intent IN to be a value and one with intent OUT or INOUT to be a pointer.
* CCTK\_STRING must appear at the end of the argument list.

Using an Aliased Function
""""""""""""""""""""""""""
To use an aliased function you must first declare it in your ``interface.ccl`` file. Declare the prototype as, for example,

.. code-block:: c

    /* this function will be either required in your thorn by */
    REQUIRES FUNCTION <alias>
    /* or optionally used in your thorn by */
    USES FUNCTION <alias>

A prototype of this function will be available to any C routine that includes the ``cctk.h`` header file.

Providing a Function
"""""""""""""""""""""
To provide an aliased function you must again add the prototype to your ``interface.ccl`` file. A statement containing the name of the providing function and the language it is provided in, must also be given. For example,

.. code-block:: c

    PROVIDES FUNCTION <alias> WITH <provider> LANGUAGE <providing_language>

As with the alias name, ``<provider>`` must contain at least one uppercase and one lowercase letter, and follow the C standard for function names. It is necessary to specify the language of the providing function; no default will be assumed. Currently, the only supported values of ``<providing_language>`` are C and Fortran.

Testing Aliased Functions
""""""""""""""""""""""""""
The calling thorn does not know if an aliased function is even provided by another thorn. Calling an aliased function that has not been provided, will lead to a level 0 warning message, stopping the code. In order to check if a function has been provided by some thorn, use the ``CCTK_IsFunctionAliased`` function described in the function reference section.

The param.ccl File
--------------------
Parameters are the means by which the user specifies the runtime behaviour of the code. Each parameter has a data type and a name, as well as a range of allowed values and a default value. These are declared in the thorn's `param.ccl` file.

The full specification for a parameter declaration is

.. code-block:: c

    [<access>:]

    [EXTENDS|USES] <parameter_type> <parameter name>[[<len>]] "<parameter_description>" [AS <alias>] [STEERABLE=<NEVER|ALWAYS|RECOVER>]
    {
        <PARAMETER_RANGES> 
    } <default_value>

The options AS, STEERABLE, etc., following <parameter description>, must all appear in one line.

Access
^^^^^^^
There are three access levels available for parameters:

* **Global**: These parameters are seen by all thorns.
* **Restricted**: These parameters may be used by other implementations if they so desire.
* **Private**: These are only seen by this thorn.

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

    EXTENDS KEYWORD <par> 
    {
        "KEYWORD"   :: "A description of the parameter"
    }

    USES CCTK_REAL <par>

Note that you must compile at least one thorn which implements <name>.

parameter type
^^^^^^^^^^^^^^^
Parameters can be of these types:

* **CCTK\_INT**: Can take any integral value

    The range specification is of the form

    .. code-block:: c

        INT <par> "A description of the parameter"
        {
            \\ Each range may have a description associated with it by placing a ``::`` on the line, and putting the description afterwards.
            lower:upper:stride :: "Describing the allowed values of the parameter. lower and upper specify the lower and upper allowed range, and stride allows numbers to be missed out. A missing end of range (or a `*`) indicates negative or positive infinity."
        } <default value>

* **CCTK\_REAL**: Can take any floating point value

    .. code-block:: c

        REAL <par> "A description of the parameter"
        {
            \\ Each range may have a description associated with it by placing a ``::`` on the line, and putting the description afterwards.
            lower:upper :: "Describing the allowed values of the parameter. lower and upper specify the lower and upper allowed range. A missing end of range (or a `*`) implies negative or positive infinity. " 
        } <default value>

* CCTK\_KEYWORD: A distinct string with only a few known allowed values.

    .. code-block:: c

        KEYWORD <par> "A description of the parameter"
        {
            "KEYWORD_1"   :: "A description of the parameter"
            "KEYWORD_2"   :: "A description of the parameter"
            "KEYWORD_3"   :: "A description of the parameter"
        } <default value>

* CCTK\_STRING: An arbitrary string, which must conform to a given regular expression. To allow any string, the regular expression "" should be used. Regular expressions and string values should be enclosed in double quotes.

* CCTK\_BOOLEAN: A boolean type which can take values 1, t, true, yes or 0, f, false, no.

    .. code-block:: c

        BOOLEAN <par> "A description of the parameter"
        {
        } <default value>

Name
^^^^^^
The <parameter name> must be unique within the scope of the thorn. <len> indicates that this is an array parameter of len values of the specified type. <alias> allows a parameter to appear under a different name in this thorn, other than its original name in another thorn.

Steerable
^^^^^^^^^^
By default, parameters may not be changed after the parameter file has been read, or on restarting from checkpoint. A parameter can be changed dynamically if it is specified to be steerable. It can then be changed by a call to the flesh function ``CCTK_ParameterSet``.

The value RECOVERY is used in checkpoint/recovery situations, and indicates that the parameter may be altered until the value is read in from a recovery par file, but not after.

The schedule.ccl File
-----------------------
A schedule configuration file consists of:

* Assignment statements to switch on storage for grid variables for the entire duration of program execution.
* Schedule blocks to schedule a subroutine from a thorn to be called at specific times during program execution in a given manner.
* Conditional statements for both assignment statements and schedule blocks to allow them to be processed depending on parameter values.

Assignment Statements
^^^^^^^^^^^^^^^^^^^^^^
Assignment statements, currently only assign storage.

These lines have the form:

.. code-block:: c

    STORAGE: <group>[timelevels]

If the thorn is active, storage will be allocated, for the given groups, for the duration of program execution (unless storage is explicitly switched off by some call to ``CCTK_DisableGroupStorage`` within a thorn).

The storage line includes the number of timelevels to activate storage for, this number can be from 1 up to the maximum number or timelevels for the group, as specified in the defining *interface.ccl* file. Alternatively timelevels can be the name of a parameter accessible to the thorn. The parameter name is the same as used in C routines of the thorn, fully qualified parameter names of the form ``thorn::parameter`` are not allowed.

The behaviour of an assignment statement is independent of its position in the schedule file (so long as it is outside a schedule block).

Schedule Blocks
^^^^^^^^^^^^^^^^
The flesh knows about everything in *schedule.ccl* files, and handles sorting scheduled routines into an order. Each schedule block in the file schedule.ccl must have the syntax

.. code-block:: c

    schedule [GROUP] <function|schedule group name> AT|IN <schedule bin|group name> [AS <alias>] [WHILE <variable>] [IF <variable>] [BEFORE|AFTER <item>|(<item> <item> ...)]
    {
        [LANG: <FORTRAN|C>]
        [STORAGE: <group>[timelevels]]
        [TRIGGERS: <group>]
        [SYNC: <group>]
        [OPTIONS: <option>]
        [TAGS: [list of keyword=value definitions]]
        [READS: <group>]
        [WRITES: <group>]
    } "A description"

Schedule Bins
""""""""""""""
Each schedule item is scheduled either AT a particular scheduling bin, or IN a schedule group. A list of the most useful schedule bins for application thorns is given here.

.. figure:: ../picture/Schedule_Bin.png

In the absence of any ordering, functions in a particular schedule bin will be called in an undetermined order.

Group
""""""
If the optional GROUP specifier is used, the item is a schedule group rather than a normal function. Schedule groups are effectively new, user-defined, schedule bins. Functions or groups may be scheduled IN these, in the same way as they are scheduled AT the main schedule bins.

Schedule Options
"""""""""""""""""
The options define various characteristics of the schedule item.

* **AS**: This assigns a new name to a function for scheduling purposes.
* **WHILE**: This specifies a CCTK\_INT grid scalar which is used to control the execution of this item. As long as the grid scalar has a nonzero value, the schedule item will be executed repeatedly.
* **IF**: This specifies a CCTK\_INT grid scalar which is used to control the execution of this item. If the grid scalar has a nonzero value, the schedule item will be executed, otherwise the item will be ignored. If both an IF and a WHILE clause are present, then the schedule is executed according to the following pseudocode:

    .. code-block:: c

        IF condition
            WHILE condition
                SCHEDULE item
            END WHILE
        END IF

* **BEFORE** or **AFTER**: These specify either a function or group before or after which this item will be scheduled.

Further details
""""""""""""""""
The schedule block specifies further details of the scheduled function or group.

* **LANG**: This specifies the language of the routine. Currently this is either C or Fortran.
* **STORAGE**: The STORAGE keyword specifies groups for which memory should be allocated for the duration of the routine or schedule group. The storage status reverts to its previous status after completion of the routine or schedule group.
* **TRIGGER**: List of grid variables or groups to be used as triggers for causing an ANALYSIS function or group to be executed.
* **SYNC**: The keyword SYNC specifies groups of variables which should be synchronised (that is, their ghostzones should be exchanged between processors) on exit from the routine.
* **OPTIONS**: Often used schedule options are local (also the default), level, or global. These options are interpreted by the driver, not by Cactus. The current set of options is useful for Berger-Oliger mesh refinement which has subcycling in time, and for multi-patch simulations in which the domain is split into several distinct patches. Routines scheduled in local mode can access individual grid points, routines scheduled in level mode are used e.g. to select boundary conditions, and routines schedule in global mode are e.g. used to calculate reduction and interpolation. This information is then passed to the driver which should then either invoke such routines once per processor, or once per sub-block per processor.
* **TAGS**: Schedule tags. These tags must have the form keyword=value, and must be in a syntax accepted by ``Util_TableCreateFromString``.
* **READS**: READS is used to declare which grid variables are read by the routine.
* **WRITES**: WRITES is used to declare which grid variables are written by the routine.

Conditional Statements
^^^^^^^^^^^^^^^^^^^^^^^
Besides schedule blocks, it’s possible to embed C style if/else statements in the schedule.ccl file. These can be used to schedule things based upon the value of a parameter.

.. code-block:: c

    if (<conditional-expression>) 
    {
        [<assignments>]
        [<schedule blocks>]
    }

<conditional-expression> can be any valid C construct evaluating to a truth value. Such conditionals are evaluated only at program startup, and are used to pick between different static schedule options.

The Source File
----------------
Compile
^^^^^^^^
By default, the CCTK looks in the ``src`` directory of the thorn for source files.

The Cactus make system looks for a file called ``make.code.defn`` in that directory (if there is no file called ``Makefile`` in the ``src`` directory). At its simplest, this file contains two lines

.. code-block:: bash

    SRCS = <list of all source files in this directory>
    SUBDIRS = <list of all subdirectories, including subdirectories of subdirectories>

Each subdirectory listed should then have a ``make.code.defn`` file containing just a ``SRCS =`` line, a ``SUBDIRS =`` line will be ignored.

Then you need to build the code. The command you need to run is the following:

.. code-block:: bash

    make <name>

Each configuration has a *ThornList* which lists the thorns to be compiled in. When this list changes, only those thorns directly affected by the change are recompiled.

Routines
^^^^^^^^^
Any source file using Cactus infrastructure should include the header file ``cctk.h`` using the line

.. code-block:: c

    #include "cctk.h"

Any routine using Cactus argument lists (for example, all routines called from the scheduler at time bins between CCTK\_STARTUP and CCTK\_SHUTDOWN) should include at the top of the file the header

.. code-block:: c

    #include "cctk_Arguments.h"

A Cactus macro CCTK\_ARGUMENTS is defined for each thorn to contain:

* General information about the grid hierarchy.
* All the grid variables defined in the thorn's *interface.ccl*.
* All the grid variables required from other thorns as requested by the ``inherits`` and ``friend`` lines in the *interface.ccl*.

These variables must be declared at the start of the routine using the macro DECLARE\_CCTK\_ARGUMENTS.

Any routine using Cactus parameters should include at the top of the file the header

.. code-block:: c

    #include "cctk_Parameters.h"

All parameters defined in a thorn's *param.ccl*. Booleans and Integers appear as CCTK\_INT types (with nonzero/zero values for boolean yes/no), Reals as CCTK\_REAL, and Keywords and String parameters as CCTK\_STRING. These variables are read only, and changes should not be made to them. The effect of changing a parameter is undefined (at best). To compare a string valued parameter use the function ``CCTK_Equals()``.

The parameters should be declared at the start of the routine using them with the macro DECLARE\_CCTK\_PARAMETERS.

Example
""""""""
The C routine MyCRoutine is scheduled in the schedule.ccl file, and uses Cactus parameters. The source file should look like

.. code-block:: c

    #include "cctk.h"
    #include "cctk_Arguments.h"
    #include "cctk_Parameters.h"

    void MyFunction(CCTK_ARGUMENTS)
    {
        DECLARE_CCTK_ARGUMENTS
        DECLARE_CCTK_PARAMETERS

        /* Here goes your code */
    };

The C++ routine MyCRoutine is scheduled in the schedule.ccl file, and uses Cactus parameters. The source file should look like

.. code-block:: c

    #include "cctk.h"
    #include "cctk_Arguments.h"
    #include "cctk_Parameters.h"

    extern "C" void MyFunction(CCTK_ARGUMENTS)
    {
        DECLARE_CCTK_ARGUMENTS
        DECLARE_CCTK_PARAMETERS

        /* Here goes your code */
    };

The Fortran routine MyCRoutine is scheduled in the schedule.ccl file, and uses Cactus parameters. The source file should look like

.. code-block:: c

    #include "cctk.h"
    #include "cctk_Arguments.h"
    #include "cctk_Parameters.h"
    #include "cctk_Functions.h"

    subroutine MyFunction(CCTK_ARGUMENTS)

        implicit none

        DECLARE_CCTK_ARGUMENTS
        DECLARE_CCTK_PARAMETERS
        DECLARE_CCTK_FUNCTIONS

        /* Here goes your code */
    end

Specifically for C Programmers
"""""""""""""""""""""""""""""""
Grid functions are held in memory as 1-dimensional C arrays. Cactus provides macros to find the 1-dimensional index which is needed from the multidimensional indices which are usually used. There is a macro for each dimension of grid function. Below is an artificial example to demonstrate this using the 3D macro ``CCTK_GFINDEX3D``:

.. code-block:: c

    for (k=0; k<cctk_lsh[2]; ++k) {
        for (j=0; j<cctk_lsh[1]; ++j) {
            for (i=0; i<cctk_lsh[0]; ++i) {
                int const ind3d = CCTK_GFINDEX3D(cctkGH,i,j,k);
                rho[ind3d] = exp(-pow(r[ind3d],2));
            }
        }
    }

Here, ``CCTK_GFINDEX3D(cctkGH,i,j,k)`` expands to ``((i) + cctkGH->cctk_lsh[0]*((j)+cctkGH->cctk_lsh[1]*(k)))``. In Fortran, grid functions are accessed as Fortran arrays, i.e. simply as ``rho(i,j,k)``.

To access vector grid functions, one also needs to specify the vector index. This is best done via the 3D macro ``CCTK_VECTGFINDEX3D``:

.. code-block:: c

    for (k=0; k<cctk_lsh[2]; ++k) {
        for (j=0; j<cctk_lsh[1]; ++j) {
            for (i=0; i<cctk_lsh[0]; ++i) {
                /* vector indices are 0, 1, 2 */ 
                vel[CCTK_VECTGFINDEX3D(cctkGH,i,j,k,0)] = 1.0; 
                vel[CCTK_VECTGFINDEX3D(cctkGH,i,j,k,1)] = 0.0; 
                vel[CCTK_VECTGFINDEX3D(cctkGH,i,j,k,2)] = 0.0;
            }
        }
    }

Cactus Variables
"""""""""""""""""
The Cactus variables which are passed through the macro ``CCTK_ARGUMENTS`` are

===================== =============
Variables             Description
===================== =============
cctkGH                A C pointer identifying the grid hierarchy.
cctk\_dim             An integer with the number of dimensions used for this grid hierarchy.
cctk\_lsh             An array of cctk\_dim integers with the local grid size on this processor.
cctk\_ash             An array of cctk\_dim integers with the allocated size of the array. 
cctk\_gsh             An array of cctk\_dim integers with the global grid size.
cctk\_iteration       The current iteration number.
cctk\_delta\_time     A CCTK\_REAL with the timestep.
cctk\_time            A CCTK\_REAL with the current time.
cctk\_delta\_space    An array of cctk\_dim CCTK\_REALs with the grid spacing in each direction.
cctk\_nghostzones     An array of cctk\_dim integers with the number of ghostzones used in each direction.
cctk\_origin\_space   An array of cctk\_dim CCTK\_REALs with the spatial coordinates of the global origin of the grid.
cctk\_lbnd            An array of cctk\_dim integers containing the lowest index (in each direction) of the local grid, as seen on the global grid.
cctk\_ubnd            An array of cctk\_dim integers containing the largest index (in each direction) of the local grid, as seen on the global grid.
cctk\_bbox            An array of 2*cctk\_dim integers, which indicate whether the boundaries are internal boundaries (e.g. between processors), or physical boundaries. A value of 1 indicates a physical (outer) boundary at the edge of the computational grid, and 0 indicates an internal boundary.
cctk\_levfac          An array of cctk\_dim integer factors by which the local grid is refined in the corresponding direction with respect to the base grid.
cctk\_levoff          Two arrays of cctk\_dim integers describing the distance by which the local grid is offset with respect to the base grid, measured in local grid spacings.
cctk\_timefac         The integer factor by which the time step size is reduced with respect to the base grid.
cctk\_convlevel       The convergence level of this grid hierarchy. The base level is 0, and every level above that is coarsened by a factor of cctk_convfac.
cctk\_convfac         The factor between convergence levels. The relation between the resolutions of different convergence levels is :math:`\Delta x_{L}=\Delta x_{0} \cdot F^{L}`, where L is the convergence level and F is the convergence factor. The convergence factor defaults to 2.
===================== =============


CCTK Routines
^^^^^^^^^^^^^^
Providing Runtime Information
""""""""""""""""""""""""""""""
To write from thorns to standard output (i.e. the screen) at runtime, use the macro ``CCTK_INFO``. For example,

.. code-block:: c

    CCTK_INFO("Hellow World")

will write the line:

.. code-block:: c

    INFO (MyThorn): Hellow World

Including variables in the info message use ``CCTK_VINFO``. For example,

.. code-block:: c

    CCTK_VINFO("The integer is %d", myint);

Here are some commonly used conversion specifiers:

==========   ========
specifiers   type
==========   ========
%d           int
%g           real (the shortest representation)
%s           string
==========   ========

For a multiprocessor run, only runtime information from processor zero will be printed to screen by default.

Error Handling, Warnings and Code Termination
""""""""""""""""""""""""""""""""""""""""""""""
The Cactus macros ``CCTK_ERROR`` and ``CCTK_VERROR`` should be used to output error messages and abort the code. The Cactus macros ``CCTK_WARN`` and ``CCTK_VWARN`` should be used to issue warning messages during code execution.

Along with the warning message, an integer is given to indicate the severity of the warning.

==================  =====   =====================
Macros              Level   Description
==================  =====   =====================
CCTK_WARN_ABORT     0       abort the Cactus run
CCTK_WARN_ALERT     1       the results of this run will be wrong,
CCTK_WARN_COMPLAIN  2       the user should know about this, but the problem is not terribly surprising
CCTK_WARN_PICKY     3       this is for small problems that can probably be ignored, but that careful people may want to know about
CCTK_WARN_DEBUG     4       these messages are probably useful only for debugging purposes
==================  =====   =====================

A level 0 warning indicates the highest severity (and is guaranteed to abort the Cactus run), while larger numbers indicate less severe warnings. For example,

.. code-block:: c

    CCTK_WARN(CCTK_WARN_ALERT, "Your warning message");
    CCTK_ERROR("Your error message");

Note that if the flesh parameter ``cctk_full_warnings`` is set to true, then ``CCTK_ERROR`` and ``CCTK_WARN`` automatically include the thorn name, the source code file name and line number in the message. The default is to omit the source file name and line number.

Including variables in the warning message use ``CCTK_VERROR`` and ``CCTK_VWARN``. For example,

.. code-block:: c

    CCTK_VWARN(CCTK_WARN_ALERT, "Your warning message, including %f and %d", myreal, myint);
    CCTK_ERROR("Your warning message, including %f and %d", myreal, myint);


Iterating Over Grid Points
"""""""""""""""""""""""""""
A grid function consists of a multi-dimensional array of grid points. These grid points fall into several types:

* **interior**: regular grid point, presumably evolved in time
* **ghost**: inter-process boundary, containing copies of values owned by another process
* **physical boundary**: outer boundary, presumably defined via a boundary condition
* **symmetry boundary**: defined via a symmetry, e.g. a reflection symmetry or periodicity

.. note::

    Grid points in the edges and corners may combine several types. For example, a point in a corner may be a ghost point in the x direction, a physical boundary point in the y direction, and a symmetry point in the z direction.

The size of the physical boundary depends on the application. The number of ghost points is defined by the driver; the number of symmetry points is in principle defined by the thorn implementing the respective symmetry condition, but will in general be the same as the number of ghost points to avoid inconsistencies.

The flesh provides a set of macros to iterate over particular types of grid points.

* Loop over all grid points

    .. code-block:: c

        CCTK_LOOP3_ALL(name, cctkGH, i,j,k) 
        { 
            /* body of the loop */
        } CCTK_ENDLOOP3_ALL(name);

* Loop over all interior grid points

    .. code-block:: c

        CCTK_LOOP3_INT(name, cctkGH, i,j,k) 
        {
            /* body of the loop */
        } CCTK_ENDLOOP3_INT(name);

* Loop over all physical boundary points

    ``LOOP_BND`` loops over all points that are physical boundaries (independent of whether they also are symmetry or ghost boundaries).

    .. code-block:: c

        CCTK_LOOP3_BND(name, cctkGH, i,j,k, ni,nj,nk) 
        { 
            /* body of the loop */
        } CCTK_ENDLOOP3_BND(name);

* Loop over all "interior" physical boundary point

    ``LOOP_INTBND`` loops over those points that are only physical boundaries (and excludes any points that belongs to a symmetry or ghost boundary).

    .. code-block:: c

        CCTK_LOOP3_INTBND(name, cctkGH, i,j,k, ni,nj,nk) 
        {
            /* body of the loop */
        } CCTK_ENDLOOP3_INTBND(name);

In all cases, name should be replaced by a unique name for the loop. i, j, and k are names of variables that will be declared and defined by these macros, containing the index of the current grid point. Similarly ni, nj, and nk are names of variables describing the (outwards pointing) normal direction to the boundary as well as the distance to the boundary.

Interpolation Operators
""""""""""""""""""""""""
There are two different flesh APIs for interpolation, depending on whether the data arrays are Cactus grid arrays or processor-local, programming language built-in arrays.

``CCTK_InterpGridArrays()`` function interpolates a list of CCTK grid variables (in a multiprocessor run these are generally distributed over processors) on a list of interpolation points. The grid topology and coordinates are implicitly specified via a Cactus coordinate system. The interpolation points may be anywhere in the global Cactus grid. Additional parameters for the interpolation operation can be passed in via a handle to a key-value options table.

.. code-block:: c

    #include "cctk.h" 
    #include "util_Table.h"

    /* Pointer to a valid Cactus grid hierarchy. */
    const cGH *GH;

    /* Number of dimensions in which to interpolate. */
    #define N_DIMS 3

    /* Handle to the local interpolation operator as returned by CCTK_InterpHandle. */
    const int operator_handle = CCTK_InterpHandle(interpolator_name);
    if (operator_handle < 0) {
        CCTK_VWARN(CCTK_WARN_ABORT, "Couldn't find interpolator \"%s\"!", interpolator_name); 
    }

    /* Handle to a key-value table containing zero or more additional parameters for the interpolation operation. */
    const int param_table_handle = Util_TableCreateFromString(interpolator_pars);
    if (param_table_handle < 0) {
        CCTK_VWARN(CCTK_WARN_ABORT, "Bad interpolator parameter(s) \"%s\"!", interpolator_pars);
    }

    /* Handle to Cactus coordinate system as returned by CCTK_CoordSystemHandle. */
    const int coord_system_handle = CCTK_CoordSystemHandle(coord_name);
    if (coord_system_handle < 0) {
        CCTK_VWARN(CCTK_WARN_ABORT, "Couldn't get coordinate-system \"%s\"!", coord_name); 
    }
    
    /* The number of interpolation points requested by this processor. */
    #define N_INTERP_POINTS 1000

    /* (Pointer to) an array of N dims pointers to 1-D arrays giving the coordinates of the interpolation points requested by this processor. These coordinates are with respect to the coordinate system defined by coord system handle. */
    CCTK_REAL interp_x[N_INTERP_POINTS], interp_y[N_INTERP_POINTS], interp_z[N_INTERP_POINTS]; 
    const void *interp_coords[N_DIMS];

    interp_coords[0] = (const void *) interp_x;
    interp_coords[1] = (const void *) interp_y;
    interp_coords[2] = (const void *) interp_z;

    /* The number of input variables to be interpolated. */
    #define N_INPUT_ARRAYS 2

    /* (Pointer to) an array of N_input_arrays CCTK grid variable indices (as returned by CCTK_VarIndex) specifying the input grid variables for the interpolation. */
    CCTK_INT input_array_variable_indices[N_INPUT_ARRAYS];
    input_array_variable_indices[0] = CCTK_VarIndex("my_thorn::var1"); 
    input_array_variable_indices[1] = CCTK_VarIndex("my_thorn::var2");

    /* The number of output arrays to be returned from the interpolation. Note that N_output_arrays may differ from N_input_arrays. */
    #define N_OUTPUT_ARRAYS 2

    /* Giving the data types of the 1-D output arrays pointed to by output_arrays[]. */
    CTK_INT output_array_type_codes[N_OUTPUT_ARRAYS]
    output_array_type_codes[0] = CCTK_VARIABLE_REAL
    output_array_type_codes[0] = CCTK_VARIABLE_COMPLEX

    /* (Pointer to) an array of N_output_arrays pointers to the (user-supplied) 1-D output arrays for the interpolation. */
    void *output_arrays[N_OUTPUT_ARRAYS];
    CCTK_REAL output_for_real_array [N_INTERP_POINTS]; 
    CCTK_COMPLEX output_for_complex_array[N_INTERP_POINTS];
    output_arrays[0] = (void *) output_for_real_array;
    output_arrays[1] = (void *) output_for_complex_array;

    int status = CCTK_InterpGridArrays(
        GH,
        N_DIMS,
        operator_handle,
        param_table_handle,
        coord_system_handle,
        N_INTERP_POINTS,
        CCTK_VARIABLE_REAL, // Giving the data type of the interpolation-point coordinate arrays pointed to by interp_coords[].
        interp_coords,
        N_INPUT_ARRAYS,
        input_array_variable_indices,
        N_OUTPUT_ARRAYS,
        output_array_type_codes,
        output_arrays 
    )

    if (status < 0) {
        CCTK_WARN(CCTK_WARN_ABORT, "error return from interpolator!");
    }

``CCTK_InterpLocalUniform()`` interpolate a list of processor-local arrays which define a uniformly-spaced data grid.

Reduction Operators
""""""""""""""""""""
A reduction operation can be defined as an operation on variables distributed across multiple processor resulting in a single number. Typical reduction operations are: sum, minimum/maximum value, and boolean operations. The different operators are identified by their name and/or a unique number, called a handle. 

There are two different flesh APIs for reduction, depending on whether the data arrays are Cactus grid arrays or processor-local, programming language built-in arrays.


``CCTK_ReduceGridArrays()`` reduces a list of CCTK grid arrays (in a multiprocessor run these are generally distributed over processors).

.. code-block:: c

    #include "cctk.h" 
    #include "util_Table.h"

    /* Pointer to a valid Cactus grid hierarchy. */
    const cGH *GH;

    /* Handle to the local reduction operator as returned by CCTK_LocalArrayReductionHandle(). */


    const int status = CCTK_ReduceGridArrays(
        GH,
        0, // The destination processor
        param_table_handle,
        N_INPUT_ARRAYS,
        input_array_variable_indices,
        M_OUTPUT_VALUES,
        output_value_type_codes,
        output_values
    );

``CCTK_ReduceLocalArrays()`` performs reduction on a list of local grid arrays.

Utility Routines
^^^^^^^^^^^^^^^^^
As well as the high-level ``CCTK_*`` routines, Cactus also provides a set of lower-level ``Util_*`` utility routines which thorns developers may use. Cactus functions may need to pass information through a generic interface. In the past, we often had trouble passing ``extra`` information that wasn't anticipated in the original design. Key-value tables provide a clean solution to these problems. They're implemented by the ``Util_Table*`` functions.