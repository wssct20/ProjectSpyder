<?php
require_once("system.php");

$authcode = $_REQUEST["authcode"];

$now = time();
$ip = getipaddress();

// Prepared statement, stage 1: prepare
if (!($statement = $db->prepare("SELECT * FROM devices WHERE authcode='?'"))) {
	echo "Prepare failed: (" . $db->errno . ") " . $db->error;
}
// Prepared statement, stage 2: bind
if (!$statement->bind_param("s", $authcode)) {
	die("Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
}
// Prepared statement, stage 3: execute
if (!$statement->execute()) {
	echo "Execute failed: (" . $statement->errno . ") " . $statement->error;
}
// Prepared statement, stage 4: get results
if (!($result = $statement->get_result())) {
	echo "Getting result set failed: (" . $statement->errno . ") " . $statement->error;
}

var_dump($result->fetch_all());
?>