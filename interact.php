<?php
require_once("system.php");

$authcode = $_REQUEST["authcode"] ?? "";
$state = $_REQUEST["state"] ?? "";
$requesttype = $_REQUEST["requesttype"] ?? "";

$now = time();
$ip = getipaddress();
global $updatetime;
$debugstring = "";

//return array
$returnstack = array();

//var_dump($result);


$device = getdevicebyauthcode($authcode);
if (sizeof($device) == 0) die("AUTHFAILED");
if ($device["authcode"] != $authcode) die ("AUTHSQLFAIL"); //should never happen

updatedevice($device["id"], $now, $ip);

switch ($requesttype) {
	case "GET":
		$returnstack["state"] = getdata($device["id"], $device["type"]);
		//updateconditions
		break;
	case "PUT":
		updatedata($device["id"], $device["type"], $state);
		break;
	default:
		die("REQUESTTYPEINVALID");
		break;
}

$returnstack["requesttimeout"] = $updatetime;

die(formatreturnvalues($returnstack, $debugstring));

?>