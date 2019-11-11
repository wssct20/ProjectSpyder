<?php
//die("GUIUNFINISHED");
//TODO whole gui stuff is untested

require_once("GUI/system.php");

//this should only redirect to subpages

//check if session is valid and redirect
if (sessionvalid()) {
	header("Location: GUI/main.php");
} else {
	header("Location: GUI/login.php");
}
//die();

?>