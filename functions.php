<?php

function preparereturnvalues($data, $debug) {
	$returntext = "";
	if (sizeof($debug) > 0) {
		$returntext = $returntext."#DEBUG\n";
		foreach ($debug as $key => $value) {
			$returntext = $returntext."[".$key."]"."=>".$value."\n";
		}
	}
	$returntext = $returntext."#DATA\n";
	foreach ($data as $key => $value) {
		$returntext = $returntext."[".$key."]"."=>".$value."\n";
	}
	$returntext = $returntext."#END\n";
	return $returntext;
}

?>