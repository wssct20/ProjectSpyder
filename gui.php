<?php
//die("GUIUNFINISHED");
//TODO whole gui stuff is untested

require_once("GUI/system.php");

//this should only redirect to subpages

//check if session is valid and redirect
header("DEBUG: gui.php redirect");
if (sessionvalid()) {
	header("Location: GUI/main.php",true,307);
} else {
	header("Location: GUI/login.php",true,307);
}
//die();

?>