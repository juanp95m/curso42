cat << EOF
line one
line two
line three
EOF
grep "an" << WORDS
apple
banana
cherry
mango
WORDS
wc -l << COUNTER
a
b
c
d
e
COUNTER
