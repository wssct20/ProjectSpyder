<?php
require_once(__DIR__."/../system.php"); //does this really reference to parent folder?

if (!session_start()) die("SESSIONINITFAILED");

function sessionvalid() {
	//TODO: check if login session is valid
	//return false;
	//return true;
	return $_SESSION["login"] ?? false;
}
function checksession() {
	//checksession: checks wether session is valid, if not redirects to login
	if (!sessionvalid()) {
		header("Location: login.php",true,303);
		die();
	}
}

?>
