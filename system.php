<?php
require_once("functions.php");

$db = new mysqli($sqlhost, $sqluser, $sqlpass, $sqldbname);
if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	die();
}
echo $mysqli->host_info . "\n";

?>