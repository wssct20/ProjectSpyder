<?php
global $hashalgo, $hashprefix, $updatetime, $types, $subtypes, $db;
//algoryhtm used by computing hash for authentication purposes
//$hashalgo = "sha512"; //64 bytes
$hashalgo = "sha256"; //32 bytes
//$hashalgo = "haval128,3"; //16 bytes
//$hashalgo = "crc32"; //4 bytes
//hash prefix for individualization
$hashprefix = "WSS";
//updatetime defines how long a client should wait until next update push/request in seconds
$updatetime = 10;
//following two arrays define which client types this system is compatible with
//general types of clients
$types = array(
	//"actuator",
	"sensor",
);
//more specific types of clients, all general types need to be found here
$subtypes = array(
	"actuator" => array(
		//"motor",
		//"lock",
		//"sps",
		//"addressablergbledstrip",
		//"epaper",
	),
	"sensor" => array(
		"button",
		//"finger",
		//"temp",
		//"rotation",
		//"rgb",
	),
);

require_once ("functions.php");
require_once ("sqlfunctions.php");
require("credentials.php");

$db = new mysqli($sqlhost, $sqluser, $sqlpass, $sqldbname);
if ($db->connect_errno) {
	die("Failed to connect to MySQL: (" . $db->connect_errno . ") " . $db->connect_error);
	die("ERRSQLDB");
}
checktables();



?>