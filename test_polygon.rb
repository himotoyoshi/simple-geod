require "simple-geod"

geod = GEOD.new

points = [
  [130,35],
  [130,40],
  [140,40],
  [140,35],
  [130,35],
].reverse

lons, lats = points.transpose
p lons, lats
area, perimeter = geod.measure_polygon(lats, lons)

p area/1000/1000
p perimeter/1000