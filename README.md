Simple Geod
===========

A Ruby wrapper of geodesic.c

### Description

This is a Ruby wrapper of Charles Karney's [`geodesic.c` (Geodesic routines implemented in C)](https://geographiclib.sourceforge.io/html/C/), which is a part of GeographicLib and is also included in PROJ.4. 

Currently, this library wraps two functions `geod_direct` and `geod_inverse` in `geodesic.c`.
It provides the geodesic calculation between two geographic points.

### Installation

    gem install simple-geod

### Todo

* Implementation of the wrappers for geodesicline routines.
* Implementation of the wrappers for polygon routines.

gl = geod.directline(lat1,lon1,az12,s12)
gl = geod.inverseline(lat1,lon1,lat2,lon2)
gl.position()