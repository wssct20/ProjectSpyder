<?php
require_once("system.php");
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

if ($action == "overwritefield") {
	//TODO: check for user permission
	$id = $_POST["id"] ?? "";
	if ($id == "") die("INVALIDID");
	$device = getdevicebyid($id);
	$data = getdata($device);
	$category = $_POST["category"] ?? "";
	switch ($category) {
		case "data":
		case "settings":
		break;
		default:
		die("INVALIDCATEGORY");
	}
	$var = $_POST["var"] ?? "";
	if ($var == "") die("INVALIDVAR");
	$value = $_POST["value"] ?? "";
	$data[$category][$var] = $value;
	updatedata($id, $data);
	header("DEBUG: devices.php overwritefield successful");
	header("Location: devices.php",true,303);
	die();
}

if ($action == "details") {
	$id = $_POST["id"] ?? "";
	if ($id == "") die("INVALIDID");
	$id = intval($id);
	$device = getdevicebyid($id);
	$data = getdata($device);
	$friendlytype = ($data["friendly"]["type"] ?? $device["type"]);
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
				<?php 
					if (sizeof($data["usermodifiabledata"]) > 0) echo "<h3>Data</h3>";
					foreach ($data["usermodifiabledata"] as $usermodifiabledatafield => $usermodifiabledatavalue) {
						?>
							<form method=post>
								<input type=text name=id value="<?php echo $device["id"]; ?>" style="display: none;">
								<input type=text name=action value=overwritefield style="display: none;">
								<input type=text name=category value=data style="display: none;">
								<input type=text name=var value="<?php echo $usermodifiabledatavalue; ?>" style="display: none;">
								<label><?php sanitizehtml($data["friendly"]["datavar"][$usermodifiabledatafield] ?? $usermodifiabledatafield) ?>: </label>
								<?php //TODO: add for= to label for accessablity ?>
								<input type=text name=value value="<?php echo $data["data"][$usermodifiabledatavalue]; ?>">
								<input type=submit name=submit value="Overwrite">
							</form>
						<?php
					}
				?>
				<?php 
					if (sizeof($data["settings"]) > 0) echo "<h3>Settings</h3>";
					foreach ($data["settings"] as $settingsfield => $settingsvalue) {
						?>
							<form method=post>
								<input type=text name=id value="<?php echo $device["id"]; ?>" style="display: none;">
								<input type=text name=action value=overwritesettingsfield style="display: none;">
								<input type=text name=category value=settings style="display: none;">
								<input type=text name=var value="<?php echo $settingsfield; ?>" style="display: none;">
								<label><?php sanitizehtml($data["friendly"]["settingsvar"][$datafield] ?? $settingsfield) ?>: </label>
								<?php //TODO: add for= to label for accessablity ?>
								<input type=text name=value value="<?php echo $data["settings"][$settingsfield]; ?>">
								<input type=submit name=submit value="Overwrite">
							</form>
						<?php
					}
				?>
				<h3>Manage</h3>
				<form method=post>
					<input type=text name=id value="<?php echo $device["id"]; ?>" style="display: none;">
					<input type=text name=action value=rename style="display: none;">
					<label for="devicename">Name: </label>
					<input type=text name=name id="devicename"
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
				<h4 style="margin-bottom: 0;">Debug</h4>
				<p style="margin-top: 0;"><?php echo jsonencode($data); ?></p>
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
			}
			th {
				color: white;
				border-bottom: white solid 1px;
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
					echo "<th>" . "" . "</th>"; //line with manage button
					echo "</tr>";
					foreach ($devices as $device) {
						$data = getdata($device);
						echo "<tr>";
						echo "<td>" . $device["id"] . "</td>";
						echo "<td>" . getdevicename($device) . "</td>";
						echo "<td>" . ($data["friendly"]["type"] ?? $device["type"]) . "</td>";
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
