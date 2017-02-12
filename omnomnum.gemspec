# -*- encoding: utf-8 -*-
lib = File.expand_path('../lib/', __FILE__)
$:.unshift lib unless $:.include?(lib)

Gem::Specification.new do |s|
  s.name              = 'omnomnum'
  s.version           = '0.0.2'
  s.rubyforge_project = 'omnomnum'
  s.summary           = 'Gobbles up numbers in strings.'
  s.description       = 'OmNomNum normalizes numbers in ruby strings.'
  s.platform          = Gem::Platform::RUBY
  s.authors           = ['Jesse Buesking']
  s.email             = ['jessebuesking@gmail.com']
  s.homepage          = 'https://github.com/JesseBuesking/ruby_omnomnum'
  s.license           = 'BSD-3-Clause'

  s.add_development_dependency 'rake'
  s.add_development_dependency 'rake-compiler'

  s.required_rubygems_version = '>= 1.3.6'

  s.files        = Dir.glob("{bin,lib}/**/*") + Dir.glob("ext/**/*.{c,h,rb}")

  s.extensions = ['ext/omnomnum/extconf.rb']
  s.require_paths = ['lib']
end
