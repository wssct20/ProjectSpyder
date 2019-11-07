<?php

function adddevice($type, $subtype, $ip, $pairtime, $now, $authcode) {
	//adddevice: add a device to the system
	global $db;
	// Create device entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO devices(type, subtype, ipaddress, pairtime, lastact, authcode) VALUES (?, ?, ?, ?, ?, ?)"))) {
		dieerror("ERRSQLTABLE", "adddevice insert devices Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("sssiis", $type, $subtype, $ip, $pairtime, $now, $authcode)) {
		dieerror("ERRSQLTABLE", "adddevice insert devices Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "adddevice insert devices Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	
	$statement->close();
	$statement = null;
	
	$device = getdevicebyauthcode($authcode);
	
	// Create type specific entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO ".$device["type"]."(id) VALUES (?)"))) {
		dieerror("ERRSQLTABLE", "adddevice insert ".$device["type"]." Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("i", $device["id"])) {
		dieerror("ERRSQLTABLE", "adddevice insert ".$device["type"]." Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "adddevice insert ".$device["type"]." Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function getdevicebyauthcode($authcode) {
	//getdevicebyauthcode: get a device using its authcode
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM devices WHERE authcode=?"))) {
		dieerror("ERRSQLTABLE", "getdevicebyauthcode Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("s", $authcode)) {
		dieerror("ERRSQLTABLE", "getdevicebyauthcode Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "getdevicebyauthcode Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getdevicebyauthcode Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch row
	return $result->fetch_array();
}

function getdevicebyid($id) {
	//getdevicebyid: get a device using its unique id
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM devices WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "getdevicebyid Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("i", $id)) {
		dieerror("ERRSQLTABLE", "getdevicebyid Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "getdevicebyid Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getdevicebyid Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch row
	return $result->fetch_array();
}

function updatedevice($id, $now, $ipaddress) {
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE devices SET ipaddress=?, lastact=? WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "updatedevice Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("sii", $ipaddress, $now, $id)) {
		dieerror("ERRSQLTABLE", "updatedevice Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "updatedevice Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function getdata($id, $type) {
	//getdata: get data of a device from the according type table
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM ".$type." WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "getdata Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("i", $id)) {
		dieerror("ERRSQLTABLE", "getdata Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "getdata Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getdata Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch state from row
	return $result->fetch_array()[state];
}

function updatedata($id, $type, $state) {
	//updatedata: set data of a device in the according type table
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE ".$type." SET state=? WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "updatedevice Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("si", $state, $id)) {
		dieerror("ERRSQLTABLE", "updatedevice Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "updatedevice Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function checktables() {
	//checktables: check if all needed tables are available by querying a create if not exist
	global $db;
	//unprepared query: create table devices
	if (!$db->query("create table if not exists devices(id INT NOT NULL AUTO_INCREMENT, name TEXT, type TEXT NOT NULL, ipaddress TEXT NOT NULL, lastact BIGINT NOT NULL, pairtime BIGINT NOT NULL, subtype TEXT NOT NULL, authcode TEXT NOT NULL, PRIMARY KEY (id));")
	) {
		dieerror("ERRSQLTABLE", "checktables devices Table creation failed: (" . $db->errno . ") " . $db->error);
	}
	global $types;
	foreach ($types as $type) {
		//unprepared query: create table $type
		if (!$db->query("create table if not exists " . $type . "(id INT NOT NULL, state TEXT, PRIMARY KEY(id));")
		) {
			dieerror("ERRSQLTABLE", "checktables " . $type . " Table creation failed: (" . $db->errno . ") " . $db->error);
		}
	}
	//unprepared query: create table conditions
	if (!$db->query("create table if not exists conditions(ifid INT NOT NULL, ifstate TEXT NOT NULL, thenid INT NOT NULL, thenstate TEXT NOT NULL);")
	) {
		dieerror("ERRSQLTABLE", "checktables conditions Table creation failed: (" . $db->errno . ") " . $db->error);
	}
}

function getconditions() {
	//getconditions: get all conditions
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM conditions"))) {
		dieerror("ERRSQLTABLE", "getconditions Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "getconditions Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getconditions Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch all as array with associative names
	return $result->fetch_all(MYSQLI_BOTH);
}

?>