===============================================================================
 NanoK
===============================================================================

|build-status| |docs|

-------------------------------------------------------------------------------
What is this?
-------------------------------------------------------------------------------

NanoK is a kernel for microcontrollers that is so small it is a nano-kernel
(hence its name "NanoK"). It shall be compiled with the application, in a
*unikernel* fashion.


-------------------------------------------------------------------------------
Documentation
-------------------------------------------------------------------------------

The documentation of NanoK is available at `<https://nanok.readthedocs.io>`_.
To build the documentation, you will need `sphinx`_ to be installed:

.. code:: sh

   pip install --user sphinx sphinx-autobuild sphinx_rtd_theme breathe


Then, use ``docs/Makefile`` to produce the documentation in your favorite
format. For instance, to generate and open the HTML documentation:

.. code:: sh

   make -C docs html
   xdg-open docs/build/html/index.html
   


.. |build-status| image:: https://img.shields.io/travis/jeanguyomarch/nanok.svg?style=flat
    :alt: build status
    :scale: 100%
    :target: https://travis-ci.org/jeanguyomarch/nanok


.. |docs| image:: https://readthedocs.org/projects/nanok/badge/?version=latest
    :alt: Documentation Status
    :scale: 100%
    :target: https://nanok.readthedocs.org

.. _sphinx: http://www.sphinx-doc.org
