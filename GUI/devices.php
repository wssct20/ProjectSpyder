<?php
require_once("system.php");
global $systemname;
checksession();

$action = $_POST["action"] ?? "";

if ($action == "delete") {
	//TODO: check for user permission
	$id = $_POST["id"] ?? "";
	if ($id == "") die("INVALIDID");
	deletedevice($id);
	header("DEBUG: devices.php delete device successful");
	header("Location: devices.php",true,303);
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
		
			<h3>Paired Devices</h3>
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
						echo "<td>" . $device["name"] . "</td>";
						echo "<td>" . ($friendlytypenames[$device["type"]] ?? $device["type"]) . "</td>";
						echo "<td>" . $device["ipaddress"] . "</td>";
						?>
						<td>
							<form method=post style="margin: 0;">
								<input type=text name=id value="<?php echo $device["id"]; ?>" style="display: none;">
								<input type=text name=action value=delete style="display: none;">
								<input type=submit name=submit value="Delete">
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