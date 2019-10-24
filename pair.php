<?php 
require_once("system.php");

$type = $_REQUEST["type"];
$subtype = $_REQUEST["subtype"];

$now = time();

$typesvalid = checktypes($type, $subtype);
die ($typesvalid);
if (!$typesvalid) {
	die("TYPEINVALID");
}


$ip = getipaddress();

$pairtime = $now;

$authcode = calculateauthcode($type,$subtype,$ip,$pairtime);

// Prepared statement, stage 1: prepare
if (!($statement = $db->prepare("INSERT INTO devices(type, subtype, ipaddress, pairtime, lastact, authcode) VALUES (?, ?, ?, ?, ?, ?, ?)"))) {
	die("Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error);
}
// Prepared statement, stage 2: bind
if (!$statement->bind_param("sssiis", $type, $subtype, $ip, $pairtime, $now, $authcode)) {
	die("Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
}
// Prepared statement, stage 3: execute
if (!$statement->execute()) {
	die("Execute failed: (" . $statement->errno . ") " . $statement->error);
}

?>