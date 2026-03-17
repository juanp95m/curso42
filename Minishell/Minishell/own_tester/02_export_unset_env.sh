export TESTVAR=hello42
echo $TESTVAR
export TESTVAR=updated
echo $TESTVAR
echo $?
echo $USER
unset TESTVAR
echo $TESTVAR

export MY_VAR=hello
echo $MY_VAR
env | grep MY_VAR
export MY_VAR=updated
env | grep MY_VAR
unset MY_VAR
env | grep MY_VAR
echo "exit:$?"
export A=1
export B=2
export C=3
unset B
env | grep -E "^A=|^B=|^C=" | sort
export $USER=la
echo $USER
export a b=$LESS c=d
echo $a $b $c
export ""

echo "before whitespace only line"
   
echo "after"
echo "testing dollar in various positions"
export EDGE_VAR=42
echo "value=$EDGE_VAR"
echo $EDGE_VAR$EDGE_VAR
echo "$EDGE_VAR""$EDGE_VAR"

env | grep _=
unset _
env | grep _=
