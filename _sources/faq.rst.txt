.. _faq:

Frequently Asked Questions
==========================

Can I use PyEDDL 0.7.0 with PyECVL 0.3.0?
-----------------------------------------

PyEDDL 0.7.0 depends on EDDL 0.5.4a. PyECVL 0.3.0 depends on ECVL 0.2.1, which
fails to build its EDDL support module for EDDL 0.5.4a due to a change in the
EDDL CMake config file names since version 0.4.4.

However, there's a workaround to make it work. After installing EDDL 0.5.4a,
change to the installation directory for CMake config files (e.g.,
``/usr/local/lib/cmake/``) and create symlinks with the names expected by ECVL
0.2.1. Example::

    cd /usr/local/lib/cmake/eddl
    ln -s EDDLConfig.cmake eddlConfig.cmake
    ln -s EDDLConfigVersion.cmake eddlConfigVersion.cmake
    ln -s EDDLTargets-release.cmake eddlTargets-release.cmake
    ln -s EDDLTargets.cmake eddlTargets.cmake

This should allow you to build ECVL with EDDL support, after which you can
build PyEDDL and PyECVL.
