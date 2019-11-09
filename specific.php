<?php 

function specificactions($device, $requesttype, $returnstack) {
	//specificactions: actions specific to certain types
	switch ($device["type"]) {
		
		default:
			//no action needed
			break;
	}
}

function checkstatesyntax($state, $type) {
	switch ($type) {
		case "button":
			if (!sizeof(explode("", $state)) == 1) return false;
			if (!($state == 1 || $state == 0)) return false;
			return true;
		default:
			//no check needed
			return true;	
	}
}

?>