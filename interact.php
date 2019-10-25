<?php
require_once("system.php");

$authcode = $_REQUEST["authcode"];
$state = $_REQUEST["state"];

$now = time();
$ip = getipaddress();


//var_dump($result);


$device = getdevice($authcode);
if (sizeof($device) == 0) die("AUTHFAILED");
if ($device["authcode"] != $authcode) die ("AUTHSQLFAIL"); //should never happen

updatedevice($device["id"], $now, $ip);

updatedata($device["id"], $device["type"], $state);

?>