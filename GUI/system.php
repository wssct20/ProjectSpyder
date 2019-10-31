<?php
//require_once("../system.php"); //check if parent folder access is possible this way

function checksession() {
	if (!sessionvalid()) die("SESSIONINVALID");
}
function sessionvalid() {
	//check if login session is valid
	//return false;
	return true;
}


?>
