A brief introduction to C
==========================
C is a programming language originally developed for developing the Unix operating system. It is a low-level and powerful language, but it lacks many modern and useful constructs. C++ is a newer language, based on C, that adds many more modern programming language features that make it easier to program than C. 

A C program should be written into one or more text files with extension ".c".

A C program basically consists of the following parts:

* Preprocessor Commands
* Functions
* Variables
* Statements & Expressions
* Comments

Variables
----------
A variable is nothing but a name given to a storage area that our programs can manipulate. The name of a variable can be composed of letters, digits, and the underscore character. It must begin with either a letter or an underscore. Upper and lowercase letters are distinct because C is case-sensitive. 

Each variable in C has a specific type, which determines how much space it occupies in storage and how the bit pattern stored is interpreted.

======= ===========
Type    Description
======= ===========
char    A single character.
int     An integer.
float   A single-precision floating point value.
double  A double-precision floating point value.
void    Represents the absence of type.
======= ===========

To declare a variable you use

.. code-block:: c

    <variable type> <name of variable>;

Variables can be initialized (assigned an initial value) in their declaration.

.. code-block:: c

    <variable type> <name of variable> = <value of variable>;

Constants
^^^^^^^^^^
Constants refer to fixed values that the program may not alter during its execution. There are two simple ways in C to define constants

* Using ``#define`` preprocessor.
* Using ``const`` keyword.

The #define Preprocessor
"""""""""""""""""""""""""
Given below is the form to use ``#define`` preprocessor to define a constant

.. code-block:: c

    #define <identifier> <value>

The const Keyword
""""""""""""""""""
The word "const" in front of a type name means that the variable is constant and thus its value cannot be modified by the program. Constant variables are initialised when they are declared:

.. code-block:: c

    const <variable type> <name of variable> = <value of variable>;

Arrays
^^^^^^^
Arrays are special variables which can hold more than one value under the same variable name, organised with an index.

To declare an array in C, a programmer specifies the type of the elements and the number of elements required by an array as follows

.. code-block:: c

    <type> <arrayName> [ <arraySize> ];

The arraySize must be an integer constant greater than zero and type can be any valid C data type.

Initializing Arrays
""""""""""""""""""""
You can initialize an array in C either one by one or using a single statement as follows

.. code-block:: c

    double balance[5] = {1000.0, 2.0, 3.4, 7.0, 50.0};

The number of values between braces { } cannot be larger than the number of elements that we declare for the array between square brackets [ ]. If you omit the size of the array, an array just big enough to hold the initialization is created.

Accessing Array Elements
"""""""""""""""""""""""""
An element is accessed by indexing the array name. For example

.. code-block:: c

    double salary = balance[9];

The above statement will take the :math:`10^{th}` element from the array and assign the value to ``salary`` variable.

Strings
^^^^^^^^
Strings are actually one-dimensional array of characters terminated by a null character '\0'.

The following declaration and initialization create a string consisting of the word "Hello". To hold the null character at the end of the array, the size of the character array containing the string is one more than the number of characters in the word "Hello".

.. code-block:: c

    char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};

If you follow the rule of array initialization then you can write the above statement as follows

.. code-block:: c

    char greeting[] = "Hello";

Structures
^^^^^^^^^^^
When programming, it is often convenient to have a single name with which to refer to a group of a related values. Structures provide a way of storing many different values in variables of potentially different types under the same name.

Defining a Structure
"""""""""""""""""""""
To define a structure, you must use the struct statement. The struct statement defines a new data type, with more than one member. The format of the struct statement is as follows

.. code-block:: c

    struct <tag> {
        <members>;
    };

Where Tag is the name of the entire type of structure and Members are the variables within the struct.

Accessing Structure Members
""""""""""""""""""""""""""""
To access any member of a structure, we use the member access operator '.'. 

.. code-block:: c

    struct <tag> <structure_variables>; // Declare <structure_variables> of type <tag>
    <structure_variables>.<members>

