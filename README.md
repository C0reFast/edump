### edump - eval() dump tool


如果php代码中使用了eval，使用此扩展可以将eval的代码打印出来，大多的webshell在混淆时都会将源代码压缩后，最终调用`eval`执行，通过此扩展可以对混淆的代码进行解压。


##### 使用方法

```
php -d 'extension=edump.so' xxx.php
```
