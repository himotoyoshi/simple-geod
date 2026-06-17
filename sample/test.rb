require "simple-geod"

geod2 = GEOD.new()
p geod2.inverse(30,100,-30,-100)
p geod2.distance(30,100,-30,-100)
# [18101709.587288667, 94.90534751023246, -85.09465248976755]
