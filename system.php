<?php
require_once ("functions.php");
//algoryhtm used by computing hash for authentication purposes
//$hashalgo = "sha512"; //64 bytes
$hashalgo = "sha256"; //32 bytes
//$hashalgo = "haval128,3"; //16 bytes
//$hashalgo = "crc32"; //4 bytes
//hash prefix for individualization
$hashprefix = "WSS";
//following to arrays define which client types this system is compatible with
//general types of clients
$types = array(
	"actuator",
	"sensor",
	"gui",
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
		//"button",
		//"finger",
		//"temp",
		//"rotation",
		//"rgb",
	),
	"gui" => array(
		//"gui",
	),
);

$db = new mysqli($sqlhost, $sqluser, $sqlpass, $sqldbname);
if ($db->connect_errno) {
	// die("Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error);
	die("ERRSQLDB");
}

function calculateauthcode($id, $ipaddress, $pairtime) {
	$data = $hashprefix.$id.$ipaddress.$pairtime;
	return hash($hashalgo, $data, false);
}

function preparereturnvalues($data, $debug) {
	$returntext = "";
	if (sizeof($debug) > 0) {
		$returntext = $returntext."#DEBUG\n";
		foreach ($debug as $key => $value) {
			$returntext = $returntext."[".$key."]"."=>".$value."\n";
		}
	}
	$returntext = $returntext."#DATA\n";
	foreach ($data as $key => $value) {
		$returntext = $returntext."[".$key."]"."=>".$value."\n";
	}
	$returntext = $returntext."#END\n";
}

?>