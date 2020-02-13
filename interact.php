<?php

$now = time();

require_once("system.php");

$authcode = $_REQUEST["authcode"] ?? "";
$data = $_REQUEST["data"] ?? "";
$requesttype = $_REQUEST["requesttype"] ?? "";
$type = $_REQUEST["type"] ?? "";


$ip = getipaddress();
$debugstring = "";

//return array
$returnstack = array();


//get device and check for valid authcode
$device = getdevicebyauthcode($authcode);
if (sizeof($device) == 0) dieerror("AUTHFAILED", "Authentication failed, client should request a new one using pair.");
if ($device["authcode"] != $authcode) die("AUTHCODESQLFATALERROR"); //should never happen

//check if device type matches
if ($device["type"] != $type) dieerror("TYPEMISMATCH","Type doesn't match.");

//update device ip and lastact timestamp
updatedevice($device["id"], $now, $ip);

// check for requesttype
switch ($requesttype) {
	case "GET":
		// requesttype GET: get data and return it to client
		$data = jsondecode($device["data"]);
		$data["device"] = collectdeviceproperties($device);
		$returnstack["data"] = $data;
		break;
	case "PUT":
		// requesttype PUT: place new state into table
		//check for previuos data and only update table and conditions if state changed
		//if (!checkstate($data, $device["type"])) dieerror("DATAINVALID", "Data is invalid, wrong type or old authcode?");
		$previousdata = getdata($device["id"]);
		if ($previousdata != $data) {
			updatedata($device["id"], $data);
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