<?php
die("unfinished");
require_once("system.php");
checksession();

if ($_POST["action"] ?? "" == "create") {
	$username = $_POST["username"] ?? "";
	$password = $_POST["password"] ?? "";
	if ($username == "" || $password == "") die("CREDENTIALSINCOMPLETE");
	$password = calculateuserhash($username, $password);
	//TODO: sql query into database
}

?>