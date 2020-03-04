<?php 
$now = time();
require_once("system.php");
$PARAM = getparameters();

$type = $PARAM["type"];

//return array
$returnstack = array();

$ip = getipaddress();
$pairtime = $now;
$authcode = calculateauthcode($type, $ip, $pairtime);

adddevice($type, $ip, $pairtime, $now, $authcode);
updatedevice(getdevicebyauthcode($authcode)["id"], $now, $ip);


$returnstack["requesttimeout"] = 5;
$returnstack["authcode"] = $authcode;

echo formatreturnvalues($returnstack, null);

?>