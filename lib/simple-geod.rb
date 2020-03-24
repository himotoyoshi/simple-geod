require "simple_geod.so"

class GEOD

  alias direct_latlon direct
  
  def direct_lonlat (lon1, lat1, az12, s12)
    return direct(lat1, lon1, az12, s12)
  end
  
  alias inverse_latlon inverse
  
  def inverse_lonlat (lon1, lat1, lon2, lat2)
    return inverse(lat1, lon1, lat2, lon2)
  end    
  
  alias distance_latlon distance

  def distance_lonlat (lon1, lat1, lon2, lat2)
    return distance(lat1, lon1, lat2, lon2)
  end

  def measure_polygon (lats, lons)
    if lats.size != lons.size
      raise "lon list and lat list should has same length."
    end
    if lats.size < 3
      raise "lon list and lat list should include at least 3 points."
    end
    return *_measure_polygon(lats.pack("d*"), lons.pack("d*"), lats.size)
  end

  def geodline (lat0, lon0, lat1, lon1, count: nil, interval: nil)

    total_geod_S, az12, az21 = self.inverse(lat0, lon0, lat1, lon1)
    total_geod_S *= @fr_meter

    if not count.nil? and interval.nil?
      del_S = total_geod_S / ( count - 1 )
    elsif count.nil? and not interval.nil?
      del_S = interval
    else
      del_S = total_geod_S / ( 100 - 1 )
    end

    list = []
    list.push [lon0, lat0, 0]
    
    geod_S = del_S
    loop do 
      lat, lon, az21 = self.forward(lat0, lon0, az12, geod_S*@to_meter)
      list.push [lat, lon, geod_S]
      geod_S += del_S
      if geod_S >= total_geod_S
        break
      end
    end

    list.push [lat1, lon1, total_geod_S]
    
    return list
  end

  alias geodline_latlon geodline

  def geodline_lonlat (lon0, lat0, lon1, lat1, count: nil, interval: nil)
    return geodline(lat0, lon0, lat1, lon1, count: nil, interval: nil)
  end

end
