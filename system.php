<?php
global $devicehashalgo, $userhashalgo, $hashprefix, $updatetime, $types, $db, $systemname, $basestructure;
//systemname: The Name of this system, displayed in GUI, default is ProjectSpyder
$systemname = "ProjectSpyder";
//devicehashalgo: algoryhthm used for computing hash for device authentication purposes
//		can be changed, because only generated when device is paired
$devicehashalgo = "sha512"; //64 bytes, 128 chars
//$devicehashalgo = "sha256"; //32 bytes, 64 chars
//$devicehashalgo = "haval128,3"; //16 bytes, 32 chars
//$devicehashalgo = "crc32"; //4 bytes, 8 chars
//userhashalgo: algoryhthm used for computing hash for user authentication purposes
//		should not be changed, because its used for auth every time and would result in every password being wrong
$userhashalgo = "sha512"; //64 bytes, 128 chars
//hash prefix for individualization
$hashprefix = "WSS";
//updatetime defines how long a client should wait until next update push/request in seconds
//system is optimized for 10 seconds, only increase when needed, never decrease below 10
$updatetime = 10;

require_once("functions.php");
require_once("credentials.php");

// JSON basic structure to merge data with, to prevent errors due to missing parts
$basestructure = jsondecode("{
	\"settings\": {
	},
	\"data\": {
	},
	\"usermodifiabledata\": [],
	\"friendly\": {
		\"settingsvar\": {
		},
		\"datavar\": {
		},
		\"datavalue\": {
		}
	}
}");

//connect to mysql database
$db = new mysqli($sqlhost, $sqluser, $sqlpass, $sqldbname);
if ($db->connect_errno) {
	dieerror("ERRSQLDB", "Failed to connect to MySQL: (" . $db->connect_errno . ") " . $db->connect_error);
}

checktables(); //check for sql tables

?>