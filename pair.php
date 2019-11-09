<?php 

$now = time();

require_once("system.php");

$type = $_REQUEST["type"];


//return array
$returnstack = array();

//check if type is valid and supported by the system
$typevalid = checktype($type);
if (!$typevalid) {
	dieerror("TYPEINVALID", "Client type not recognized by the system.");
}

$ip = getipaddress();
$pairtime = $now;
$authcode = calculateauthcode($type, $ip, $pairtime);

adddevice($type, $ip, $pairtime, $now, $authcode);


$returnstack["requesttimeout"] = 5;
$returnstack["authcode"] = $authcode;

echo formatreturnvalues($returnstack);

?>