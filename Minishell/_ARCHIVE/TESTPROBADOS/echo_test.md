# ExitEcho commands

## Bash
``

echo "Usuario: $USER, Home: $HOME"
output = Usuario: jperez-m, Home: /home/jperez-m

echo "Texto con varios     espacios"
output = Texto con varios     espacios

echo "Texto con caracteres especiales: !@#$%^&*()"
output = Texto con caracteres especiales: !@#$%^&*()

echo "Texto con redirección: > >> < <<"
output = Texto con redirección: > >> < <<

echo "Texto con pipes: | |"
output = Texto con pipes: | |

echo "Texto $USER con $VARIABLE_INEXISTENTE variables"
output = Texto jperez-m con  variables

echo "Texto"" concatenado"
output = Texto concatenado

echo """"""
output = 


echo ";"
output = ;

echo "&&"
output = &&

echo "||"
output = ||

echo "*"
output = *


## Minishell
``
echo 'Usuario: $USER, Home: $HOME'
output = Usuario: jperez-m, Home: /home/jperez-m

echo 'Texto con varios     espacios'
output = Texto con varios     espacios

echo 'Texto con caracteres especiales: !@#$%^&*()'
output = Texto con caracteres especiales: !@#$%^&*()

echo 'Texto con redirección: > >> < <<'
output = Texto con redirección: > >> < <<

echo 'Texto con pipes: | |'
output = Texto con pipes: | |

echo 'Texto $USER con $VARIABLE_INEXISTENTE variables'
output = Texto jperez-m con  variables

echo 'Texto'' concatenado'
output = Texto concatenado

echo ''''''
output = 


echo ';'
output = ;

echo '&&'
output = &&

echo '||'
output = ||

echo '*'
output = *
``