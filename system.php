<?php
global $hashalgo, $hashprefix, $types, $subtypes, $db;
//algoryhtm used by computing hash for authentication purposes
//$hashalgo = "sha512"; //64 bytes
$hashalgo = "sha256"; //32 bytes
//$hashalgo = "haval128,3"; //16 bytes
//$hashalgo = "crc32"; //4 bytes
//hash prefix for individualization
$hashprefix = "WSS";
//following two arrays define which client types this system is compatible with
//general types of clients
$types = array(
	//"actuator",
	"sensor",
	//"gui",
);
//more specific types of clients, all general types need to be found here
$subtypes = array(
	"actuator" => array(
		//"motor",
		//"lock",
		//"sps",
		//"rgbledstrip",
		//"epaper",
	),
	"sensor" => array(
		"button",
		//"finger",
		//"temp",
		//"rotation",
		//"rgb",
	),
	"gui" => array(
		//"gui",
	),
);

require_once ("functions.php");
require("credentials.php");

$db = new mysqli($sqlhost, $sqluser, $sqlpass, $sqldbname);
if ($db->connect_errno) {
	die("Failed to connect to MySQL: (" . $db->connect_errno . ") " . $db->connect_error);
	die("ERRSQLDB");
}



?>