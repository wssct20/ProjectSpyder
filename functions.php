<?php

function calculateauthcode($type, $subtype, $ipaddress, $pairtime) {
	global $hashprefix, $devicehashalgo;
	$data = $hashprefix . $type . $subtype . $ipaddress . $pairtime;
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
	foreach ($data as $key => $value) {
		$returntext = $returntext . "[" . $key . "]" . "=>" . $value . "\n";
	}
	$returntext = $returntext . "#END";
	//$returntext = $returntext."\n";
	return $returntext;
}

function getipaddress() {
	//TODO untested code from stackoverflow, hope it works
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

function checktypes($inputtype, $inputsubtype) {
	global $types, $subtypes;
	$typevalid = false;
	$subtypevalid = false;
	foreach ($types as $type) {
		if ($type == $inputtype) {
			$typevalid = true;
			breaK;
		}
	}
	if (! $typevalid) return false;
	foreach ($subtypes[$inputtype] as $subtype) {
		if ($subtype == $inputsubtype) {
			$subtypevalid = true;
			break;
		}
	}
	if (! $subtypevalid) return false;
	return true;
}

function updateconditions() {
	return;
	//TODO untested code, skipping for now
	$conditions = getconditions();
	foreach($conditions as $condition) {
		$ifdevice = getdevicebyid($condition["ifid"]);
		if ($condition["ifstate"] != getdata($ifdevice["id"], $ifdevice["type"])) continue;
		$thendevice = getdevicebyid($condition["thenid"]);
		updatedata($thendevice["id"], $thendevice["type"], $condition["thenstate"]);
	}
}

?>