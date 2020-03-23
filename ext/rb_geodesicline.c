#include "ruby.h"
#include "rb_geod.h"

VALUE rb_cGeodesicline;

static void 
free_geodesicline (Geodesicline *geodesicline)
{
  if ( geodesicline->ref ) {
    free(geodesicline->ref);
  }
  free(geodesicline);
}

static VALUE
rb_geodesicline_s_allocate (VALUE klass)
{
  Geodesicline *geodesicline;
  return Data_Make_Struct(klass, Geodesicline, 0, free_geodesicline, geodesicline);
}

void
Init_geodesicline ()
{
}
