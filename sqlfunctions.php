<?php
//SQLFUNCTIONS.PHP: functions which interact with the mysql server

// DEVICE MANAGEMENT

function adddevice($type, $ip, $pairtime, $now, $authcode) {
	//adddevice: add a device to the system
	global $db;
	// Create device entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO devices(type, ipaddress, pairtime, lastact, authcode) VALUES (?, ?, ?, ?, ?)"))) {
		dieerror("ERRSQLTABLE", "adddevice insert devices Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("ssiis", $type, $ip, $pairtime, $now, $authcode)) {
		dieerror("ERRSQLTABLE", "adddevice insert devices Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "adddevice insert devices Execute failed: (" . $statement->errno . ") " . $statement->error);
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

function getdevices() {
	//getdevices: get all devices
	global $db;
	if (!($statement = $db->prepare("SELECT * FROM devices"))) {
		dieerror("ERRSQLTABLE", "getdevices Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "getdevices Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getdevices Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: fetch all as array with associative names
	return $result->fetch_all(MYSQLI_ASSOC);
}

function deletedevice($id) {
	//deletedevice: delete a device
	global $db;
	// delete device entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("DELETE FROM devices WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "deletedevice delete from devices Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("i", $id)) {
		dieerror("ERRSQLTABLE", "deletedevice delete from devices Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "deletedevice delete from devices Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function updatedevicename($id, $name) {
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE devices SET name=? WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "updatedevicename Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("si", $name, $id)) {
		dieerror("ERRSQLTABLE", "updatedevicename Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "updatedevicename Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function sqlupdatedata($id, $data) {
	//added sql in front because updatedata in functions needs to encode json string first
	//updatedata: set data of a device in the according type table
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE devices SET data=? WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "updatedata Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("si", $data, $id)) {
		dieerror("ERRSQLTABLE", "updatedata Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "updatedata Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

// SANITY CHECK

function checktables() {
	//checktables: check if all needed tables are available by querying a create if not exist
	global $db;
	//unprepared query: create table devices
	if (!$db->query("create table if not exists devices(id INT NOT NULL AUTO_INCREMENT, name TEXT, type TEXT NOT NULL, ipaddress TEXT NOT NULL, lastact BIGINT NOT NULL, pairtime BIGINT NOT NULL, authcode TEXT NOT NULL, data TEXT , PRIMARY KEY (id));")
	) {
		dieerror("ERRSQLTABLE", "checktables devices Table creation failed: (" . $db->errno . ") " . $db->error);
	}
	//unprepared query: create table conditions
	if (!$db->query("create table if not exists conditions(id INT NOT NULL AUTO_INCREMENT, name TEXT, ifid INT NOT NULL, ifvar TEXT NOT NULL, ifvalue TEXT NOT NULL, thenid INT NOT NULL, thenvar TEXT NOT NULL, thenvalue TEXT NOT NULL, PRIMARY KEY (id));")
	) {
		dieerror("ERRSQLTABLE", "checktables conditions Table creation failed: (" . $db->errno . ") " . $db->error);
	}
	//unprepared query: create table guiusers
	if (!$db->query("create table if not exists guiusers(id INT NOT NULL AUTO_INCREMENT, name TEXT NOT NULL, pass TEXT NOT NULL, role TEXT NOT NULL, color TEXT, PRIMARY KEY (id));")
	) {
		dieerror("ERRSQLTABLE", "checktables guiusers Table creation failed: (" . $db->errno . ") " . $db->error);
	}
}

// CONDITION MANAGEMENT

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
	// Stage 3: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getconditions Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: fetch all as array with associative names
	return $result->fetch_all(MYSQLI_ASSOC);
}

function getconditionbyid($id) {
	//getconditionbyid: get a condition using its unique id
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM conditions WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "getconditionbyid Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("i", $id)) {
		dieerror("ERRSQLTABLE", "getconditionbyid Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "getconditionbyid Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getconditionbyid Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch row
	return $result->fetch_array();
}

function addcondition($ifid, $ifvar, $ifvalue, $thenid, $thenvar, $thenvalue, $name) {
	//TODO: untested code
	//addcondition: add a condition
	global $db;
	// Create condition entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO conditions(ifid, ifvar, ifvalue, thenid, thenvar, thenvalue, name) VALUES (?, ?, ?, ?, ?, ?, ?)"))) {
		dieerror("ERRSQLTABLE", "addcondition insert conditions Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("ississs", $ifid, $ifvar, $ifvalue, $thenid, $thenvar, $thenvalue, $name)) {
		dieerror("ERRSQLTABLE", "addcondition insert conditions Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "addcondition insert conditions Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function updatecondition($id, $ifid, $ifvar, $ifvalue, $thenid, $thenvar, $thenvalue, $name) {
	//TODO: untested code
	//updatecondition: update an existing conditon
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE conditions SET ifid=?, ifvar=?, ifvalue=?, thenid=?, thenvar=?, thenvalue=?, name=? WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "updatecondition Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("ississsi", $ifid, $ifvar, $ifvalue, $thenid, $thenvar, $thenvalue, $name, $id)) {
		dieerror("ERRSQLTABLE", "updatecondition Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "updatecondition Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function deletecondition($id) {
	//deletecondition: delete a condition
	global $db;
	// delete condition entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("DELETE FROM conditions WHERE id=?"))) {
		dieerror("ERRSQLTABLE", "deletecondition Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("i", $id)) {
		dieerror("ERRSQLTABLE", "deletecondition Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "deletecondition Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

// USER MANAGEMENT

function getuserbyusername($username) {
	//getuserbyusername: get a user using his username
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM guiusers WHERE name=?"))) {
		dieerror("ERRSQLTABLE", "getuserbyusername Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("s", $username)) {
		dieerror("ERRSQLTABLE", "getuserbyusername Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "getuserbyusername Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getuserbyusername Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch row
	return $result->fetch_array();
}

function getusers() {
	//getusers: get all users
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM guiusers"))) {
		dieerror("ERRSQLTABLE", "getusers Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "getusers Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: get results
	if (!($result = $statement->get_result())) {
		dieerror("ERRSQLTABLE", "getusers Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: fetch all as array with associative names
	return $result->fetch_all(MYSQLI_ASSOC);
}

function adduser($username, $password, $role) {
	//adduser: add a user to the gui
	global $db;
	// Create user entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO guiusers(name, pass, role) VALUES (?, ?, ?)"))) {
		dieerror("ERRSQLTABLE", "adduser insert guiusers Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("sss", $username, $password, $role)) {
		dieerror("ERRSQLTABLE", "adduser insert guiusers Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "adduser insert guiusers Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function deleteuser($id, $username) {
	//deleteuser: delete a user
	global $db;
	// delete user entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("DELETE FROM guiusers WHERE id=? AND name=?"))) {
		dieerror("ERRSQLTABLE", "deleteuser delete from guiusers Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("is", $id, $username)) {
		dieerror("ERRSQLTABLE", "deleteuser delete from guiusers Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		dieerror("ERRSQLTABLE", "deleteuser delete from guiusers Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

//EOF
?>