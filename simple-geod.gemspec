Gem::Specification::new do |s|
  version = "1.0.0"
  files = Dir.glob("**/*") - [ 
                               Dir.glob("simple-geod-*.gem"), 
                             ].flatten

  s.platform    = Gem::Platform::RUBY
  s.name        = "simple-geod"
  s.summary     = "A Ruby wrapper of geodesic"
  s.description = <<-HERE
    A Ruby wrapper of geodesic
  HERE
  s.version     = version
  s.licenses    = ['MIT']
  s.author      = "Hiroki Motoyoshi"
  s.email       = ""
  s.homepage    = 'https://github.com/himotoyoshi/simple-geod'
  s.files       = files
  s.extensions  = [ "ext/extconf.rb" ]
  s.required_ruby_version = ">= 1.8.1"
end

