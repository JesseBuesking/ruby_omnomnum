require "rubygems"
require "hoe"
require "rake/extensiontask"

lib = File.expand_path("../lib/", __FILE__)
$:.unshift lib unless $:.include?(lib)

require "omnomnum/version"

Hoe.spec "omnomnum" do
  developer("Jesse Buesking", "jessebuesking at gmail dot com")
  self.version = OmNomNum::VERSION
  self.readme_file = "readme.md"
  self.history_file = "History.txt"
  self.extra_dev_deps << ["rake-compile", ">= 0"]
  self.spec_extras = { :extensions => ["ext/omnomnum/extconf.rb"] }
  self.clean_globs << "ext/omnomnum/ruby_omnomnum.o"

  Rake::ExtensionTask.new("omnomnum", spec) do |ext|
    ext.lib_dir = File.join("lib", "omnomnum")
  end

  license ""
end

Rake::Task[:test].prerequisites << :compile
