<?php

function adddevice($type, $subtype, $ip, $pairtime, $now, $authcode) {
	global $db;
	// Create device entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO devices(type, subtype, ipaddress, pairtime, lastact, authcode) VALUES (?, ?, ?, ?, ?, ?)"))) {
		die("adddevice insert devices Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("sssiis", $type, $subtype, $ip, $pairtime, $now, $authcode)) {
		die("adddevice insert devices Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("adddevice insert devices Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	
	return;
	//TODO untested code, skipping for now
	
	$statement->close();
	$statement = null;
	
	$device = getdevice($authcode);
	
	// Create type specific entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO "+$device["type"]+"(id) VALUES (?)"))) {
		die("adddevice insert "+$device["type"]+" Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("i", $device["id"])) {
		die("adddevice insert "+$device["type"]+" Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("adddevice insert "+$device["type"]+" Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function getdevicebyauthcode($authcode) {
	//TODO function rename, check for occurencies
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM devices WHERE authcode=?"))) {
		echo "getdevicebyauthcode Prepare failed: (" . $db->errno . ") " . $db->error;
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("s", $authcode)) {
		die("getdevicebyauthcode Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("getdevicebyauthcode Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		die("getdevicebyauthcode Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch row
	return $result->fetch_array();
}

function getdevicebyid($id) {
	//TODO untested code, but believed to be working
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM devices WHERE id=?"))) {
		echo "getdevicebyid Prepare failed: (" . $db->errno . ") " . $db->error;
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("i", $id)) {
		die("getdevicebyid Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("getdevicebyid Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		die("getdevicebyid Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch row
	return $result->fetch_array();
}

function updatedevice($id, $now, $ipaddress) {
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE devices SET ipaddress=?, lastact=? WHERE id=?"))) {
		die("updatedevice Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("sii", $ipaddress, $now, $id)) {
		die("updatedevice Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("updatedevice Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function getdata($id, $type) {
	//TODO untested code
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM "+$type+" WHERE id=?"))) {
		echo "getdevicebyid Prepare failed: (" . $db->errno . ") " . $db->error;
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("i", $id)) {
		die("getdevicebyid Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("getdevicebyid Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		die("getdevicebyid Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch state from row
	return $result->fetch_array()[state];
}

function updatedata($id, $type, $state) {
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE "+$type+" SET state=? WHERE id=?"))) {
		die("updatedevice Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("si", $state, $id)) {
		die("updatedevice Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("updatedevice Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function checktables() {
	return;
	//TODO untested code, temporarily disabled
	global $db;
	//unprepared query: create table devices
	if (!$db->query("create table if not exists devices(id INT NOT NULL AUTO_INCREMENT, name TEXT, type TEXT NOT NULL, ipaddress TEXT NOT NULL, lastact BIGINT NOT NULL, pairtime BIGINT NOT NULL, subtype TEXT NOT NULL, authcode TEXT NOT NULL, PRIMARY KEY (id));")
	) {
		die("checktables devices Table creation failed: (" . $db->errno . ") " . $db->error);
	}
	global $types;
	foreach ($types as $type) {
		//unprepared query: create table $type
		if (!$db->query("create table if not exists " + $type + "(id INT NOT NULL, state TEXT, PRIMARY KEY(id));")
		) {
			die("checktables " + $type + " Table creation failed: (" . $db->errno . ") " . $db->error);
		}
	}
	if (!$db->query("create table if not exists conditions(ifid INT NOT NULL, ifstate TEXT NOT NULL, thenid INT NOT NULL, thenstate TEXT NOT NULL);")
	) {
		die("checktables conditions Table creation failed: (" . $db->errno . ") " . $db->error);
	}
}

function getconditions() {
	return;
	//TODO untested code
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM conditions"))) {
		echo "getconditions Prepare failed: (" . $db->errno . ") " . $db->error;
	}
	// Stage 2: execute
	if (!$statement->execute()) {
		die("getconditions Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		die("getconditions Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch row
	return $result->fetch_array();
}

?>