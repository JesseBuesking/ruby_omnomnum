# OmNomNum

Wrapper for the [OmNomNum](https://github.com/JesseBuesking/omnomnum) c project,
which implements most of the logic from [numerizer](https://github.com/jduff/numerizer).

## Benchmarks

### Memory

| Library | Bytes at exit | Total # of Allocations | Total Frees | Total # of Bytes Allocated | Savings |
| ------- | -------------:| ----------------------:| -----------:| --------------------------:| -------:|
| Numerizer<sup>[1](#footnote-1)</sup> | 2,746,272 | 59,243 | 35,161 | 11,055,638 | - |
| Numerizer<sup>[2](#footnote-2)</sup> | 3,719,364 | 10,852,981 | 10,821,658 | 1,115,915,077 | - |
| Numerizer<sup>[3](#footnote-3)</sup> | 973,092 | 10,793,738 | 10,786,497 | 1,104,859,439 | 1&times; |
| OmNomNum<sup>[1](#footnote-1)</sup> | 2,657,613 | 57,967 | 34,681 | 10,797,999 | - |
| OmNomNum<sup>[2](#footnote-2)</sup> | 2,659,473 | 62,006 | 38,700 | 10,839,010 | - |
| OmNomNum<sup>[3](#footnote-3)</sup> | 1,860 | 4,039 | 4,019 | 41,011 | 25,000+&times; |

<a name="footnote-1">1</a>: loads the library and does nothing else<br/>
<a name="footnote-2">2</a>: runs the string "two hundred" 2,000 times<br/>
<a name="footnote-3">3</a>: difference between <sup>[1](#footnote-1)</sup> and <sup>[2](#footnote-2)</sup><br/>

_Note: Benchmark done using valgrind._
`valgrind ruby -w Ilib test/memory_test_*.rb`

### CPU

| Library | Iterations per second | Speedup |
| ------- | ---------------------:| -------:|
| Numerizer | 323.271 | 1&times; |
| OmNomNum | 2.516M | 7,750+&times; |

### Notes

The [OmNomNum](https://github.com/JesseBuesking/omnomnum) actually has two methods: one that returns a normalized string, and one that returns a list containing the locations of the numbers in the string and their values. `ruby_omnomnum` currently only supports the first function, but the second could eventually be exposed.
