<?php
require_once("sqlfunctions.php"); //sql specific stuff

function calculateauthcode($type, $ipaddress, $pairtime) {
	global $hashprefix, $devicehashalgo;
	$data = $hashprefix . $type . $ipaddress . $pairtime;
	$hash = hash($devicehashalgo, $data, false);
	return strtolower($hash);
}

function calculateuserhash($username, $password) {
	//TODO untested, but believed to be working
	global $hashprefix, $userhashalgo;
	$data = $hashprefix.$username.$password;
	return hash($userhashalgo, $data, false);
}

function formatreturnvalues($data, $debug) {
	$returntext = "";
	$returntext = $returntext . "#START" . "\n";
	if (!empty($debug)) {
		$returntext = $returntext . "#DEBUG" . "\n";
		$returntext = $returntext . $debug . "\n";
	}
	$returntext = $returntext . "#DATA" . "\n";
	$returntext = $returntext . jsonencode($data) . "\n";
	$returntext = $returntext . "#END" . "\n";
	return $returntext;
}

function formaterrorreturn($simpleerrorstring, $debugerrorstring) {
	//prepare error feedback
	$returnstack = array(
		"error" => $simpleerrorstring,
		"requesttimeout" => 60*60, // default to 1h //TODO: implement gettimeout(type)
	);
	return formatreturnvalues($returnstack, $debugerrorstring);
}

function dieerror($simpleerrorstring, $debugerrorstring) {
	//dieerror: die() but with proper error feedback
	die(formaterrorreturn($simpleerrorstring, $debugerrorstring));
}

function getipaddress() {
	$ipaddress = '';
	if (isset($_SERVER['HTTP_CLIENT_IP']))
		$ipaddress = $_SERVER['HTTP_CLIENT_IP'];
	else 
		if (isset($_SERVER['HTTP_X_FORWARDED_FOR']))
			$ipaddress = $_SERVER['HTTP_X_FORWARDED_FOR'];
		else 
			if (isset($_SERVER['HTTP_X_FORWARDED']))
				$ipaddress = $_SERVER['HTTP_X_FORWARDED'];
			else 
				if (isset($_SERVER['HTTP_X_CLUSTER_CLIENT_IP']))
					$ipaddress = $_SERVER['HTTP_X_CLUSTER_CLIENT_IP'];
				else 
					if (isset($_SERVER['HTTP_FORWARDED_FOR']))
						$ipaddress = $_SERVER['HTTP_FORWARDED_FOR'];
					else 
						if (isset($_SERVER['HTTP_FORWARDED']))
							$ipaddress = $_SERVER['HTTP_FORWARDED'];
						else 
							if (isset($_SERVER['REMOTE_ADDR']))
								$ipaddress = $_SERVER['REMOTE_ADDR'];
							else
								$ipaddress = 'UNKNOWN';
	return $ipaddress;
}

function updateconditions() {
	//updateconditions: update devices if conditions match
	$conditions = getconditions();
	foreach($conditions as $condition) {
		$ifdevice = getdevicebyid($condition["ifid"]);
		$ifdata = getdata($device);
		if ($ifdata[$condition["ifvar"]] != $condition["ifvalue"]) continue;
		$thendevice = getdevicebyid($condition["thenid"]);
		$thendata = getdata($thendevice);
		//TODO: check if thenvar exists
		$thendata[$condition["thenvar"]] = $condition["thenvalue"];
		updatedata($thendevice["id"], jsonencode($thendata));
	}
}

function gettimeout($device) {
	// gettimeout: get the client request timeout in seconds
	//TODO: calculate dynamic timeout
	global $updatetime;
	$thisupdatetime = (intval(getdata($device)["preferredupdatetime"]) ?? $updatetime);
	return $thisupdatetime;
}

function jsondecode($json) {
	//decodes a JSON string to an associative array
	return json_decode($json, true);
}

function jsonencode($data) {
	//encodes an associative array to a JSON string
	return json_encode($data);
}

function getdata($device) {
	global $basestructure;
	return array_replace_recursive($basestructure, jsondecode($device["data"]) ?? array());
}

function updatedata($id, $data) {
	sqlupdatedata($id, jsonencode($data));
}

function collectdeviceproperties($device) {
	//filter out device props, to be sent to the client
	$deviceprops = array();
	$deviceprops["id"] = $device["id"];
	$deviceprops["name"] = $device["name"];
	$deviceprops["type"] = $device["type"];
	return $deviceprops;
}

function getparameters() {
	//merges GET and POST parameters to support both methods,
	// POST overwrites GET parameters if both are available
	return array_replace($_REQUEST, $_POST);
}

?>