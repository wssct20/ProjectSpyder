<?php
//die("GUIUNFINISHED");
//TODO whole gui stuff is untested

require_once("GUI/system.php");

if (!session_start()) die("SESSIONINITFAILED");

//this should only redirect to subpages

// switch to login page if session is invalid
if (sessionvalid()) {
	header("Location: GUI/main.php");
} else {
	header("Location: GUI/login.php");
}
//die();

?>