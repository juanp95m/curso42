echo '$USER'
echo '$?'
echo 'hello world'
echo ''
echo 'no | pipe here'
echo 'no > redirect'
echo 'spaces   preserved'
echo '$USER is not expanded in single quotes'
echo "hello world"
echo "spaces   preserved"
echo "cat lol.c | cat > lol.c"
export DQTEST=expanded
echo "$DQTEST"
echo "value is $DQTEST end"
echo "$?"
echo "'$USER'"
echo '"$USER"'
export USER=estudiante42
echo "'$USER'"
echo '"$USER"'
echo "$COMPLICADO"
echo '$COMPLICADO'
echo "'$COMPLICADO'"
echo '"$COMPLICADO"'
