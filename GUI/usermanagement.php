<?php
die("unfinished");
require_once("system.php");

if (!session_start()) die("SESSIONINITFAILED");
checksession();

if ($_POST["action"] ?? "" == "create") {
	$username = $_POST["username"] ?? "";
	$password = $_POST["password"] ?? "";
	if ($username == "" || $password == "") die("CREDENTIALSINCOMPLETE");
	$password = calculateuserhash($username, $password);
	//sql query into database
}

?>