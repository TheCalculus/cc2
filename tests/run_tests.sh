#!/bin/bash

set -xa

passes=0
fails=0

for src in *.c; do
  gcc "$src" -o "$src.out"
 
  ./"$src.out" > "$src.output"

  if diff "$src.output" "$src.expected" > /dev/null; then
    echo "test passed for $src"
    passes=$((passes+1))
  else
    echo "test failed for $src"
    diff "$src.output" "$src.expected"
    fails=$((fails+1))
  fi
  
  rm "$src.out" "$src.output"
done

echo "total:$((passes+fails))\npasses:$((passes))\nfails:$((fails))"
