ParamCheck
===========

In your *schedule.ccl* file.

.. code-block:: c

    SCHEDULE MyCRoutine_ParamCheck AT CCTK_PARAMCHECK
    {
        LANG: C
    } "ParamCheck"

In your code.

.. code-block:: c

    #include "cctk.h"

    #include "cctk_Arguments.h"
    #include "cctk_Parameters.h"

    void MyCRoutine_ParamCheck(CCTK_ARGUMENTS)
    {
        DECLARE_CCTK_ARGUMENTS;
        DECLARE_CCTK_PARAMETERS;

        if(! CCTK_EQUALS(metric_type, "physical") &&
           ! CCTK_EQUALS(metric_type, "static conformal"))
        {
            CCTK_PARAMWARN("Unknown ADMBase::metric_type - known types are \"physical\" and \"static conformal\"");
        }
    }

API
----
.. c:function:: int CCTK_IsThornActive(const char* thorn)

    Reports whether a thorn was activated in a parameter file.

    :param char thorn: The character-string name of the thorn 
    :result: **status** (*int*) This function returns a non-zero value if thorn was activated in a parameter file, and zero otherwise.

    >>> if (CCTK_IsThornActive ("MoL")) {
    >>>     /* Here goes your code */
    >>> }

.. c:function:: char CCTK_ParameterValString(const char *name, const char *thorn)

    Get the string representation of a parameter's value.

    :Discussion: The memory must be released with a call to ``free()`` after it has been used.

    :param char name: Parameter name
    :param char thorn: Thorn name (for private parameters) or implementation name (for restricted parameters)
    :result: **valstring** (*char*) - Pointer to parameter value as string
    :error: **NULL** - No parameter with that name was found.

    >>> char *valstring = CCTK_ParameterValString("cctk_run_title", "Cactus")
    >>> assert( valstring != NULL );
    >>> free(valstring);

.. c:function:: CCTK_ParameterGet(const char *name, const char *thorn, int *type)

    Get the data pointer to and type of a parameter’s value.

    :param char name: Parameter name
    :param char thorn: Thorn name (for private parameters) or implementation name (for restricted parameters)
    :param int type: If not NULL, a pointer to an integer which will hold the type of the parameter
    :result: **valstring** (*char*) - Pointer to the parameter value
    :error: **NULL** - No parameter with that name was found.

    >>> const void *ghost_ptr = CCTK_ParameterGet("ghost_size", "Carpet", NULL); 
    >>> assert( ghost_ptr != NULL );
    >>> int ghost = *(const int *)ghost_ptr;

