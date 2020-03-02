<?php 
$now = time();
require_once("system.php");
$PARAM = getparameters();

$type = $PARAM["type"];
$data = $PARAM["data"];


//return array
$returnstack = array();

//check if type is valid and supported by the system
// temporarily disabled, as any type will be supported with JSON data
/*if (!checktype($type)) {
	dieerror("TYPEINVALID", "Client type not recognized by the system.");
}*/

$ip = getipaddress();
$pairtime = $now;
$authcode = calculateauthcode($type, $ip, $pairtime);

adddevice($type, $ip, $pairtime, $now, $authcode);
updatedevice(getdevicebyauthcode($authcode)["id"], $now, $ip);
if (!empty($data)) updatedata(getdevicebyauthcode($authcode)["id"], $data);


$returnstack["requesttimeout"] = 5;
$returnstack["authcode"] = $authcode;

echo formatreturnvalues($returnstack, null);

?>