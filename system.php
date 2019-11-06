<?php
global $devicehashalgo, $userhashalgo, $hashprefix, $updatetime, $types, $subtypes, $db;
//devicehashalgo: algoryhthm used for computing hash for device authentication purposes
//$devicehashalgo = "sha512"; //64 bytes
$devicehashalgo = "sha256"; //32 bytes
//$devicehashalgo = "haval128,3"; //16 bytes
//$devicehashalgo = "crc32"; //4 bytes
//userhashalgo: algoryhthm used for computing hash for user authentication purposes
$userhashalgo = "sha512"; //64 bytes
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