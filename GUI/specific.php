<?php 

function gettile($type, $state) {
	$state = sanitizehtml($state);
	$returnstring = "";
	switch($type) {
		case "button":
			$value = intval($state);
			$returnstring = "<p> The button is " . ($state == 0 ? "released" : "pressed") . ".</p>";
			break;
		case "raw":
		default:
			$returnstring = "<p>" . $state . "</p>";
			break;
	}
	return $returnstring;
}

?>