<?php

function calculateauthcode($type, $subtype, $ipaddress, $pairtime) {
	global $hashprefix, $hashalgo;
	$data = $hashprefix . $type . $subtype . $ipaddress . $pairtime;
	return hash($hashalgo, $data, false);
}

function formatreturnvalues($data, $debug) {
	$returntext = "";
	$returntext = $returntext . "#START\n";
	if (isset($debug) > 0) {
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

?>