<?php
require_once(__DIR__."/../system.php"); //does this really reference to parent folder?
if (!session_start()) die("SESSIONINITFAILED");


$friendlytypenames = array(
	//"motor" => "Motor",
	//"lock" => "Lock",
	"addressablergbledstrip" => "LED-Strip",
	"rgbled" => "RGB-LED",
	"led" => "LED",
	//"epaper" => "E-Paper Screen",
	"button" => "Button",
	//"finger" => "Fingerprint Sensor",
	//"temperature" => "Temperature Sensor",
	//"rotation" => "Rotational Sensor",
	"rgbdetect" => "RGB Sensor",
	"raw" => "unknown",
	"" => null, //for automatic fallback using ?? when no friendlyname was found
);


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

?>
