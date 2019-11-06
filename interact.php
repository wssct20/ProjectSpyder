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
if (sizeof($device) == 0) dieerror("AUTHFAILED");
if ($device["authcode"] != $authcode) die("AUTHCODESQLFATALERROR"); //should never happen

updatedevice($device["id"], $now, $ip);

switch ($requesttype) {
	case "GET":
		$returnstack["state"] = getdata($device["id"], $device["type"]);
		//updateconditions
		break;
	case "PUT":
		updatedata($device["id"], $device["type"], $state);
		updateconditions();
		break;
	default:
		dieerror("REQUESTTYPEINVALID");
		break;
}

updatedevice($device["id"], $now, $ip);

$returnstack["requesttimeout"] = $updatetime;

echo formatreturnvalues($returnstack, $debugstring);

?>