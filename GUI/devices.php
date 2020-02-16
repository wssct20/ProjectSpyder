<?php
require_once("system.php");
require_once(__DIR__."/../specific.php"); //idk why but this is needed although imported though system.php > system.php > functions.php > specific.php
global $systemname;
checksession();

$action = $_POST["action"] ?? "";

if ($action == "delete") {
	//TODO: check for user permission
	$id = $_POST["id"] ?? "";
	if ($id == "") die("INVALIDID");
	$id = intval($id);
	deletedevice($id);
	//TODO: delete conditions with this device
	header("DEBUG: devices.php delete device successful");
	header("Location: devices.php",true,303);
	die();
}

if ($action == "rename") {
	//TODO: check for user permission
	$id = $_POST["id"] ?? "";
	if ($id == "") die("INVALIDID");
	$id = intval($id);
	$name = $_POST["name"] ?? "";
	$name = sanitizehtml($name);
	updatedevicename($id, $name);
	header("DEBUG: devices.php rename device successful");
	header("Location: devices.php",true,303);
	die();
}

if ($action == "overwritestate") {
	//TODO: check for user permission
	$id = $_POST["id"] ?? "";
	if ($id == "") die("INVALIDID");
	$state = $_POST["state"] ?? "";
	if (!checkstate($state, getdevicebyid($id)["type"])) {
		header("DEBUG: devices.php overwritestate failed due to invalid state");
		$_POST["action"] = "";
		header("Location: devices.php",true,307);
		die();
	}
	updatedata($id, $state);
	header("DEBUG: devices.php overwritestate successful");
	header("Location: devices.php",true,303);
	die();
}

if ($action == "details") {
	$id = $_POST["id"] ?? "";
	if ($id == "") die("INVALIDID");
	$id = intval($id);
	$device = getdevicebyid($id);
	$friendlytype = ($friendlytypenames[$device["type"]] ?? $device["type"]);
	?>
	
	<!DOCTYPE html>
	<html lang="de">
		<head>
	        <meta charset="utf-8">
	        <link rel="stylesheet" href="style.css">
	        <link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
	        <link href="https://fonts.googleapis.com/css?family=Roboto+Condensed&display=swap" rel="stylesheet"> 
			<title><?php echo $systemname;?> Devices</title>
		</head>
		<body>
			<nav>
				<h1><a href="main.php"><?php echo $systemname;?></a> Devices</h1>
				<ul>
	                <div class="separator"></div>
					<li><a href="main.php">Home</a></li>
					<li><a href="devices.php">Devices</a></li>
				</ul>
			</nav>
			
			<div class="settings">
				<h2><?php echo $friendlytype." ".$device["id"]; echo empty($device["name"]) ? "" : " - ".$device["name"]; ?></h2>
				<!-- TODO: change to json
				<h3>State</h3>
				<form method=post>
					<input type=text name=id value="<?php echo $device["id"]; ?>" style="display: none;">
					<input type=text name=action value=overwritestate style="display: none;">
					<input type=text name=state value="<?php echo getdata($device["id"]); ?>">
					<input type=submit name=submit value="Overwrite">
				</form>
				<br>
				-->
				<h3>Manage</h3>
				<form method=post>
					<input type=text name=id value="<?php echo $device["id"]; ?>" style="display: none;">
					<input type=text name=action value=rename style="display: none;">
					<input type=text name=name 
						placeholder="<?php echo $friendlytype." ".$device["id"]; ?>" 
						value="<?php echo empty($device["name"]) ? "" : $device["name"]; ?>">
					<input type=submit name=submit value="Rename">
				</form>
				<br>
				<form method=post>
					<input type=text name=id value="<?php echo $device["id"]; ?>" style="display: none;">
					<input type=text name=action value=delete style="display: none;">
					<input type=submit name=submit value="Delete">
				</form>
			</div>
		</body>
	</html>
	
	<?php 
	die();
}


?>

<!DOCTYPE html>
<html lang="de">
	<head>
        <meta charset="utf-8">
        <link rel="stylesheet" href="style.css">
        <link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
        <link href="https://fonts.googleapis.com/css?family=Roboto+Condensed&display=swap" rel="stylesheet"> 
		<title><?php echo $systemname;?> Devices</title>
		<style>
			td {
				color: white;
				border: white solid 1px;
			}
			th {
				color: white;
				border: white solid 1px;
			}
		</style>
	</head>
	<body>
		<nav>
			<h1><a href="main.php"><?php echo $systemname;?></a> Devices</h1>
			<ul>
                <div class="separator"></div>
				<li><a href="main.php">Home</a></li>
				<!--<li><a href="devices.php">Devices</a></li>-->
			</ul>
		</nav>
		
		<div class="settings">
		
			<h2>Paired Devices</h2>
			<?php 
			//this generates a table of devices paired with the system
			$devices = getdevices();
			if (sizeof($devices) == 0) {
				echo("No devices found.");
			} else {
				?>
				<table>
					<?php
					echo "<tr>";
					echo "<th>" . "ID" . "</th>";
					echo "<th>" . "Name" . "</th>";
					echo "<th>" . "Type" . "</th>";
					echo "<th>" . "IP-Address" . "</th>";
					echo "<th>" . "" . "</th>"; //line with edit/delete buttons
					echo "</tr>";
					foreach ($devices as $device) {
						echo "<tr>";
						echo "<td>" . $device["id"] . "</td>";
						echo "<td>" . (empty($device["name"]) ? ($friendlytypenames[$device["type"]] ?? $device["type"])." ".$device["id"] : $device["name"]) . "</td>";
						echo "<td>" . ($friendlytypenames[$device["type"]] ?? $device["type"]) . "</td>";
						echo "<td>" . $device["ipaddress"] . "</td>";
						?>
						<td>
							<form method=post style="margin: 0;">
								<input type=text name=id value="<?php echo $device["id"]; ?>" style="display: none;">
								<input type=text name=action value=details style="display: none;">
								<input type=submit name=submit value="Manage">
							</form>
						</td>
						<?php
						echo "</tr>";
					}
					?>
				</table>
				<?php
			}
			?>
			
		</div>
	</body>
</html>