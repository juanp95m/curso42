
echo true && echo executed
echo true || echo ignored
ls nowhere || echo "ls failed, this runs"
ls Makefile && echo "found makefile"
false && echo skipped
false || echo recovered
