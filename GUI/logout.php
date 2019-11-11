<?php 

//require_once("system.php");

$_SESSION["login"] = false;
if (!session_destroy()) die("SESSIONDESTROYFAILED");
die("LOGOUT SUCCESSFUL!");

?>