require "mkmf"

if have_header("geodesic.h") 
  create_makefile("simple_geod")
end
