# -*- encoding: utf-8 -*-
lib = File.expand_path('../lib/', __FILE__)
$:.unshift lib unless $:.include?(lib)

Gem::Specification.new do |gem|
  gem.name        = "omnomnum"
  gem.version     = "0.0.1"
  gem.platform    = Gem::Platform::RUBY
  gem.authors     = [""]
  gem.email       = [""]
  gem.homepage    = ""
  gem.summary     = ""
  gem.description = ""

  gem.add_development_dependency "rake"
  gem.add_development_dependency "rake-compiler"

  gem.required_rubygems_version = ">= 1.3.6"
  gem.rubyforge_project         = "omnomnum"

  gem.files        = Dir.glob("{bin,lib}/**/*") + Dir.glob("ext/**/*.{c,h,rb}")

  gem.extensions = ["ext/omnomnum/extconf.rb"]
  gem.require_paths = ["lib"]
end
