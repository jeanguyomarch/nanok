===============================================================================
NanoKBS
===============================================================================

Introduction
-------------------------------------------------------------------------------

As stated in the :doc:`intro` page, NanoK must be compiled with the application
that will run on the targeted hardware. As such, NanoK's build shall be driven
by the application. Given this requirement, NanoK should not be built on its
own. So, NanoK does not provide a build system out-of-the-box. This may seem
shocking at first, but this allows an more in-depth integration with the
application. Third parties will be able to tweak NanoK more easily.

Instead, NanoK provides an exhaustive and comprehensive **description of its
sources**, as well as a small (python3) script ``nanokbs/nanokbs.py`` that
allows to generate a build sytem from an input template file. Third-parties
will be able to write the template that better suit their needs. A basic
`ninja`_ build template is provided by NanoK for its testing. It can be used as
an example.


Command-Line Interface
-------------------------------------------------------------------------------

``nanokbs/nanokbs.py`` can be run as an executable python3 script. To consult
the command-line interface of this tool, run the following command, from the
top source directory of NanoK:

.. code:: sh

   ./nanokbs/nanokbs.py --help


``nanokbs/nanokbs.py`` is run to generate a build system if the following
arguments are provided:

* ``--app`` (or ``-a``) to provide the path to a JSON (`hjson`_) file that
  describes how the application is built (see :ref:`app-desc`);
* ``--template`` (or ``-t``) to provide the path to a `jinja2`_ template
  that will be used to generate the application build system; and
* ``--output`` (or ``-o``) to specify the path where the generated build system
  shall be written.


It is likely to always be used as follows:

.. code:: sh

   ./nanokbs/nanokbs.py -a "<path/to/app.hjson>" -t "<path/to/template>" -o "<build>"


.. _app-desc:

Describing a NanoK Application
-------------------------------------------------------------------------------

An application shall be defined in an `hjson`_ file. It is a superset of JSON,
so this description can be written in JSON instead of HJSON. Note however that
HJSON offers a more understandable syntax with syntactic suggar.

This document must define a key ``app``, which shall contain the following data:

* ``arch``: a string that indicates the hardware architecture to be used. The
  possible options can be seen by looking at the directories in the
  ``src/arch`` folder. Note that ``pc`` is reserved to unit tests.
* ``products``: it is a list of binaries compiled against NanoK. Each element
  within this list shall define the following data:

  * ``name``: the name of the binary to be generated;
  * ``path``: provide the path from with all strings in the field ``c_sources``
    and ``asm_sources`` are relative to;
  * ``c_sources`` and ``asm_sources``, which consists in the source files
    required by the product.

* and any other data that a user-defined template may want to use.


You can have a look at the following existing files:

* ``tests/pc/unit.hjson``: used to generate the unit tests;
* ``tests/target/disco.hjson``: used to generate an stm32f4-disco program.

.. _ninja: https://ninja-build.org
.. _hjson: https://hjson.org
.. _jinja2: https://pypi.org/project/Jinja2/
