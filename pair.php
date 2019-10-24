<?php 
require_once("system.php");

$type = $_REQUEST["type"];
$subtype = $_REQUEST["subtype"];

$now = time();

$typesvalid = checktypes($type, $subtype);
if (!$typesvalid) {
	die("TYPEINVALID");
}

$ip = getipaddress();
$pairtime = $now;
$authcode = calculateauthcode($type,$subtype,$ip,$pairtime);

adddevice($type, $subtype, $ip, $pairtime, $now, $authcode);

$returnvalues = array(
	"authcode" => $authcode,
);
echo formatreturnvalues($returnvalues);

?>