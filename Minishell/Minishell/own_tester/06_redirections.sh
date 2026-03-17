echo "first line" > /tmp/ms_test_redir.txt
cat /tmp/ms_test_redir.txt
echo "second line" >> /tmp/ms_test_redir.txt
cat /tmp/ms_test_redir.txt
echo "third line" >> /tmp/ms_test_redir.txt
wc -l < /tmp/ms_test_redir.txt
echo "overwrite" > /tmp/ms_test_redir.txt
cat /tmp/ms_test_redir.txt
rm /tmp/ms_test_redir.txt



