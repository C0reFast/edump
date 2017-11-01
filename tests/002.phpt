--TEST--
Check for edump presence
--SKIPIF--
<?php if (!extension_loaded("edump")) print "skip"; ?>
--FILE--
<?php 
eval("echo 'hello';");
?>
--EXPECTF--
/* ----- [start dump %s : eval()'d code] ----- */
echo 'hello';
/* ----- [end dump %s : eval()'d code] ----- */
hello
