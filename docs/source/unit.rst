===============================================================================
NanoK Unit Tests
===============================================================================

Unit tests reside in the `tests/pc/` directory. The following files are worth
considering:

* ``unit.hjson``: which describes the different applications (products) to be
  built. Each product is actually a test;
* ``build-unit-tests.ninja.j2``: which is a `ninja`_ build template to compile
  and run the unit tests on a Linux-hosted platform; and
* ``run-test.sh``: which is the unit tests runner. Each unit test is supposed
  to produce a given result in its standard output. This test compares the
  output to a known reference. Failure in executing the test or exactly
  matching the expected output will yield to a test failure. These references
  are stores in the `tests/pc/refs/` directory.


.. _ninja: https://ninja-build.org
