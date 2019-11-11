<?php
require_once(__DIR__."/../system.php"); //does this really reference to parent folder?

function sessionvalid() {
	//TODO: check if login session is valid
	//return false;
	//return true;
	return $_SESSION["login"] ?? false;
}


?>