Pointers to Structures
"""""""""""""""""""""""
You can define pointers to structures in the same way as you define pointer to any other variable

.. code-block:: c

    struct <tag> *<struct_pointer>;

Now, you can store the address of a structure variable in the above defined pointer variable. To find the address of a structure variable, place the '&'; operator before the structure's name as follows

.. code-block:: c

    <struct_pointer> = &<structure_variables>;

To access the members of a structure using a pointer to that structure, you must use the ``->`` operator as follows

.. code-block:: c

    <struct_pointer> -> <members>

typedef
^^^^^^^^
The C programming language provides a keyword called ``typedef``, which you can use to give a type a new name.

.. code-block:: c

    typedef <existing_name> <alias_name>

Local Variable
^^^^^^^^^^^^^^^
Variables can be declared at any point in the code, provided that, of course, they are declared before they are used. The declaration is valid only within the local block, i.e. within the region limited by braces "{  }".

Size
^^^^^
To get the exact size of a type or a variable on a particular platform, you can use the ``sizeof`` operator.

.. code-block:: c

    int a
    sizeof(a)

Type Casting
^^^^^^^^^^^^^
Converting one datatype into another is known as type casting or, type-conversion. To typecast something, simply put the type of variable you want the actual variable to act as inside parentheses in front of the actual variable.

.. code-block:: c

    (type_name) expression

Functions
----------
A function is simply a collection of commands that do "something". You can either use the built-in library functions or you can create your own functions. 

They must all be declared before there is a call to them. A function declaration tells the compiler about a function's name, return type, and a list of arguments. 

.. code-block:: c

    <return_type> <function_name>(<arguments>)

A function definition provides the actual body of the function.

.. code-block:: c

    <return_type> <function_name>(<arguments>) {
        /* Here goes your code */
    }

Here are all the parts of a function:

* **Return Type** - A function may return a value. The return_type is the data type of the value the function returns. Some functions perform the desired operations without returning a value. In this case, the return_type is the keyword ``void``.
* **Function Name** - This is the actual name of the function.
* **Arguments** - When a function is invoked, you pass a value to the parameter. This value is referred to as actual parameter or argument. The parameter list refers to the type, order, and number of the parameters of a function.
* **Function Body** - The function body contains a collection of statements that define what the function does.

.. note::

    In C, arguments are copied by value to functions, which means that we cannot change the arguments to affect their value outside of the function. To do that, we must use pointers.

Pointers
---------
As you know, every variable is a memory location and every memory location has its address defined which can be accessed using ampersand (&) operator, which denotes an address in memory.

A pointer is a variable whose value is the address of another variable, i.e., direct address of the memory location. Like any variable or constant, you must declare a pointer before using it to store any variable address.

.. code-block:: c

    <type> *<varname>;

Here, type is the pointer's base type; it must be a valid C data type and varname is the name of the pointer variable.

The cool thing is that once you can talk about the address of a variable, you'll then be able to go to that address and retrieve the data stored in it, use the ``*``. The technical name for this doing this is dereferencing the pointer.

NULL Pointers
^^^^^^^^^^^^^^
It is always a good practice to assign a NULL value to a pointer variable in case you do not have an exact address to be assigned. This is done at the time of variable declaration.

Memory allocation
^^^^^^^^^^^^^^^^^^
The function ``malloc``, residing in the *stdlib.h* header file, is used to initialize pointers with memory from free store. The argument to ``malloc`` is the amount of memory requested (in bytes), and ``malloc`` gets a block of memory of that size and then returns a pointer to the block of memory allocated. 

Since different variable types have different memory requirements, we need to get a size for the amount of memory ``malloc`` should return. So we need to know how to get the size of different variable types. This can be done using the keyword ``sizeof``, which takes an expression and returns its size. For example,

.. code-block:: c

    #include <stdlib.h>

    int *ptr = malloc(sizeof(int));

This code set ``ptr`` to point to a memory address of size int. The memory that is pointed to becomes unavailable to other programs. This means that the careful coder should free this memory at the end of its usage lest the memory be lost to the operating system for the duration of the program (this is often called a memory leak because the program is not keeping track of all of its memory). The free function returns memory to the operating system.

.. code-block:: c

    free(ptr);

Passing pointers to functions in C
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
C programming allows passing a pointer to a function. To do so, simply declare the function parameter as a pointer type.


Return pointer from functions in C
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


Operators
----------
An operator is a symbol that tells the compiler to perform specific mathematical or logical functions.

Arithmetic Operators
^^^^^^^^^^^^^^^^^^^^^
The following table shows all the arithmetic operators supported by the C language. 

========= ===============
Operator  Description
========= ===============
\+        Adds two operands.
\-        Subtracts second operand from the first.
\*        Multiplies both operands.
/         Divides numerator by de-numerator.
%         Modulus Operator and remainder of after an integer division.
++        Increment operator increases the integer value by one.
\- \-     Decrement operator decreases the integer value by one.
========= ===============

Relational Operators
^^^^^^^^^^^^^^^^^^^^^
The following table shows all the relational operators supported by C.

========= ===============
Operator  Description
========= ===============
==        Checks if the values of two operands are equal or not. If yes, then the condition becomes true.
!=        Checks if the values of two operands are equal or not. If the values are not equal, then the condition becomes true.
>         Checks if the value of left operand is greater than the value of right operand. If yes, then the condition becomes true.
<         Checks if the value of left operand is less than the value of right operand. If yes, then the condition becomes true.
>=        Checks if the value of left operand is greater than or equal to the value of right operand. If yes, then the condition becomes true.
<=        Checks if the value of left operand is less than or equal to the value of right operand. If yes, then the condition becomes true.
========= ===============

Logical Operators
^^^^^^^^^^^^^^^^^^
Following table shows all the logical operators supported by C language.

========= ===============
Operator  Description
========= ===============
&&        Called Logical AND operator. 
||        Called Logical OR Operator.
!         Called Logical NOT Operator.
========= ===============

Decision
---------
The ``if`` statement allows us to check if an expression is true or false, and execute different code according to the result.

.. code-block:: c

    if ( expression ) {
        /* Here goes your code */
    }
    else { 
        /* Here goes your code */
    }

.. note::

    C programming language assumes any **non-zero** and **non-null** values as **true**, and if it is either **zero** or **null**, then it is assumed as **false** value.

Conditional Operator ``? :`` can be used to replace ``if...else`` statements. It has the following general form

.. code-block:: c

    Exp1 ? Exp2 : Exp3;

File I/O
---------
A file represents a sequence of bytes, regardless of it being a text file or a binary file. C programming language provides access to handle file on your storage devices.

Opening Files
^^^^^^^^^^^^^^
You can use the ``fopen()`` function to create a new file or to open an existing file. This call will initialize an object of the type ``FILE``, which contains all the information necessary to control the stream. The prototype of this function call is as follows

.. code-block:: c

    FILE *fp;
    fp = fopen(filename, mode);

Here, filename is a string literal, which you will use to name your file, and access mode can have one of the following values

===== ===============
Mode  Description
===== ===============
r     Opens an existing text file for reading purpose.
w     Opens a text file for writing. If it does not exist, then a new file is created. Here your program will start writing content from the beginning of the file.
a     Opens a text file for writing in appending mode. If it does not exist, then a new file is created. Here your program will start appending content in the existing file content.
r+    Opens a text file for both reading and writing.
w+    Opens a text file for both reading and writing. It first truncates the file to zero length if it exists, otherwise creates a file if it does not exist.
a+    Opens a text file for both reading and writing. It creates the file if it does not exist. The reading will start from the beginning but writing can only be appended.
===== ===============

Closing a File
^^^^^^^^^^^^^^^
To close a file, use the ``fclose()`` function. The prototype of this function is

.. code-block:: c

    fclose(fp);

The ``fclose()`` function returns zero on success, or EOF if there is an error in closing the file.

Writing a File
^^^^^^^^^^^^^^^
Following is the simplest function to write argument to a stream 

.. code-block:: c

    fprintf(fp, comments);

Reading a File
^^^^^^^^^^^^^^^
Use ``fscanf()`` function to read strings from a file, but it stops reading after encountering the first space character.

.. code-block:: c

    fscanf(fp, "%s", buff);


Library
--------
The C standard library provides numerous built-in functions that your program can call. To access the standard functions that comes with your compiler, you need to include a header with the ``#include`` directive. 

assert.h
^^^^^^^^^^
TODO

math.h
^^^^^^^
TODO

stdio.h
^^^^^^^^
TODO

stdlib.h
^^^^^^^^^
TODO

string.h
^^^^^^^^^
*string.h* is a header file that contains many functions for manipulating strings.

