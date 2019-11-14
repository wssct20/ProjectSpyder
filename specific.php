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
	switch ($type) {
		case "button":
			if (sizeof(explode("", $state)) != 1) return false;
			if (!($state == 1 | $state == 0)) return false;
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
		case "raw":
		default:
			//no check needed
			return true;	
	}
}

?>