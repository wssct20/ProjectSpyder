<?php
require_once("specific.php"); //sensor/actuator specifc stuff
require_once ("sqlfunctions.php"); //sql specific stuff

function calculateauthcode($type, $ipaddress, $pairtime) {
	global $hashprefix, $devicehashalgo;
	$data = $hashprefix . $type . $ipaddress . $pairtime;
	return hash($devicehashalgo, $data, false);
}

function calculateuserhash($username, $password) {
	//TODO untested, but believed to be working
	global $hashprefix, $userhashalgo;
	$data = $hashprefix.$username.$password;
	return hash($userhashalgo, $data, false);
}

function formatreturnvalues($data, $debug) {
	$returntext = "";
	$returntext = $returntext . "#START\n";
	if (isset($debug)) {
		$returntext = $returntext . "#DEBUG\n";
		$returntext = $returntext . $debug . "\n";
	}
	$returntext = $returntext . "#DATA\n";
	$returntext = $returntext . jsonencode($data) . "\n";
	$returntext = $returntext . "#END";
	//$returntext = $returntext."\n";
	return $returntext;
}

function formaterrorreturn($simpleerrorstring, $debugerrorstring) {
	//prepare error feedback
	$returnstack = array(
		"error" => $simpleerrorstring,
		"requesttimeout" => 60*60, // default to 1h, maybe move? //TODO: implement gettimeout(type)
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

function checktype($inputtype) {
	//checktype: checks if type is valid and supported by the system
	global $types;
	foreach ($types as $type) {
		if ($type == $inputtype) {
			return true;
		}
	}
	return false;
}

function updateconditions() {
	//updateconditions: update devices if conditions match
	$conditions = getconditions();
	foreach($conditions as $condition) {
		$ifdevice = getdevicebyid($condition["ifid"]);
		if ($condition["ifstate"] != getdata($ifdevice["id"])) continue;
		$thendevice = getdevicebyid($condition["thenid"]);
		updatedata($thendevice["id"], $condition["thenstate"]);
	}
}

function gettimeout($type) {
	// gettimeout: get the client request timeout in seconds
	//TODO: calculate dynamic timeout
	global $updatetime;
	//updatetimes: time in seconds to add to default updatetime depending on device type
	$updatetimes = array(
		"button" => 120,
		"rotation" => -9,
		"" => 0, //default
	);
	$thisupdatetime = $updatetime + ($updatetimes[$type] ?? $updatetimes[""]);
	if ($thisupdatetime < 0) $thisupdatetime = 0;
	return $thisupdatetime;
}

function jsondecode($json) {
	return json_decode($json, true);
}

function jsonencode($data) {
	return json_encode($data);
}

?>