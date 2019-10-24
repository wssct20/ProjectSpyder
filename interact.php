<?php
require_once("system.php");

$authcode = $_REQUEST["authcode"];

$now = time();
$ip = getipaddress();


//var_dump($result);

if (sizeof($result) == 0) die("AUTHFAILED");
if ($result["authcode"] != $authcode) die ("AUTHSQLFAIL"); //should never happen

$device = getdevice($authcode);

updatedevice($device["id"], $now, $ip);



?>