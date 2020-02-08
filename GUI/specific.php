<?php 

function gettile($type, $state) {
	//gettile: needs to output the state userfriendly for the GUI
	$state = sanitizehtml($state);
	$returnstring = "";
	switch($type) {
		case "button":
			$value = intval($state);
			$returnstring = "<p> The button is " . ($state == 0 ? "released" : "pressed") . ".</p>";
			break;
		case "digitaloutput":
			$value = intval($state);
			$returnstring = "<p> This output is " . ($state == 0 ? "off" : "on") . ".</p>";
			break;
		case "raw":
		default:
			$returnstring = "<p>" . $state . "</p>";
			break;
	}
	return $returnstring;
}

?>