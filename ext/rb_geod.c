#include "ruby.h"
#include "rb_geod.h"

void Init_geodesic ();
void Init_geodesicline ();
void Init_polygon ();

void
Init_simple_geod ()
{
  Init_geodesic();
  Init_geodesicline();
  Init_polygon();
}

