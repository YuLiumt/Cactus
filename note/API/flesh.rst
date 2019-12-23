Cactus.Flesh
=============

WarnLevel.c
------------

.. py:function:: CCTK_VWarn(level, line, *file, *thorn, *format, ...)

    If the given warning level is less or equal to the current one, it will print the given warning message to stderr.

    :param int level: Warn Level
    :rtype: int

.. py:function:: CCTK_Info(*thorn, *message)

    Print an information message to stdout

    :param char thorn: Name of originating thorn
    :param char message: the warning message to output

.. py:function:: CCTK_VInfo(*thorn, *format, ...)

    Info output routine with variable argument list

    :param char thorn: Name of originating thorn
    :param char format: format string for message