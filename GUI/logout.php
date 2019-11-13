<?php 

//require_once("system.php");

$_SESSION["login"] = false;
if (!session_destroy()) die("SESSIONDESTROYFAILED");
header("Location: login.php",true,307);
die();

?>