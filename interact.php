<?php
$now = time();
require_once("system.php");
$PARAM = getparameters();

$authcode = strtolower($PARAM["authcode"] ?? "");
$data = $PARAM["data"] ?? "";
$requesttype = $PARAM["requesttype"] ?? "";
$type = $PARAM["type"] ?? "";


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

if (!empty($data)) if (jsondecode($data) == null) dieerror("DATAINVALID", "Data is invalid, maybe the JSON is not complete");

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
		// requesttype PUT: place new data into table
		$previousdata = getdata($device["id"]);
		if ($previousdata != $data) {
			updatedata($device["id"], $data);
			updateconditions();
		}
		break;
	case "UPDATE":
		// requesttype UPDATE: merge new data with already existing data
		$previousdata = getdata($device["id"]);
		$newdata = array_merge($previousdata, $data);
		if ($previousdata != $newdata) {
			updatedata($device["id"], $newdata);
			updateconditions();
		}
		break;
	default:
		// requesttype not recognized: return error to client
		dieerror("REQUESTTYPEINVALID");
		break;
}

$returnstack["requesttimeout"] = gettimeout($device);

echo formatreturnvalues($returnstack, $debugstring);

?>