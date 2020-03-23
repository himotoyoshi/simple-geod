#include "ruby.h"
#include "rb_geod.h"

VALUE rb_cGeodesic;

static void 
free_geodesic (Geodesic *geodesic)
{
  if ( geodesic->ref ) {
    free(geodesic->ref);
  }
  free(geodesic);
}

static VALUE
rb_geodesic_s_allocate (VALUE klass)
{
  Geodesic *geodesic;
  return Data_Make_Struct(klass, Geodesic, 0, free_geodesic, geodesic);
}

/*
 *  call-seq:
 *     Geodesic.new(a = 6378137, f = 1.0/298.257223563)  ->  nil
 * 
 *  Sets parameters for geodesic computations.
 *  See manual of 'geod' for the details of paramters.
 *
 */

static VALUE
rb_geodesic_initialize (int argc, VALUE *argv, VALUE self)
{
  VALUE ra, rf;
  Geodesic *geodesic;
  rb_scan_args(argc, argv, "02", &ra, &rf);
  if ( NIL_P(ra) ) {
    ra = rb_float_new(6378137);           /* WGS84 : default */    
  }
  if ( NIL_P(rf) ) {
    rf = rb_float_new(1.0/298.257223563); /* WGS84 : default */    
  }
  Data_Get_Struct(self, Geodesic, geodesic);
  geodesic->ref = ALLOC(struct geod_geodesic);
  geod_init(geodesic->ref, NUM2DBL(ra), NUM2DBL(rf));
  return Qnil;
}

/*
 *  call-seq:
 *     Geodesic#inverse(lon1,lat1,lon2,lat2)  ->  array
 * 
 *  Calculates the forward and back azimuths and distance
 *  between an initial and terminus point latitudes and longitudes.
 *  The latitude should be a floating point value in degrees, which
 *  positive value means northern direction. The longitude should be a
 *  floating point value in degrees, which positive value means western
 *  direction. The returned array contains the forward and back azimuths 
 *  in degrees and distance in the metric specified by +Geod.init+.
 *
 *     geodesic = Geodesic.new()
 *     geodesic.inverse(100,30,-100,-30)
 *     #=> [94.9053479513086, -85.0946520486914, 18101.7096098234]
 *
 */

static VALUE
rb_geodesic_inverse (VALUE self, VALUE vl1, VALUE vp1, VALUE vl2, VALUE vp2)
{
  Geodesic *geodesic;
  double ps12, paz12, paz21;
  Data_Get_Struct(self, Geodesic, geodesic);
  geod_inverse(geodesic->ref, 
                     NUM2DBL(vl1), 
                     NUM2DBL(vp1), 
                     NUM2DBL(vl2),
                     NUM2DBL(vp2), 
                     &ps12, &paz12, &paz21);
  return rb_ary_new3(3,
		     rb_float_new(ps12),
		     rb_float_new(paz12),
		     rb_float_new(paz21));
}

/*
 *  call-seq:
 *     Geodesic#distance(lon1,lat1,lon2,lat2)  ->  array
 *
 *  Shortcut of +Geod.invgeod(lon1,lat1,lon2,lat2)[2]+
 * 
 */

static VALUE
rb_geodesic_distance (VALUE self, VALUE vl1, VALUE vp1, VALUE vl2, VALUE vp2)
{
  Geodesic *geodesic;
  double ps12;
  Data_Get_Struct(self, Geodesic, geodesic);
  geod_inverse(geodesic->ref,
                NUM2DBL(vl1), NUM2DBL(vp1), NUM2DBL(vl2), NUM2DBL(vp2),
                &ps12, 0, 0);
  return rb_float_new(ps12);
}

/*
 *  call-seq:
 *     Geodesic#direct(lat1, lon1, az12, dist)  ->  array
 * 
 *  Calculates the latitude, longitude and back azimuth of a terminus point
 *  given a initial point latitude, longitude, azimuth and  distance.
 *  The latitude should be a floating point value in degrees, which
 *  positive value means northern direction. The longitude should be a
 *  floating point value in degrees, which positive value means western
 *  direction. The returned array contains the latitude, longitude and
 *  back azimuth at the terminus point in degrees.
 *
 *     Geod.init("+ellps=WGS84 +units=km")
 *     Geod.geod(100,30,94.9053479513086,18101.7096098234)
 *     #=> [-99.9999997537569, -30.0000001660067, -85.0946531598225]
 *
 */

static VALUE
rb_geodesic_direct (VALUE self, VALUE vlat1, VALUE vlon1, VALUE vaz, VALUE vdist)
{
  Geodesic *geodesic;
  double l2, p2, az21;
  Data_Get_Struct(self, Geodesic, geodesic);
  geod_direct(geodesic->ref,
                     NUM2DBL(vlat1), NUM2DBL(vlon1), NUM2DBL(vaz), NUM2DBL(vdist), 
                     &l2, &p2, &az21);
  return rb_ary_new3(3,
		     rb_float_new(l2),
		     rb_float_new(p2),
		     rb_float_new(az21));
}

void
Init_geodesic ()
{
  rb_cGeodesic = rb_define_class("GEOD", rb_cObject);
  rb_define_alloc_func(rb_cGeodesic, rb_geodesic_s_allocate);
  rb_define_method(rb_cGeodesic, "initialize", rb_geodesic_initialize, -1);
  rb_define_method(rb_cGeodesic, "direct",   rb_geodesic_direct,  4);
  rb_define_method(rb_cGeodesic, "inverse",  rb_geodesic_inverse,  4);
  rb_define_method(rb_cGeodesic, "distance", rb_geodesic_distance, 4);
}

