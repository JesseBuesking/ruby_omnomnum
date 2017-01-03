gem "minitest"
require "minitest/autorun"
require "omnomnum"

class TestOmNomNum < Minitest::Test
  def test_basic
    actual = OmNomNum.normalize('one')
    expected = '1'
    assert_equal expected, actual
    assert_equal expected.encoding, actual.encoding
  end

  def test_simple_benchmark_speed
      require 'numerizer'
      require 'benchmark/ips'

      Benchmark.ips do |x|
          x.config(:time => 3, :warmup => 1)
          x.report("numerizer - simple number", "Numerizer.numerize('two hundred')")
          x.report("omnomnum - simple number", "OmNomNum.normalize('two hundred')")
          x.compare!
      end

      assert true
  end

  def test_long_benchmark_speed
      require 'numerizer'
      require 'benchmark/ips'

      Benchmark.ips do |x|
          x.config(:time => 3, :warmup => 1)
          x.report("numerizer - long string", "Numerizer.numerize('two hundred hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world ')")
          x.report("omnomnum - long string", "OmNomNum.normalize('two hundred hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world ')")
          x.compare!
      end

      assert true
  end

  def test_benchmark_long_strings
      require 'numerizer'
      require 'benchmark/ips'

      Benchmark.ips do |x|
          x.config(:time => 3, :warmup => 1)
          x.report("omnomnum - lots of numbers", "OmNomNum.normalize('two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello')")
      end

      assert true
  end
end

