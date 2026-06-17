GEMSPEC = "simple-geod.gemspec"

task :install do
  spec = eval File.read(GEMSPEC)
  system %{
    gem build #{GEMSPEC}; gem install --local #{spec.full_name}.gem
  }
end