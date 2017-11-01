
PHP_ARG_ENABLE(edump, whether to enable edump support,
[  --enable-edump           Enable edump support])

if test "$PHP_EDUMP" != "no"; then
  PHP_NEW_EXTENSION(edump, edump.c, $ext_shared)
fi
