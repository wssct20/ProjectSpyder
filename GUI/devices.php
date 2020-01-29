<?php
require_once("system.php");
global $systemname;
checksession();

$action = $_POST["action"] ?? "";

if ($action == "delete") {
	//TODO: check for user permission
	$id = $_POST["id"] ?? "";
	if ($username == "") die("INVALIDID");
	deletedevice($user["id"]);
	header("DEBUG: devices.php delete device successful");
	header("Location: usermanagement.php",true,303);
	die();
}

$friendlytypenames = array(
	//"motor" => "Motor",
	//"lock" => "Lock",
	"addressablergbledstrip" => "LED-Strip",
	"rgbled" => "RGB-LED",
	"led" => "LED",
	//"epaper" => "E-Paper Screen",
	"button" => "Button",
	//"finger" => "Fingerprint sensor",
	//"temp" => "temperature sensor",
	//"rotation" => "rotational sensor",
	"rgbdetect" => "RGB sensor",
	"raw" => "unknown",
	"" => null, //for automatic fallback using ?? when no friendlyname was found
);


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
			//this will generate a table of devices paired with the system
			//devices array: columns of the devices table to show. format: Visible text => column name of table devices.
			/*$columns = array(
				"ID" => "id",
				"Name" => "name",
				"Type" => "type",
				"IP-Address" => "ipaddress",
			);*/
			$devices = getdevices();
			if (sizeof($devices) == 0) {
				echo("No devices found.");
			} else {
				?>
				<table>
					<?php
					/*echo "<tr>";
					foreach ($columns as $key => $column) {
						echo "<th>";
						echo $key;
						echo "</th>";
					}
					echo "</tr>";
					foreach ($devices as $device) {
						echo "<tr>";
						foreach ($columns as $column) {
							echo "<td>";
							echo ($friendlytypenames[$device[$column]] ?? $device[$column]);
							echo "</td>";
						}
						echo "</tr>";
					}*/
					
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