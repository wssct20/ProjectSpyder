<?php

//require_once("system.php");
session_start();

$_SESSION["login"] = false;
if (!session_destroy()) die("SESSIONDESTROYFAILED");
header("Location: login.php",true,303);
die();

?>