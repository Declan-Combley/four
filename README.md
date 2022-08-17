# Four Pattern

## Rules

You start with a word and the number of digits it has, you then convert the number of digits it has to its word equivalent and get the digits of that associated word and rinse and repeat. The idea is that every word should end up at four and keep repeating because four has four digits. For example if you had the word grandular the next itteration would be nine, nine has four digits and four has four digits, thus leading to an infinite loop.

An example pattern

```
$ ./build.sh && ./four grandular
$           grandular
$       nine | 4 digits
$       four | 4 digits
$         ...| 4 digits
$          ..| 4 digits
$           .| 4 digits
```

## Quickstart

```shell
$ ./build.sh
$ ./four 'text'
```

Reference: https://www.quora.com/What-are-some-interesting-math-concepts
