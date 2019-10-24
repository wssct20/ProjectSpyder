<?php
require("system.php");
//print_r($_REQUEST);
//print_r($_POST);
$debug = array(
	"debug" => "test",
);
echo preparereturnvalues($_REQUEST, $debug);
?>