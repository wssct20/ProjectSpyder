<?php 
require_once("system.php");

$type = $_REQUEST["type"];
$subtype = $_REQUEST["subtype"];

$now = time();

//return array
$returnstack = array();

//check if type is valid and supported by the system
$typesvalid = checktypes($type, $subtype);
if (!$typesvalid) {
	dieerror("TYPEINVALID");
}

$ip = getipaddress();
$pairtime = $now;
$authcode = calculateauthcode($type,$subtype,$ip,$pairtime);

adddevice($type, $subtype, $ip, $pairtime, $now, $authcode);


$returnstack["authcode"] = $authcode;

echo formatreturnvalues($returnstack);

?>