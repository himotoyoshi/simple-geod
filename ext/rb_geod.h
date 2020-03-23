#ifndef RB_GEOD_H
#define RB_GEOD_H

#include <geodesic.h>

typedef struct {
  struct geod_geodesic *ref;
} Geodesic;

typedef struct {
  struct geod_geodesicline *ref;
} Geodesicline;

typedef struct {
  struct geod_polygon *ref;
} Polygon;

extern VALUE rb_mGeod;
extern VALUE rb_cGeodesic;
extern VALUE rb_cGeodesicline;
extern VALUE rb_cPolygon;

#endif

