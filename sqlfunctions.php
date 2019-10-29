<?php

function adddevice($type, $subtype, $ip, $pairtime, $now, $authcode) {
	global $db;
	// Create device entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO devices(type, subtype, ipaddress, pairtime, lastact, authcode) VALUES (?, ?, ?, ?, ?, ?)"))) {
		die("Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("sssiis", $type, $subtype, $ip, $pairtime, $now, $authcode)) {
		die("Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	
	$device = getdevice($authcode);
	
	// Create type specific entry
	// Stage 1: prepare
	if (!($statement = $db->prepare("INSERT INTO ?(id) VALUES (?)"))) {
		die("Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("si", $device["type"], $device["id"])) {
		die("Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function getdevice($authcode) {
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("SELECT * FROM devices WHERE authcode=?"))) {
		echo "Prepare failed: (" . $db->errno . ") " . $db->error;
	}
	// Stage 2: bind parameters
	if (!$statement->bind_param("s", $authcode)) {
		die("Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 4: get results
	if (!($result = $statement->get_result())) {
		die("Getting result set failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 5: fetch row
	return $result->fetch_array();
}

function updatedevice($id, $now, $ipaddress) {
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE devices SET ipaddress=?, lastact=? WHERE id=?"))) {
		die("Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("sii", $ipaddress, $now, $id)) {
		die("Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function updatedata($id, $type, $state) {
	global $db;
	// Stage 1: prepare
	if (!($statement = $db->prepare("UPDATE ? SET state=? WHERE id=?"))) {
		die("Prepare failed: (" . $db->errno . ") " . $db->error);
	}
	// Stage 2: bind
	if (!$statement->bind_param("ssi", $type, $state, $id)) {
		die("Binding parameters failed: (" . $statement->errno . ") " . $statement->error);
	}
	// Stage 3: execute
	if (!$statement->execute()) {
		die("Execute failed: (" . $statement->errno . ") " . $statement->error);
	}
}

function checktables() {
	global $db;
	if (!$db->query("create table if not exists devices(
			id INT NOT NULL AUTO_INCREMENT, 
			name TEXT, 
			type TEXT NOT NULL, 
			ipaddress TEXT NOT NULL, 
			lastact BIGINT NOT NULL, 
			pairtime BIGINT NOT NULL, 
			subtype TEXT NOT NULL, 
			authcode TEXT NOT NULL, 
			PRIMARY KEY (id)
			);
		")
	) {
		die("Table creation failed: (" . $db->errno . ") " . $db->error);
	}
	global $types;
	foreach ($types as $type) {
		if (!$db->query("create table if not exists " + $type + "(
			id INT NOT NULL,
			state TEXT,
			PRIMARY KEY(id)
			);
		")
		) {
			die("Table creation failed: (" . $db->errno . ") " . $db->error);
		}
	}
}

?>