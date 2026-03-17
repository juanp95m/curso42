
cat << EOF
line1
line2
EOF
grep "a" << END
apple
banana
cherry
diff
END
wc -l << TERMINATOR
line A
line B
line C
TERMINATOR
