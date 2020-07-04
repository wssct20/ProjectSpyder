<?php
$now = time();
require_once("system.php");
$PARAM = getparameters();

$type = $PARAM["type"] ?? "";
$data = $PARAM["data"] ?? "";

//return array
$returnstack = array();

$ip = getipaddress();
$pairtime = $now;
$authcode = calculateauthcode($type, $ip, $pairtime);

adddevice($type, $ip, $pairtime, $now, $authcode);
updatedevice(getdevicebyauthcode($authcode)["id"], $now, $ip);
if (!empty($data)) {
	if (jsondecode($data) == null) dieerror("DATAINVALID", "Data is invalid, maybe the JSON is not complete");
    updatedata(getdevicebyauthcode($authcode)["id"], jsondecode($data));
}


$returnstack["requesttimeout"] = 5;
$returnstack["authcode"] = $authcode;

echo formatreturnvalues($returnstack, null);

?>