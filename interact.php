<?php

$now = time();

require_once("system.php");

$authcode = $_REQUEST["authcode"] ?? "";
$state = $_REQUEST["state"] ?? "";
$requesttype = $_REQUEST["requesttype"] ?? "";


$ip = getipaddress();
$debugstring = "";

//return array
$returnstack = array();


//get device and check for valid authcode
$device = getdevicebyauthcode($authcode);
if (sizeof($device) == 0) dieerror("AUTHFAILED", "Authentication failed, client should request a new one using pair.");
if ($device["authcode"] != $authcode) die("AUTHCODESQLFATALERROR"); //should never happen

//update device ip and lastact timestamp
updatedevice($device["id"], $now, $ip);

// check for requesttype
switch ($requesttype) {
	case "GET":
		// requesttype GET: get data and return it to client
		$returnstack["state"] = getdata($device["id"]);
		break;
	case "PUT":
		// requesttype PUT: place new state into table
		//check for previos state and only update table and conditions if state changed
		$stateprevious = getdata($device["id"]);
		if ($stateprevious != $state) {
			updatedata($device["id"], $state);
			updateconditions();
		}
		break;
	default:
		// requesttype not recognized: return error to client
		dieerror("REQUESTTYPEINVALID");
		break;
}

// run type specific actions
specificactions($device, $requesttype, $returnstack);

$returnstack["requesttimeout"] = gettimeout($device["type"]);

echo formatreturnvalues($returnstack, $debugstring);

?>