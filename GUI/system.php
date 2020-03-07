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
		header("DEBUG: GUI/system.php checksession invalid session");
		header("Location: login.php",true,303);
		die();
	}
}

function sanitizehtml($input) {
	return htmlspecialchars($input, ENT_QUOTES | ENT_HTML401);
}

function getdevicename($device) {
	return (empty($device["name"]) ? ($data["friendly"]["type"] ?? $device["type"])." ".$device["id"] : $device["name"]);
}

?>
