<?php 
require_once("system.php");



$typesvalid = checktypes($type, $subtype);
print_r(get_defined_vars());
if (!$typesvalid) {
	die("TYPEINVALID");
}


$ip = getipaddress();
/*
// Prepared statement, stage 1: prepare
if (!($stmt = $mysqli->prepare("INSERT INTO devices() VALUES (?)"))) {
	echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
}

// Prepared statement, stage 2: bind
$id = 1;
if (!$stmt->bind_param("i", $id)) {
    echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
}

// Prepared statement, stage 3: execute
if (!$stmt->execute()) {
    echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
}*/

?>