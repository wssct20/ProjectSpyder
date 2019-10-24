<?php

function calculateauthcode($id, $ipaddress, $pairtime) {
	$data = $hashprefix.$id.$ipaddress.$pairtime;
	return hash($hashalgo, $data, false);
}

function formatreturnvalues($data, $debug) {
	$returntext = "";
	$returntext = $returntext."#START\n";
	if (isset($debug) > 0) {
		$returntext = $returntext."#DEBUG\n";
		$returntext = $returntext.$debug."\n";
	}
	$returntext = $returntext."#DATA\n";
	foreach ($data as $key => $value) {
		$returntext = $returntext."[".$key."]"."=>".$value."\n";
	}
	$returntext = $returntext."#END";
	//$returntext = $returntext."\n";
	return $returntext;
}

?>