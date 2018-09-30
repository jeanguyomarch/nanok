===============================================================================
NanoK Development
===============================================================================

Installing the build dependencies
-------------------------------------------------------------------------------

NanoK requires python3 (probably at least 3.4, but this was not tested so
earlier python3 versions may work). It relies on the `hjson`_ and `jinja2`_
packages. Assuming that ``pip3`` is your pip program for python3, run the
following to install the python dependencies for the current user:

.. code:: sh

   pip3 install --user env/requirements.txt

Then, you need to install the following programs:

* `ninja`_: the fast incremental and parallel build-system;
* `gcc`_: the GNU Compiler Collection with **C11** support;
* `diff`_: to compare files.

You can install the right packages using this one-liner, depending on your
GNU/Linux distribution. It must be run from the top-source directory of NanoK:

+---------------+------------------------------------------------------------+
| Distribution  | Command                                                    |
+===============+============================================================+
| Debian/Ubuntu | ``cat env/debian_packages.txt | xargs sudo apt install``   |
+---------------+------------------------------------------------------------+


Building the Core Unit Tests
-------------------------------------------------------------------------------

The core services provided by NanoK are written in a platform-agnostic module.
This allows them to be tested on a Linux-hosted platform, so the underlying
logic of NanoK can be unit-tested without the burden of maintaining hardware
tests. As such, NanoK is first developed on a Linux-hosted platform, and then
implemented on a physical platform.

You should first make sure you are able to compile and run the core test suite
on a Linux platform. First generate the appropriate build system, then use the
generated ``build.ninja`` to perform the tasks. Assuming a POSIX shell, run the
following:

.. code:: sh

   sh ./scripts/gen-unit-tests.sh
   ninja check


To better understand what the tests do, and how to maintain them, please refer
to the :doc:`unit` page.

.. _hjson: https://pypi.org/project/hjson/
.. _jinja2: https://pypi.org/project/Jinja2/
.. _ninja: https://ninja-build.org
.. _gcc: https://www.gnu.org/software/gcc/
.. _diff: https://www.gnu.org/software/diffutils/
