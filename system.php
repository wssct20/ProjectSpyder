<?php
global $devicehashalgo, $userhashalgo, $hashprefix, $updatetime, $types, $subtypes, $db;
//devicehashalgo: algoryhthm used for computing hash for device authentication purposes
//		can be changed, because only generated when device is paired
$devicehashalgo = "sha512"; //64 bytes, 128 chars
//$devicehashalgo = "sha256"; //32 bytes, 64 chars
//$devicehashalgo = "haval128,3"; //16 bytes, 32 chars
//$devicehashalgo = "crc32"; //4 bytes, 8 chars
//userhashalgo: algoryhthm used for computing hash for user authentication purposes
//		should not be changed, because its used for auth every time and would result in every password beeing wrong
$userhashalgo = "sha512"; //64 bytes, 128 chars
//hash prefix for individualization
$hashprefix = "WSS";
//updatetime defines how long a client should wait until next update push/request in seconds
$updatetime = 10;
//following two arrays define which client types this system is compatible with
//general types of clients
$types = array(
	"actuator",
	"sensor",
);
//more specific types of clients, all general types need to be found here
$subtypes = array(
	"actuator" => array(
		//"motor",
		//"lock",
		//"sps",
		"addressablergbledstrip",
		"rgbled",
		"led",
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
require_once("credentials.php");

//connect to mysql database
$db = new mysqli($sqlhost, $sqluser, $sqlpass, $sqldbname);
if ($db->connect_errno) {
	dieerror("ERRSQLDB", "Failed to connect to MySQL: (" . $db->connect_errno . ") " . $db->connect_error);
}

checktables(); //check for sql tables



?>