echo "extra" > /tmp/ms_complex_a.txt && cat /tmp/ms_complex_a.txt

echo one && echo two
(echo one && echo two)
true && echo "true_passed"
(true && echo "true_passed")
false && echo "SHOULD_NOT_PRINT"
(false && echo "SHOULD_NOT_PRINT")
false || echo "false_recovered"
(false || echo "false_recovered")
true || echo "SHOULD_NOT_PRINT"
(true || echo "SHOULD_NOT_PRINT")
echo "start" && false || echo "fallback"
(echo "start" && false) || echo "fallback"
false || false || echo "last_resort"
(false || false || echo "last_resort")
true && true && echo "all_true"
(true && true && echo "all_true")
false || true && echo "chain_ok"
(false || true && echo "chain_ok")

(echo uno && (false || echo dos)) && echo tres
(false && echo "nope") || (true && echo "ok")
(echo "A" && (false || (echo "B" && true))) || echo "C"
(false && (echo "no1" || echo "no2")) && echo "no3"
(true && (false || (true && echo "deep"))) && echo "final"
(false || (echo "X" && false) || (echo "Y" && true)) && echo "Z"
(echo "start" && (false || (echo "mid" && false)) && echo "never") || echo "end"
(false || (false && echo "no") || (true && echo "yes")) && echo "done"

ls && echo "éxito"
ls archivo_que_no_existe && echo "no se ve"
ls || echo "no se ve"
ls archivo_que_no_existe || echo "se ve"
true && echo "éxito" || echo "fallo"
false && echo "no se ve" || echo "se ve"
ls && ls && ls && ls && echo "todos exitosos"
ls && ls archivo_que_no_existe && ls && ls
ls || ls || ls || ls
ls archivo_que_no_existe || echo "recuperación" && echo "continúa"
(ls && echo "dentro de paréntesis") && echo "fuera de paréntesis"
(ls archivo_que_no_existe || echo "recuperado") && echo "continúa"
false || (true && echo "esto se ve")
true && (false || echo "esto también")
true && true || false && false
false && false || true && true
(ls && echo a) && (ls && echo b) || (ls && echo c)
