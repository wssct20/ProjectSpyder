<?php 

function specificactions($device, $requesttype, $returnstack) {
	//specificactions: actions specific to certain types
	switch ($device["type"]) {
		
		default:
			//no action needed
			break;
	}
}

function checkstate($state, $type) {
	return true; //TODO: complete rework
	switch ($type) {
		case "button":
		case "digitaloutput":
			if (sizeof(explode("", $state)) != 1) return false;
			$value = intval($state);
			if (!($value == 1 | $value == 0)) return false;
			return true;
		case "rgbled":
			$colors = explode(":", $state);
			if (sizeof($colors) != 3) return false;
			foreach ($colors as $color) {
				$color = intval($color);
				if ($color < 0 | $color > 255) return false;
			}
			return true;
		case "led":
			$color = intval($state);
			if ($color < 0 | $color > 255) return false;
			return true;
		case "rgbdetect":
			$values = explode(":", $state);
			if (sizeof($values) != 6) return false;
			foreach ($values as $value) {
				$value = intval($value);
				if ($value < 0 | $value > (2**16)) return false;
			}
			return true;
		case "rotation":
			$values = explode(":", $state);
			if (sizeof($values) != 5) return false;
			if (intval($values[0]) < -127 | intval($values[0]) > 128) return false;
			for ($i = 1; $i < sizeof($values) - 2; $i++) {
				$value = intval($values[$i]);
				if ($value < 0 | $value > 360) return false;
			}
			//if (intval($values[4]) < -65536 | intval($values[4]) > 65536) return false; //TODO: yet unknown size limits
			return true;
		case "temperature":
			$values = explode(":", $state);
			if (sizeof($values) != 2) return false;
			if (floatval($values[0]) < -273.15 | floatval($values[0]) > 1000) return false; //TODO: check limits
			if (floatval($values[1]) < 0 | floatval($values[1]) > 100) return false;
			return true;
		case "raw":
		default:
			//no check needed
			return true;	
	}
}

?>