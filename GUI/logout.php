<?php 

//require_once("system.php");

if (!session_start()) die("SESSIONINITFAILED");


$_SESSION["login"] = false;
if (!session_destroy()) die("SESSIONDESTROYFAILED");
die("LOGOUT SUCCESSFUL!");

?>