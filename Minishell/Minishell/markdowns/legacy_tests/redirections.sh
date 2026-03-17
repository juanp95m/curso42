
echo "test file" > test_file.txt
cat test_file.txt
echo "append this" >> test_file.txt
cat test_file.txt
wc -l < test_file.txt
ls -la > listing.txt
sort < listing.txt
cat < Makefile > copy_makefile.txt

rm test_file.txt listing.txt copy_makefile.txt
