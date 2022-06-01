#!/bin/bash

assert() {
  expected="$1"
  input="$2"

  actual=$(./objects/test_parser "$input")

  if [ "$actual" = "$expected" ]; then
    echo "'$input' => '$actual'"
  else
    echo "'$input' => '$expected' expected, but got '$actual'"
    exit 1
  fi
}

echo
echo "=== TEST ==="
echo "   parser"
echo

assert '"/bin/ls","."' '/bin/ls .'
assert '"/bin/ls"' '/bin/ls '
assert '"/bin","/bin"' '/bin /bin'
assert '' ''

echo
echo OK
